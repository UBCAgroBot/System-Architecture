## Build Docker Image and Start Docker Container

```bash
docker buildx build -t agrobotappliedai/deepstream-dev:latest -f Deepstream-Dev.Dockerfile . --network=host
docker run -it --rm --net=host agrobotappliedai/deepstream-dev:latest
```

## For live display on NoMachine:

Run in terminal on NoMachine:
```bash
export DISPLAY=:1001
xhost +
```

```source install/setup.bash```

## For serial connection to Arduino:

Make sure to connect the Arduino **BEFORE** building container!

## To look at GStreamer element properties:

```bash
gst-inspect-1.0 
```

# TO START PIPELINE:
```bash 
python3 video-pipeline.py
```

# PROJECT STRUCTURE:

daniels-wonderland/
└── agrobot-pipeline/
    ├── config.py
    ├── main.py
    ├── README.md
    ├── hardware/
    │   ├── __init__.py
    │   └── arduino.py
    ├── pipeline/
    │   ├── __init__.py
    │   └── callbacks.py
    ├── probe/
    │   ├── __init__.py
    │   ├── fps.py
    │   ├── latency.py
    │   └── pad_probe.py
    ├── ros_nodes/
    │   ├── __init__.py
    │   ├── mock_nav_server.py
    │   ├── mock_nav_subscriber.py
    │   ├── pad_probe_client.py
    │   └── pad_probe_publisher.py
    ├── ros2_ws/
    │   └── src/
    │       ├── agrobot_msgs/
    │       │   ├── CMakeLists.txt
    │       │   ├── package.xml
    │       │   └── msg/
    │       │       └── Detection.msg
    │       └── ros_pad_probe/
    │           ├── package.xml
    │           ├── setup.py
    │           ├── setup.cfg
    │           ├── resource/
    │           │   └── ros_pad_probe
    │           └── test/
    │               ├── test_copyright.py
    │               ├── test_flake8.py
    │               └── test_pep257.py
    ├── model_config/
    │   ├── config_infer_test.txt
    │   └── config_tracker_NvDCF_accuracy.yml
    ├── models/
    │   ├── best.onnx
    │   ├── best.onnx_b1_gpu0_fp16.engine
    │   ├── best.onnx.data
    │   ├── best.pt
    │   ├── export_model.py
    │   ├── labels.txt
    │   ├── resnet10.caffemodel
    │   ├── resnet10.caffemodel_b2_gpu0_fp16.engine
    │   └── resnet10.prototxt
    ├── outputs/
    │   ├── detections.csv
    │   └── test_output.mp4
    └── test-videos/
        ├── test_video.mp4
        ├── test_video2.mp4
        ├── test_video3.MP4
        └── test_video4.mp4