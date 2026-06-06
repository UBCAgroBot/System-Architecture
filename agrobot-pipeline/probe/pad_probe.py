import queue
import time
from gi.repository import Gst
from config import (
    ENABLE_ARDUINO, ENABLE_ROS, LOG_DETECTIONS, LOG_STATS_DURING_STREAM, LOG_STATS_EOS,
    ROS_MODE, color_map, class_map,
    FPS_ELAPSED_TIME, MAX_LATENCY_SAMPLES
)
from probe.latency import calculate_latency, log_latency, log_probe_time, log_latency_total, log_probe_time_total
from probe.fps import log_fps, log_fps_total
from hardware.arduino import send_arduino

try:
    import pyds
except ImportError:
    import sys
    sys.stderr.write("WARNING: Could not import pyds\n")

# State
id_map_cam0 = {}
id_map_cam1 = {}
next_id_cam0 = 1
next_id_cam1 = 1
count_array_cam0 = [0] * len(class_map)
count_array_cam1 = [0] * len(class_map)

def pad_probe(pad, info, u_data):
    global next_id_cam0, next_id_cam1

    if LOG_STATS_EOS or LOG_STATS_DURING_STREAM:
        probe_start = time.perf_counter() # For logging

    arduino = u_data.get("arduino")
    ros_queue = u_data.get("ros_queue")

    gst_buffer = info.get_buffer()
    if not gst_buffer:
        print("Unable to get GstBuffer")
        return Gst.PadProbeReturn.OK

    batch_meta = pyds.gst_buffer_get_nvds_batch_meta(hash(gst_buffer))
    l_frame = batch_meta.frame_meta_list

    while l_frame is not None:
        try:
            frame_meta = pyds.NvDsFrameMeta.cast(l_frame.data)
        except StopIteration:
            break

        frame_number = frame_meta.frame_num
        camera_id = frame_meta.pad_index

        if LOG_STATS_EOS or LOG_STATS_DURING_STREAM:
            latency = calculate_latency(frame_meta)
            if LOG_STATS_DURING_STREAM:
                log_fps(camera_id, FPS_ELAPSED_TIME)
                log_latency(camera_id, latency, MAX_LATENCY_SAMPLES)
            if LOG_STATS_EOS:
                log_fps_total(camera_id)
                log_latency_total(camera_id, latency)

        l_obj = frame_meta.obj_meta_list
        while l_obj is not None:
            try:
                obj_meta = pyds.NvDsObjectMeta.cast(l_obj.data)
            except StopIteration:
                break
            
            #########################################
            ##### EXTRACT BOUNDING BOX METADATA #####
            #########################################
            rect = obj_meta.rect_params
            top, left, width, height = rect.top, rect.left, rect.width, rect.height
            obj_id = obj_meta.object_id
            class_id = obj_meta.class_id
            confidence = obj_meta.confidence
            #########################################
            #########################################
            #########################################

            # Bounding box visuals
            rect.border_width = 4
            color = color_map[class_id]
            rect.border_color.red = color[0]
            rect.border_color.green = color[1]
            rect.border_color.blue = color[2]
            rect.border_color.alpha = color[3]

            new_obj_id = -1

            #####################################################
            ################## Camera 0 | LEFT ##################
            #####################################################
            if camera_id == 0:
                if obj_id not in id_map_cam0:
                    id_map_cam0[obj_id] = (next_id_cam0, class_id, frame_number)
                    if ENABLE_ARDUINO:
                        send_arduino(arduino, camera_id, class_id, left, top)
                    if ENABLE_ROS and ros_queue:
                        send_ros(ros_queue, top, left, width, height)
                    next_id_cam0 += 1
                new_obj_id = id_map_cam0[obj_id][0]


            #####################################################
            ################# Camera 1 | RIGHT  #################
            #####################################################
            elif camera_id == 1:
                if obj_id not in id_map_cam1:
                    id_map_cam1[obj_id] = (next_id_cam1, class_id, frame_number)
                    if ENABLE_ARDUINO:
                        send_arduino(arduino, camera_id, class_id, left, top)
                    # Only send when requesting location data from Nav team
                    if ENABLE_ROS and ROS_MODE == "NAV_CLIENT" and ros_queue:
                        send_ros(ros_queue, top, left, width, height)
                    next_id_cam1 += 1
                new_obj_id = id_map_cam1[obj_id][0]

            obj_meta.text_params.display_text = f"Object {new_obj_id}"

            if LOG_DETECTIONS:
                print(f"[Cam {camera_id}] Frame {frame_number}: Obj {obj_id} "
                      f"[Class {class_id}] [Conf={confidence:.2f}] "
                      f"| BBox: Top={top:.1f}, Left={left:.1f}, W={width:.1f}, H={height:.1f}")

            try:
                l_obj = l_obj.next
            except StopIteration:
                break

        try:
            l_frame = l_frame.next
        except StopIteration:
            break
    
    if LOG_STATS_EOS or LOG_STATS_DURING_STREAM:
        probe_duration_ms = (time.perf_counter() - probe_start) * 1000
        if LOG_STATS_DURING_STREAM:
            log_probe_time(probe_duration_ms, MAX_LATENCY_SAMPLES)
        if LOG_STATS_EOS:
            log_probe_time_total(probe_duration_ms)

    return Gst.PadProbeReturn.OK

def send_ros(ros_queue : queue.Queue, top, left, width, height):
    try:
        if ROS_MODE == "BBOX_PUBLISHER":
            ros_queue.put_nowait({'top': top, 'left': left, 'width': width, 'height': height})
        else:
            ros_queue.put_nowait(True)
            
    except queue.Full:
        print("WARNING: ROS Queue full, dropping trigger!")