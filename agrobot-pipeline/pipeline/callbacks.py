import os
import sys
from gi.repository import Gst
from config import class_map, LOG_STATS_EOS
from probe.fps import get_fps_summary
from probe.latency import get_latency_summary, get_probe_time_summary
from probe.pad_probe import id_map_cam0, id_map_cam1, count_array_cam0, count_array_cam1

main_pipeline = None

def bus_call(bus, message, pipeline_loop_data):
    loop, pipeline = pipeline_loop_data
    t = message.type

    if t == Gst.MessageType.EOS:
        print("[GST] End of stream. Forcing Exit.\n")
        print_detection_summary()
        if LOG_STATS_EOS:
            print_stats_summary()
        os._exit(0)

    elif t == Gst.MessageType.ERROR:
        err, debug = message.parse_error()

        if message.src.get_name() == "zedsrc":
            sys.stderr.write("="*60 + "\n")
            sys.stderr.write("ZED Camera failed to start!\n")
            sys.stderr.write(f"Reason: {err}\n")
            sys.stderr.write(f"Debug: {debug}\n")
            sys.stderr.write("="*60 + "\n\n")
        else:
            sys.stderr.write(f"Error: {err}: {debug}\n")
        os._exit(1)

    elif t == Gst.MessageType.WARNING:
        err, debug = message.parse_warning()
        if "audio/mpeg" not in str(err):
            sys.stderr.write(f"Warning: {err}: {debug}\n")

    return True

def callback_newpad(decodebin, decoder_src_pad, streammux_sink_pad):
    print("[GST] In callback_newpad")
    caps = decoder_src_pad.get_current_caps()
    gststruct = caps.get_structure(0)
    gstname = gststruct.get_name()
    if (gstname.find("video") != -1):
        if not streammux_sink_pad.is_linked():
            decoder_src_pad.link(streammux_sink_pad)
        print("[GST] Linked decodebin pad to nvstreammux\n")

def handle_exit_signal(sig, frame):
    print("[GST] Ctrl+C received, sending EOS...\n")
    if main_pipeline:
        main_pipeline.send_event(Gst.Event.new_eos())

def print_detection_summary():
    print("="*60)
    print("[DETECTION SUMMARY]")
    print("="*60 + "\n")
    print(f"Total Count (Cam 0: {len(id_map_cam0)} | Cam 1: {len(id_map_cam1)})\n")
    for value in id_map_cam0.values():
        count_array_cam0[value[1]] += 1
    for value in id_map_cam1.values():
        count_array_cam1[value[1]] += 1
    for key in class_map:
        print(f"Count of {class_map[key]}s: {count_array_cam0[key]} | {count_array_cam1[key]}")
    
    print("="*60 + "\n")

def print_stats_summary():
    print("="*60)
    print("[STATS SUMMARY]")
    print("="*60 + "\n")

    fps_summary = get_fps_summary()
    if fps_summary:
        print("[FPS]")
        for cam_id, stats in fps_summary.items():
            print(f"  Cam {cam_id}: avg={stats['avg']:.1f} fps | "
                  f"{stats['total_frames']} frames over {stats['total_seconds']:.1f}s")
    else:
        print("[FPS] No data collected")

    latency_summary = get_latency_summary()
    if latency_summary:
        print("[PIPELINE LATENCY]")
        for cam_id, stats in latency_summary.items():
            print(f"  Cam {cam_id}: avg={stats['avg']:.1f}ms | "
                  f"min={stats['min']:.1f}ms | max={stats['max']:.1f}ms "
                  f"({stats['count']} frames)")
    else:
        print("[PIPELINE LATENCY] No data collected")

    probe_summary = get_probe_time_summary()
    if probe_summary:
        print("[PROBE TIME]")
        print(f"  avg={probe_summary['avg']:.2f}ms | "
              f"min={probe_summary['min']:.2f}ms | max={probe_summary['max']:.2f}ms "
              f"({probe_summary['count']} frames)")
    else:
        print("[PROBE TIME] No data collected")

    print("="*60 + "\n")