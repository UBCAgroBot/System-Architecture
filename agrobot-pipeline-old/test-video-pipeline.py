import sys
import os
import gi
gi.require_version('Gst', '1.0')
# import csv
import serial
import time
from gi.repository import Gst, GLib
import queue
import threading
from ros_nodes.pad_probe_client import start_client_thread
from ros_nodes.pad_probe_publisher import start_bbox_publisher_thread

try:
    import pyds
except ImportError:
    sys.stderr.write("WARNING: Could not import pyds (DeepStream Python bindings)\n")

# --- ARDUINO CONFIGURATION --- 
ENABLE_ARDUINO = True
ARDUINO_PORT = "/dev/ttyACM0"
BAUD_RATE = 9600 # 115200
# Must also switch BAUD_RATE variable in the Arduino!

# --- ROS2 NODE CONFIGURATION ---
ENABLE_ROS = False 
ROS_MODE = "BBOX_PUBLISHER" # Options: "NAV_CLIENT" | "BBOX_PUBLISHER"

# --- CONFIGURATION --- 
OUTPUT_FILE_PATH = "test_output.mp4"
# CSV_FILE_PATH = "pad_probe_data.csv"

# --- VIDEO PATHS ---
# Test video 1
# VIDEO_1_PATH = "/opt/nvidia/deepstream/deepstream/samples/streams/sample_720p.mp4" 
# VIDEO_2_PATH = "/opt/nvidia/deepstream/deepstream/samples/streams/sample_720p.mp4" 

# Test video 2
current_dir = os.getcwd()
VIDEO_NAME = "test_video.mp4"
# This converts "./test_image.mp4" -> "/workspaces/.../test_image.mp4"
ABS_VIDEO_PATH = os.path.join(current_dir, "test-videos", VIDEO_NAME)

VIDEO_1_PATH = ABS_VIDEO_PATH 
VIDEO_2_PATH = ABS_VIDEO_PATH

# --- MODEL CONFIGS ---
PGIE_CONFIG = "config_infer_test.txt"

###### Change tracker 
TRACKER_TYPE = "NvDCF_accuracy"
TRACKER_CONFIG = "config_tracker_" + TRACKER_TYPE + ".yml"
TRACKER_LIB = "/opt/nvidia/deepstream/deepstream/lib/libnvds_nvmultiobjecttracker.so"
######

# --- OUTPUT FLAGS ---
LOG_DETECTIONS = False
ENABLE_DISPLAY = True
ENABLE_RECORD = True

# --- GLOBAL VARIABLES ---
main_loop = None
main_pipeline = None
arduino = None
ros_queue = queue.Queue(maxsize=100)

###### Eventually change this according to model!
class_map = {
    0: "Car",
    1: "Bicycle",
    2: "Person",
    3: "Roadsign"
}

# RGBA map for classes 
color_map = {
    0: (1.0, 0.0, 0.0, 1.0), # RED
    1: (0.0, 1.0, 0.0, 1.0), # GREEN
    2: (1.0, 1.0, 0.0, 1.0), # YELLOW
    3: (0.0, 0.0, 1.0, 1.0) # BLUE
}

#################################################

# value at index represents number of instances of the associated class
count_array_cam0 = [0] * len(class_map)
count_array_cam1 = [0] * len(class_map)

# For assigning object ID in order!
id_map_cam0 = {}
id_map_cam1 = {}
next_id_cam0 = 1
next_id_cam1 = 1

# --- PAD PROBE FUNCTION ---
# This function runs on EVERY Gst buffer that passes through the pad
def pad_probe(pad, info, u_data):
    global next_id_cam0, next_id_cam1, id_map_cam0, id_map_cam1, color_map, arduino

    gst_buffer = info.get_buffer()
    if not gst_buffer:
        print("Unable to get GstBuffer")
        return Gst.PadProbeReturn.OK

    # Get the Batch Metadata
    batch_meta = pyds.gst_buffer_get_nvds_batch_meta(hash(gst_buffer))
    
    # Iterate through frames in batch
    l_frame = batch_meta.frame_meta_list
    while l_frame is not None:
        try:
            frame_meta = pyds.NvDsFrameMeta.cast(l_frame.data)
        except StopIteration:
            break

        # Extract frame information
        frame_number = frame_meta.frame_num

        ### num_rects = frame_meta.num_obj_meta
        
        # This is the Camera ID (0 = source1, 1 = source2)
        # Eventually configure 0 = left camera and 1 = right camera
        camera_id = frame_meta.pad_index
        
        # Iterate through objects in this frame
        l_obj = frame_meta.obj_meta_list
        while l_obj is not None:
            try:
                obj_meta = pyds.NvDsObjectMeta.cast(l_obj.data)
            except StopIteration:
                break
            
            ##### EXTRACT BOUNDING BOX METADATA #####
            rect = obj_meta.rect_params
            top = rect.top
            left = rect.left
            width = rect.width
            height = rect.height
            #########################################
            
            obj_id = obj_meta.object_id
            class_id = obj_meta.class_id
            confidence = obj_meta.confidence

            ####### SET BOUNDING BOX VISUALS #######
            rect.border_width = 4
            color = color_map[class_id]

            rect.border_color.red = color[0]
            rect.border_color.green = color[1]
            rect.border_color.blue = color[2]
            rect.border_color.alpha = color[3]
            ########################################
            

            ##############################################################################
            new_obj_id = -1

            # Camera 0 (Left | ZED)
            if camera_id == 0:
                if obj_id not in id_map_cam0:
                    id_map_cam0[obj_id] = (next_id_cam0, class_id, frame_number)
                    
                    ####### SEND SIGNAL TO ARDUINO #######
                    if ENABLE_ARDUINO and arduino and arduino.is_open:
                        msg = f"{camera_id},{class_id},{int(left)},{int(top)}\n"
                        
                        try:
                            arduino.write(msg.encode('utf-8'))
                            print(f">> [ARDUINO TX]: {msg.strip()}")
                        except Exception as e:
                            print(f"Serial writeerror: {e}")
                    #######################################

                    ####### SEND TRIGGER TO ROS 2 #########
                    if ENABLE_ROS: 
                        if ROS_MODE == "NAV_CLIENT":
                            try:
                                ros_queue.put_nowait(True)
                            except queue.Full:
                                print("WARNING: ROS Queue full, dropping trigger!")
                        elif ROS_MODE == "BBOX_PUBLISHER":
                            try:
                                ros_queue.put_nowait({
                                    'top': top,
                                    'left': left,
                                    'width': width,
                                    'height': height,
                                })
                            except queue.Full:
                                print("WARNING: ROS Queue full, dropping trigger!")
                    #######################################

                    next_id_cam0 += 1

                new_obj_id = id_map_cam0[obj_id][0]

            # Camera 1 (Right | Arducam)
            elif camera_id == 1:
                if obj_id not in id_map_cam1:
                    id_map_cam1[obj_id] = (next_id_cam1, class_id, frame_number)

                    ####### SEND SIGNAL TO ARDUINO #######
                    if ENABLE_ARDUINO and arduino and arduino.is_open:
                        msg = f"{camera_id},{class_id},{int(left)},{int(top)}\n"
                        
                        try:
                            arduino.write(msg.encode('utf-8'))
                            print(f">> [ARDUINO TX]: {msg.strip()}")
                        except Exception as e:
                            print(f"Serial write error: {e}")
                    #######################################

                    ####### SEND TRIGGER TO ROS 2 #########
                    # Only send when left and right cameras connected
                    if ENABLE_ROS and ROS_MODE == "NAV_CLIENT":
                        try:
                            ros_queue.put_nowait(True)
                        except queue.Full:
                            print("WARNING: ROS Queue full, dropping trigger!")
                    #######################################

                    next_id_cam1 += 1

                new_obj_id = id_map_cam1[obj_id][0]
            ##############################################################################

            ### Possibly change this to display specific class name ###
            obj_meta.text_params.display_text = f"Object {new_obj_id}"
            
            # obj_meta.text_params.set_bg_clr = 1

            # obj_meta.text_params.text_bg_clr.red = color[0]
            # obj_meta.text_params.text_bg_clr.green = color[1]
            # obj_meta.text_params.text_bg_clr.blue = color[2]
            # obj_meta.text_params.text_bg_clr.alpha = color[3] * 0.6
            
            # # --- OVERWRITE CSV FILE FOR EACH PIPELINE RUN ---
            # try:
            #     with open(CSV_FILE_PATH, mode='a', newline='') as file:
            #         writer = csv.writer(file)
            #         # Format: Frame, Camera, ObjID, ClassID, Conf, Top, Left, Width, Height
            #         writer.writerow([
            #             frame_number, 
            #             camera_id, 
            #             obj_id, 
            #             class_id, 
            #             f"{confidence:.4f}", 
            #             f"{top:.2f}", 
            #             f"{left:.2f}", 
            #             f"{width:.2f}", 
            #             f"{height:.2f}",
            #         ])
            # except IOError as e:
            #     print(f"Error writing to CSV: {e}")
            
            if LOG_DETECTIONS:
                print(f"[Cam {camera_id}] Frame {frame_number}: Obj {obj_id} [Class {class_id}] [Conf={confidence:.2f}] "
                    f"| BBox: Top={top:.1f}, Left={left:.1f}, W={width:.1f}, H={height:.1f}")
            
            try:
                l_obj = l_obj.next
            except StopIteration:
                break

        try:
            l_frame = l_frame.next
        except StopIteration:
            break
            
    return Gst.PadProbeReturn.OK

def bus_call(bus, message, pipeline_loop_data):
    loop, pipeline = pipeline_loop_data
    t = message.type
    
    if t == Gst.MessageType.EOS:
        print("\n[GST] End of stream. Forcing Exit.")

        if ENABLE_ARDUINO and arduino and arduino.is_open:
            arduino.close()

        total_obj_count_cam_0 = len(id_map_cam0)
        total_obj_count_cam_1 = len(id_map_cam1)
        print(f"Total Count (Cam 0: {total_obj_count_cam_0} | Cam 1: {total_obj_count_cam_1})")

        ### Prints count for each class ###
        for value in id_map_cam0.values():
            count_array_cam0[value[1]] += 1
        
        for value in id_map_cam1.values():
            count_array_cam1[value[1]] += 1

        for key in class_map:
            print(f"Count of {class_map[key]}s: {count_array_cam0[key]} | {count_array_cam1[key]}")
        ####################################

        os._exit(0)
        
    elif t == Gst.MessageType.ERROR:
        err, debug = message.parse_error()
        sys.stderr.write("Error: %s: %s\n" % (err, debug))
        os._exit(1)
        
    elif t == Gst.MessageType.WARNING:
        # Ignore audio warnings since we are doing video only
        err, debug = message.parse_warning()
        # Only print if it's not the known audio decoder warning
        if "audio/mpeg" not in str(err):
            sys.stderr.write("Warning: %s: %s\n" % (err, debug))
            
    return True

def callback_newpad(decodebin, decoder_src_pad, streammux_sink_pad):
    print("[GST] In callback_newpad")
    caps = decoder_src_pad.get_current_caps()
    gststruct = caps.get_structure(0)
    gstname = gststruct.get_name()
    if (gstname.find("video") != -1):
        if not streammux_sink_pad.is_linked():
            decoder_src_pad.link(streammux_sink_pad)
        print("[GST] Linked decodebin pad to nvstreammux")

def main():
    global main_loop, main_pipeline, arduino
    
    Gst.init(None)

    # --- BOOT UP ROS 2 BACKGROUND CLIENT THREAD ---
    if ENABLE_ROS:
        print("\n" + "="*60)
        print("[INIT] ROS 2 Initialization")
        print("="*60)
        print(f"Mode: {ROS_MODE}")

        if ROS_MODE == "NAV_CLIENT":
            ros_thread = threading.Thread(target=start_client_thread, args=(ros_queue,), daemon=True)
            ros_thread.start()
        elif ROS_MODE == "BBOX_PUBLISHER":
            ros_thread = threading.Thread(target=start_bbox_publisher_thread, args=(ros_queue,), daemon=True)
            ros_thread.start()
        else:
            raise Exception("ROS_MODE invalid")
        
        print("✓ ROS background thread started")
        print("="*60 + "\n")


    if ENABLE_ARDUINO:
        print("\n" + "="*60)
        print("[INIT] Arduino Initialization")
        print("="*60)
        print(f"Opening serial port: {ARDUINO_PORT} @ {BAUD_RATE} baud")
        try:
            arduino = serial.Serial(ARDUINO_PORT, BAUD_RATE, timeout=0.1)
            time.sleep(2)
            print("✓ Arduino successfully connected!")
            print("="*60 + "\n")
        except Exception as e:
            print(f"✗ Arduino connection failed: {e}")
            print("Continuing pipeline without Arduino...")
            print("="*60 + "\n")
            arduino = None

    if not ENABLE_DISPLAY and not ENABLE_RECORD:
        sys.stderr.write("ERROR: Both Display and Record are disabled. The pipeline has no destination!\n")
        sys.exit(1)

    # print("\n" + "="*60)
    # print("[INIT] CSV Initialization")
    # print("="*60)
    
    # try:
    #     with open(CSV_FILE_PATH, mode='w', newline='') as file:
    #         writer = csv.writer(file)
    #         writer.writerow(["Frame", "Camera", "ObjID", "ClassID", "Conf", "Top", "Left", "Width", "Height"])
    #     print(f"✓ CSV initialized: {CSV_FILE_PATH}\n")
    # except IOError as e:
    #     print(f"✗ CSV creation failed: {e}\n")
    #     sys.exit(1)

    print("\n" + "="*60)
    print("[GST] Creating Pipeline")
    print("="*60 + "\n")
    
    pipeline = Gst.Pipeline()
    main_pipeline = pipeline

    # --- 1. SOURCES & MUX ---
    source1 = Gst.ElementFactory.make("uridecodebin", "source1")
    source1.set_property("uri", "file://" + VIDEO_1_PATH)
    source2 = Gst.ElementFactory.make("uridecodebin", "source2")
    source2.set_property("uri", "file://" + VIDEO_2_PATH)

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

    # Check Elements
    elements = [pipeline, source1, source2, streammux, convert1, inference, tracker, convert2, tiler, nvosd, tee]
    
    # --- BRANCH A: LIVE DISPLAY ---
    if ENABLE_DISPLAY:
        queue_display = Gst.ElementFactory.make("queue", "queue_display")
        convert3 = Gst.ElementFactory.make("nvvideoconvert", "convert3")
        caps_filter = Gst.ElementFactory.make("capsfilter", "caps_filter")
        caps = Gst.Caps.from_string("video/x-raw, format=(string)I420")
        caps_filter.set_property("caps", caps)
        sink_display = Gst.ElementFactory.make("xvimagesink", "sink_display")
    
        # CRITICAL SETTINGS FOR DISPLAY STABILITY
        sink_display.set_property("sync", 0) # May switch to 1
        sink_display.set_property("qos", 0)

        branch_elements = [queue_display, convert3, caps_filter, sink_display]
        elements.extend(branch_elements)

    # --- BRANCH B: FILE SAVE ---
    if ENABLE_RECORD:
        queue_record = Gst.ElementFactory.make("queue", "queue_record")
        convert_record = Gst.ElementFactory.make("nvvideoconvert", "convert_record")
        encoder = Gst.ElementFactory.make("nvv4l2h264enc", "encoder")
        parser = Gst.ElementFactory.make("h264parse", "parser")
        qtmux = Gst.ElementFactory.make("qtmux", "qtmux")
        sink_record = Gst.ElementFactory.make("filesink", "sink_record")
        sink_record.set_property("location", OUTPUT_FILE_PATH)
        sink_record.set_property("sync", 0) 

        branch_elements = [queue_record, convert_record, encoder, parser, qtmux, sink_record]
        elements.extend(branch_elements);

        
    if not all(elements):
        sys.stderr.write("One or more elements could not be created. Exiting.\n")
        sys.exit(1)
    
    # --- CONFIGURE PROPERTIES ---
    WIDTH = 1920
    HEIGHT = 1080

    streammux.set_property("width", WIDTH)
    streammux.set_property("height", HEIGHT)
    streammux.set_property("batch-size", 2)
    streammux.set_property("batched-push-timeout", 40000)

    inference.set_property("config-file-path", PGIE_CONFIG)

    tracker.set_property("ll-config-file", TRACKER_CONFIG)
    tracker.set_property("ll-lib-file", TRACKER_LIB)
    tracker.set_property("tracker-width", 640)
    tracker.set_property("tracker-height", 384)

    nvosd.set_property('display-clock', 1)
    nvosd.set_property('display-text', 1)

    tiler.set_property("rows", 1)
    tiler.set_property("columns", 2)
    tiler.set_property("width", WIDTH)
    tiler.set_property("height", HEIGHT)

    # Add elements to pipeline
    for elem in elements:
        if elem is not pipeline:
            pipeline.add(elem)

    # --- LINKING ---
    print("\n" + "="*60)
    print("[GST] Linking Elements")
    print("="*60 + "\n")
    
    # 1. Main Trunk
    streammux.link(convert1)
    convert1.link(inference)
    inference.link(tracker)
    tracker.link(convert2)
    convert2.link(tiler)
    tiler.link(nvosd)
    nvosd.link(tee) 

    # 2. Branch A (Display)
    if ENABLE_DISPLAY:
        tee_pad_display = tee.get_request_pad('src_%u')
        queue_pad_display = queue_display.get_static_pad('sink')
        tee_pad_display.link(queue_pad_display)

        queue_display.link(convert3)
        convert3.link(caps_filter)
        caps_filter.link(sink_display)

    # 3. Branch B (Recording)
    if ENABLE_RECORD:
        tee_pad_record = tee.get_request_pad('src_%u')
        queue_pad_record = queue_record.get_static_pad('sink')
        tee_pad_record.link(queue_pad_record)

        queue_record.link(convert_record)
        convert_record.link(encoder)
        encoder.link(parser)
        parser.link(qtmux)
        qtmux.link(sink_record)

    # We want to probe AFTER the tracker. The tracker connects to 'convert2'.
    # So we attach the probe to the SINK pad of 'convert2'.
    convert2_sink_pad = convert2.get_static_pad("sink")
    if not convert2_sink_pad:
        sys.stderr.write("Unable to get sink pad of convert2 \n")
    else:
        convert2_sink_pad.add_probe(Gst.PadProbeType.BUFFER, pad_probe, 0)

    # Source Pads
    sinkpad1 = streammux.get_request_pad("sink_0")
    sinkpad2 = streammux.get_request_pad("sink_1")
    source1.connect("pad-added", callback_newpad, sinkpad1)
    source2.connect("pad-added", callback_newpad, sinkpad2)

    # Start loop
    loop = GLib.MainLoop()
    main_loop = loop
    bus = pipeline.get_bus()
    bus.add_signal_watch()
    bus.connect("message", bus_call, (loop, pipeline))

    print(f"\n" + "="*60)
    print(f"[GST] Starting Pipeline")
    print(f"      Display: {ENABLE_DISPLAY} | Recording: {ENABLE_RECORD} | Output: {OUTPUT_FILE_PATH}")
    print(f"="*60 + "\n")
    
    pipeline.set_state(Gst.State.PLAYING)

    try:
        loop.run()
    except Exception as e:
        print(f"Error: {e}")
    
    # This part will likely never be reached because os._exit kills it first
    print("[GST] Exiting\n")
    pipeline.set_state(Gst.State.NULL)
    return 0

if __name__ == '__main__':
    main()