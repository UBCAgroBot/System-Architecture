import time

# Periodic logging
latency_data = {} # camera_id : [measurements]
probe_times = []

# EOS logging
latency_all = {}
probe_times_all = []

# --- Calculate latency from camera source to pad_probe ---
def calculate_latency(frame_meta):
    probe_time_ns = time.time_ns() # Time now
    capture_time_ns = frame_meta.ntp_timestamp # ZED SDK capture timestamp

    if capture_time_ns > 0:
        latency_ms = (probe_time_ns - capture_time_ns) / 1_000_000
        return latency_ms
    return None

# --- Periodically log latency from camera source to pad_probe ---
def log_latency(camera_id, latency_ms, max_samples):
    if latency_ms is None or not (0 < latency_ms < 10000):
        return

    if camera_id not in latency_data:
        latency_data[camera_id] = []

    latency_data[camera_id].append(latency_ms)

    if len(latency_data[camera_id]) >= max_samples:
        measurements = latency_data[camera_id]
        avg = sum(measurements) / len(measurements)
        min_l = min(measurements)
        max_l = max(measurements)
        print("-"*40)
        print(f"[LATENCY Cam {camera_id}] avg={avg:.1f}ms | min={min_l:.1f}ms | max={max_l:.1f}ms (over {max_samples} frames)")
        print("-"*40)
        latency_data[camera_id] = []

# --- Track latency from camera source to pad_probe for EOS logging ---
def log_latency_total(camera_id, latency_ms):
    if latency_ms is None or not (0 < latency_ms < 10000):
        return
    if camera_id not in latency_all:
        latency_all[camera_id] = []
    latency_all[camera_id].append(latency_ms)


# --- Calculate and log latency within pad_probe ---
def log_probe_time(duration_ms, max_samples):
    probe_times.append(duration_ms)
    if len(probe_times) >= max_samples:
        avg = sum(probe_times) / len(probe_times)
        max_t = max(probe_times)
        print("-"*40)
        print(f"[PROBE TIME] avg={avg:.2f}ms | max={max_t:.2f}ms (over {max_samples} frames)")
        print("-"*40)
        probe_times.clear()

# --- Track latency within pad_probe for EOS logging ---
def log_probe_time_total(duration_ms):
    probe_times_all.append(duration_ms)


# --- Get summary for latency stats from camera source to pad_probe ---
def get_latency_summary():
    summary = {}
    for cam_id, measurements in latency_all.items():
        if measurements:
            summary[cam_id] = {
                'avg': sum(measurements) / len(measurements),
                'min': min(measurements),
                'max': max(measurements),
                'count': len(measurements),
            }
    return summary

# --- Get summary for latency stats within pad_probe ---
def get_probe_time_summary():
    if probe_times_all:
        return {
            'avg': sum(probe_times_all) / len(probe_times_all),
            'min': min(probe_times_all),
            'max': max(probe_times_all),
            'count': len(probe_times_all),
        }
    return None