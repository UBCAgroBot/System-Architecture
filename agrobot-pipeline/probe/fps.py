import time

# Periodic logging
fps_data = {} # camera_id : {start time, count}

# EOS logging
fps_totals = {} # camera_id : {start time, total}

def log_fps(camera_id, elapsed_time):
    if camera_id not in fps_data:
        fps_data[camera_id] = {'start': time.time(), 'count': 0}
    
    fps_data[camera_id]['count'] += 1
    elapsed = time.time() - fps_data[camera_id]['start']
    
    if elapsed >= elapsed_time:
        fps = fps_data[camera_id]['count'] / elapsed
        print("-"*40)
        print(f"[FPS Cam {camera_id}] {fps:.1f}")
        print("-"*40)
        fps_data[camera_id] = {'start': time.time(), 'count': 0}


def log_fps_total(camera_id):
    if camera_id not in fps_totals:
        fps_totals[camera_id] = {'start': time.time(), 'total': 0}    
    fps_totals[camera_id]['total'] += 1


def get_fps_summary():
    summary = {}
    for cam_id, data in fps_totals.items():
        elapsed = time.time() - data['start']
        if elapsed > 0 and data['total'] > 0:
            summary[cam_id] = {
                'avg': data['total'] / elapsed,
                'total_frames': data['total'],
                'total_seconds': elapsed,
            }
    return summary