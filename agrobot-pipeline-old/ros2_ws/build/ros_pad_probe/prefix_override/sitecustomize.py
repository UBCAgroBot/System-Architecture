import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/workspaces/daniels-wonderland/agrobot-pipeline/ros2_ws/install/ros_pad_probe'
