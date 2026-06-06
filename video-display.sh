#!/bin/bash

xhost +si:localuser:root

 docker run -it --rm \
  --runtime nvidia \
  --gpus all \
  --network=host \
  --ipc=host \
  -v ~/Downloads:/daniels-wonderland \
  -w /daniels-wonderland \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -e DISPLAY=$DISPLAY \
  -e NVIDIA_VISIBLE_DEVICES=all \
  -e NVIDIA_DRIVER_CAPABILITIES=all \
  nvcr.io/nvidia/deepstream:7.0-triton-multiarch