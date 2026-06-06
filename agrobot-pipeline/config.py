import os

######################################################
####################### FLAGS ########################
######################################################

# --- CAMERA INPUT ---
ENABLE_CAMERAS = True # If false, must provide video source
CAMERA_TYPE = "ZED" # Options: "ZED" | "ARDUCAM" 
NUM_OF_INPUTS = 2 # Options: 1 | 2

# --- ARDUINO --- 
ENABLE_ARDUINO = True

# --- ROS2 NODE ---
ENABLE_ROS = False 
ROS_MODE = "BBOX_PUBLISHER" # Options: "NAV_CLIENT" | "BBOX_PUBLISHER"

# --- OUTPUT OPTIONS ---
ENABLE_DISPLAY = True
ENABLE_RECORD = False

# --- LOGGING FLAGS ---
LOG_DETECTIONS = False
LOG_STATS_DURING_STREAM = True
LOG_STATS_EOS = True

SAVE_TERMINAL_LOGS = True

# --- LOGGING STATS ---
FPS_ELAPSED_TIME = 5.0 # How frequently FPS is logged
MAX_LATENCY_SAMPLES = 200 # How frequently latency is logged

# --- OUTPUT FILE PATHS --- 
OUTPUT_VIDEO = "outputs/test_output.mp4"
OUTPUT_LOCATION_DATA = "outputs/detections.csv"
TERMINAL_LOG_FILE = "outputs/terminal_log"

######################################################
###################### CONFIGS #######################
######################################################

# --- ARDUINO CONNECTION CONFIG ---
ARDUINO_PORT = "/dev/ttyACM0"
BAUD_RATE = 9600 # 115200
# Must also switch BAUD_RATE variable in the Arduino!

# --- MODEL CONFIG FILES ---
BASE_DIR = os.path.dirname(os.path.abspath(__file__))

PGIE_CONFIG = os.path.join(BASE_DIR, "model_config", "config_infer_test.txt")

TRACKER_TYPE = "NvDCF_accuracy"
TRACKER_CONFIG = os.path.join(BASE_DIR, "model_config", "config_tracker_" + TRACKER_TYPE + ".yml")
TRACKER_LIB = "/opt/nvidia/deepstream/deepstream/lib/libnvds_nvmultiobjecttracker.so"

# --- VIDEO RESOLUTION ---
WIDTH = 1920
HEIGHT = 1080
# Have separate for nvstreammux and tiler

# --- CLASSES --- 
#### Eventually change this according to model!
class_map = {
    0: "Car",
    1: "Bicycle",
    2: "Person",
    3: "Roadsign"
}

# RGBA color map for classes 
color_map = {
    0: (1.0, 0.0, 0.0, 1.0), # RED
    1: (1.0, 1.0, 0.0, 1.0), # YELLOW
    2: (0.0, 1.0, 0.0, 1.0), # GREEN
    3: (0.0, 0.0, 1.0, 1.0) # BLUE
}

# --- INPUT VIDEOS (for testing) ---
if not ENABLE_CAMERAS:
    NUM_OF_INPUTS = 2

    current_dir = os.getcwd()
    VIDEO_NAME = "test_video.mp4"
    ABS_VIDEO_PATH = os.path.join(current_dir, "test-videos", VIDEO_NAME)

    VIDEO_1_PATH = ABS_VIDEO_PATH 
    VIDEO_2_PATH = ABS_VIDEO_PATH