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

## To edit nvtracker config file:
```bash
nano /opt/nvidia/deepstream/deepstream/samples/configs/deepstream-app/config_tracker_NvDCF_accuracy.yml
```

# TO START PIPELINE:
`python3 video-pipeline.py`