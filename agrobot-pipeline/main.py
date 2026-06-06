import sys
import signal
import queue
import threading
import gi
gi.require_version('Gst', '1.0')
from gi.repository import Gst, GLib

from config import *
from hardware.arduino import init_arduino
from probe.pad_probe import pad_probe
from pipeline.callbacks import bus_call, handle_exit_signal, callback_newpad
import pipeline.callbacks as cb
from pipeline.terminal_logger import Logger

logger = Logger(TERMINAL_LOG_FILE)
sys.stdout = logger
sys.stderr = logger

def main():
    Gst.init(None)
    ros_queue = queue.Queue(maxsize=100)

    # --- BOOT UP ROS 2 BACKGROUND THREAD ---
    if ENABLE_ROS:
        print("="*60)
        print(f"[INIT] ROS 2 | Mode: {ROS_MODE}")
        print("="*60 + "\n")
        if ROS_MODE == "NAV_CLIENT":
            from ros_nodes.pad_probe_client import start_client_thread
            target = start_client_thread
        elif ROS_MODE == "BBOX_PUBLISHER":
            from ros_nodes.pad_probe_publisher import start_bbox_publisher_thread
            target = start_bbox_publisher_thread
        else:
            raise Exception("ROS_MODE invalid")
        threading.Thread(target=target, args=(ros_queue,), daemon=True).start()
        
        print("-"*40)
        print("✓ ROS background thread started\n")
        print("-"*40)

    # --- INITIALIZE ARDUINO ---
    arduino = None
    if ENABLE_ARDUINO:
        print("="*60)
        print(f"[INIT] Arduino | Port: {ARDUINO_PORT} @ {BAUD_RATE} baud")
        print("="*60 + "\n")
        arduino = init_arduino(ARDUINO_PORT, BAUD_RATE)

    if not ENABLE_DISPLAY and not ENABLE_RECORD:
        sys.stderr.write("ERROR: Both Display and Record are disabled!\n")
        sys.exit(1)
        
    print("="*60)
    print("[GST] Creating Pipeline")
    print("="*60 + "\n")
    
    pipeline = Gst.Pipeline()
    cb.main_pipeline = pipeline

    ########################################################################
    ####################### Make Pipeline Elements #########################
    ########################################################################

    elements = [pipeline]

    # --- 1. INPUT SOURCE ---
    if ENABLE_CAMERAS:
        # Live camera input
        if CAMERA_TYPE == "ZED":
            # ZED camera
            if NUM_OF_INPUTS == 1:
                # Single stream - left camera only
                zedsrc = Gst.ElementFactory.make("zedsrc", "zedsrc")
                zedsrc.set_property("camera-resolution", 3)
                zedsrc.set_property("camera-fps", 30)
                zedsrc.set_property("stream-type", 0)  # left only
                zedsrc.set_property("depth-mode", 0)
                # Look into ROI and Object Detection properties

                videoconvert = Gst.ElementFactory.make("videoconvert", "videoconvert")
                convert_src = Gst.ElementFactory.make("nvvideoconvert", "src_convert_src")
                caps_src = Gst.ElementFactory.make("capsfilter", "caps_src")
                caps_src.set_property("caps", Gst.Caps.from_string(
                    "video/x-raw(memory:NVMM), format=(string)RGBA, width=1920, height=1080, framerate=30/1")
                )
                elements.extend([zedsrc, videoconvert, convert_src, caps_src])

            elif NUM_OF_INPUTS == 2:
                # Left + right via zeddemux
                zedsrc = Gst.ElementFactory.make("zedsrc", "zedsrc")
                zedsrc.set_property("camera-resolution", 8)  # VGA for stereo
                zedsrc.set_property("camera-fps", 30)
                zedsrc.set_property("stream-type", 2)  # left + right composite
                zedsrc.set_property("depth-mode", 0)


                zeddemux = Gst.ElementFactory.make("zeddemux", "zeddemux")

                videoconvert_left = Gst.ElementFactory.make("videoconvert", "videoconvert_left")
                convert_src_left = Gst.ElementFactory.make("nvvideoconvert", "convert_src_left")
                caps_src_left = Gst.ElementFactory.make("capsfilter", "caps_src_left")
                caps_src_left.set_property("caps", Gst.Caps.from_string(
                    "video/x-raw(memory:NVMM), format=(string)RGBA, width=672, height=376, framerate=30/1")
                )

                videoconvert_right = Gst.ElementFactory.make("videoconvert", "videoconvert_right")
                convert_src_right = Gst.ElementFactory.make("nvvideoconvert", "convert_src_right")
                caps_src_right = Gst.ElementFactory.make("capsfilter", "caps_src_right")
                caps_src_right.set_property("caps", Gst.Caps.from_string(
                    "video/x-raw(memory:NVMM), format=(string)RGBA, width=672, height=376, framerate=30/1")
                )

                elements.extend([zedsrc, zeddemux,
                                videoconvert_left, convert_src_left, caps_src_left,
                                videoconvert_right, convert_src_right, caps_src_right])
    else:
        # Test video input
        source1 = Gst.ElementFactory.make("uridecodebin", "source1")
        source1.set_property("uri", "file://" + VIDEO_1_PATH)
        source2 = Gst.ElementFactory.make("uridecodebin", "source2")
        source2.set_property("uri", "file://" + VIDEO_2_PATH)
        elements.extend([source1, source2])
    
    streammux = Gst.ElementFactory.make("nvstreammux", "streammux")

    # --- 2. INFERENCE & TRACKING ---
    convert1 = Gst.ElementFactory.make("nvvideoconvert", "convert1")
    inference = Gst.ElementFactory.make("nvinfer", "inference")
    tracker = Gst.ElementFactory.make("nvtracker", "tracker")

    # --- 3. TILING & OSD ---
    convert2 = Gst.ElementFactory.make("nvvideoconvert", "convert2")
    tiler = Gst.ElementFactory.make("nvmultistreamtiler", "tiler")
    nvosd = Gst.ElementFactory.make("nvdsosd", "nvosd")

    # --- 4. THE SPLITTER (TEE) ---
    tee = Gst.ElementFactory.make("tee", "nvsink-tee")

    # List of all elements to check
    elements.extend([streammux, convert1, inference, tracker, convert2, tiler, nvosd, tee])

    # --- BRANCH A: LIVE DISPLAY ---
    if ENABLE_DISPLAY:
        queue_display = Gst.ElementFactory.make("queue", "queue_display")
        convert3 = Gst.ElementFactory.make("nvvideoconvert", "convert3")

        caps_filter = Gst.ElementFactory.make("capsfilter", "caps_filter")
        caps_filter.set_property("caps", Gst.Caps.from_string("video/x-raw, format=(string)I420"))

        sink_display = Gst.ElementFactory.make("xvimagesink", "sink_display")
        
        # Look into these
        sink_display.set_property("sync", 0)
        sink_display.set_property("qos", 0)

        elements.extend([queue_display, convert3, caps_filter, sink_display])

    # --- BRANCH B: FILE SAVE ---
    if ENABLE_RECORD:
        queue_record = Gst.ElementFactory.make("queue", "queue_record")
        convert_record = Gst.ElementFactory.make("nvvideoconvert", "convert_record")
        encoder = Gst.ElementFactory.make("nvv4l2h264enc", "encoder")
        parser = Gst.ElementFactory.make("h264parse", "parser")

        qtmux = Gst.ElementFactory.make("qtmux", "qtmux")
        qtmux.set_property("reserved-moov-update-period", 1000)

        sink_record = Gst.ElementFactory.make("filesink", "sink_record")
        sink_record.set_property("location", OUTPUT_VIDEO)
        sink_record.set_property("sync", 0)

        elements.extend([queue_record, convert_record, encoder, parser, qtmux, sink_record])

    # Check if all elements are created properly
    if not all(elements):
        sys.stderr.write("One or more elements could not be created.\n")
        sys.exit(1)

    ########################################################################
    ######################## CONFIGURE PROPERTIES ##########################
    ########################################################################

    streammux.set_property("width", WIDTH)
    streammux.set_property("height", HEIGHT)
    streammux.set_property("batch-size", NUM_OF_INPUTS)
    streammux.set_property("batched-push-timeout", 40000)

    inference.set_property("config-file-path", PGIE_CONFIG)
    tracker.set_property("ll-config-file", TRACKER_CONFIG)
    tracker.set_property("ll-lib-file", TRACKER_LIB)
    # Look into these
    tracker.set_property("tracker-width", 640)
    tracker.set_property("tracker-height", 384)

    nvosd.set_property("display-clock", 1)
    nvosd.set_property("clock-font-size", 15)
    nvosd.set_property("display-text", 1)

    tiler.set_property("rows", 1)
    tiler.set_property("columns", NUM_OF_INPUTS)
    tiler.set_property("width", WIDTH)
    tiler.set_property("height", HEIGHT)

    ########################################################################
    ########################## ADD/LINK ELEMENTS ###########################
    ########################################################################    

    # --- ADD TO PIPELINE ---
    for elem in elements:
        if elem is not pipeline:
            pipeline.add(elem)

    # --- LINKING ---
    print("="*60)
    print("[GST] Linking Elements")
    print("="*60 + "\n")

    # 1. Input source
    if ENABLE_CAMERAS:
        if CAMERA_TYPE == "ZED":
            if NUM_OF_INPUTS == 1:
                zedsrc.link(videoconvert)
                videoconvert.link(convert_src)
                convert_src.link(caps_src)
                caps_src.get_static_pad("src").link(streammux.get_request_pad("sink_0"))

            elif NUM_OF_INPUTS == 2:
                zedsrc.link(zeddemux)

                # Left stream -> sink_0
                demux_left = zeddemux.get_static_pad("src_left")
                demux_left.link(videoconvert_left.get_static_pad("sink"))
                videoconvert_left.link(convert_src_left)
                convert_src_left.link(caps_src_left)
                caps_src_left.get_static_pad("src").link(streammux.get_request_pad("sink_0"))

                # Right stream -> sink_1
                demux_right = zeddemux.get_static_pad("src_aux")
                demux_right.link(videoconvert_right.get_static_pad("sink"))
                videoconvert_right.link(convert_src_right)
                convert_src_right.link(caps_src_right)
                caps_src_right.get_static_pad("src").link(streammux.get_request_pad("sink_1"))
    else:
        sinkpad1 = streammux.get_request_pad("sink_0")
        sinkpad2 = streammux.get_request_pad("sink_1")
        source1.connect("pad-added", callback_newpad, sinkpad1)
        source2.connect("pad-added", callback_newpad, sinkpad2)

    # 2. Main Trunk
    streammux.link(convert1)
    convert1.link(inference)
    inference.link(tracker)
    tracker.link(convert2)
    convert2.link(tiler)
    tiler.link(nvosd)
    nvosd.link(tee)

    # 3. Branch A (Display)
    if ENABLE_DISPLAY:
        tee.get_request_pad("src_%u").link(queue_display.get_static_pad("sink"))
        queue_display.link(convert3)
        convert3.link(caps_filter)
        caps_filter.link(sink_display)

    # 4. Branch B (Recording)
    if ENABLE_RECORD:
        tee.get_request_pad("src_%u").link(queue_record.get_static_pad("sink"))
        queue_record.link(convert_record)
        convert_record.link(encoder)
        encoder.link(parser)
        parser.link(qtmux)
        qtmux.link(sink_record)

    # --- ATTACH PAD PROBE ---
    # Attach the probe to the SINK pad of 'convert2', after the tracker
    convert2.get_static_pad("sink").add_probe(
        Gst.PadProbeType.BUFFER, pad_probe, {"arduino": arduino, "ros_queue": ros_queue}
    )

    ########################################################################
    ############################ START PIPELINE ############################
    ########################################################################

    loop = GLib.MainLoop()
    bus = pipeline.get_bus()
    bus.add_signal_watch()
    bus.connect("message", bus_call, (loop, pipeline))

    signal.signal(signal.SIGINT, handle_exit_signal)

    print("="*60)
    print(f"[GST] Starting Pipeline")
    print(f"      Display: {ENABLE_DISPLAY} | Recording: {ENABLE_RECORD}")
    print("="*60 + "\n")

    pipeline.set_state(Gst.State.PLAYING)
    try:
        loop.run()
    except Exception as e:
        print(f"Error: {e}")

    print("[GST] Exiting\n")
    pipeline.set_state(Gst.State.NULL)
    return 0

if __name__ == "__main__":
    main()