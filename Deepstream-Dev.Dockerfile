FROM nvcr.io/nvidia/deepstream:7.0-triton-multiarch

ENV DEBIAN_FRONTEND=noninteractive
ENV NVIDIA_VISIBLE_DEVICES=all
ENV NVIDIA_DRIVER_CAPABILITIES=all,compute,video,graphics,utility

# --- SYSTEM DEPENDENCIES ---
RUN apt update && apt install -y --no-install-recommends ca-certificates curl build-essential pkg-config libssl-dev libxtensor-dev plocate libeigen3-dev libgtest-dev sudo kmod
RUN apt install -y gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-plugins-good libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev && rm -rf /var/lib/apt/lists/*

# --- OPENCV ---
RUN apt update && apt install -y cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev libtbb2 
RUN mkdir /tmp/workspace
WORKDIR /tmp/workspace
RUN curl -L https://github.com/opencv/opencv/archive/4.10.0.zip -o opencv-4.10.0.zip && unzip opencv-4.10.0.zip && rm opencv-4.10.0.zip
RUN curl -L https://github.com/opencv/opencv_contrib/archive/4.10.0.zip -o opencv_contrib-4.10.0.zip && unzip opencv_contrib-4.10.0.zip && rm opencv_contrib-4.10.0.zip
RUN cd opencv-4.10.0/ && mkdir release && cd release/
WORKDIR /tmp/workspace/opencv-4.10.0/release/
RUN cmake -D WITH_CUDA=ON -D WITH_CUDNN=ON -D CUDA_ARCH_BIN="8.7" -D CUDA_ARCH_PTX="" \
          -D OPENCV_GENERATE_PKGCONFIG=ON -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib-4.10.0/modules \
          -D WITH_GSTREAMER=ON -D WITH_LIBV4L=ON -D BUILD_opencv_python3=OFF -D BUILD_TESTS=OFF \
          -D BUILD_PERF_TESTS=OFF -D BUILD_EXAMPLES=OFF -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
RUN make -j$(nproc) && make install

# --- RIDGERUN GSTREAMER PLUGINS ---
WORKDIR /tmp/workspace
RUN git clone https://github.com/RidgeRun/gst-interpipe.git
RUN apt install -y libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev gtk-doc-tools 
WORKDIR /tmp/workspace/gst-interpipe
RUN ./autogen.sh --libdir /usr/lib/$(uname -m)-linux-gnu/ && make && make check && make install
WORKDIR /tmp/workspace
RUN git clone https://github.com/RidgeRun/gst-perf.git
WORKDIR /tmp/workspace/gst-perf
RUN ./autogen.sh && ./configure --prefix /usr/ --libdir /usr/lib/$(uname -m)-linux-gnu/ && make && make install

# --- ZED SDK 5.2 (JetPack 6.0 GA / L4T 36.3) ---
RUN apt-get update && apt-get install -y --no-install-recommends zstd wget \
    && wget -q https://download.stereolabs.com/zedsdk/5.2/l4t36.3/jetsons \
       -O /tmp/ZED_SDK_v5.2_L4T36.3.zstd.run \
    && chmod +x /tmp/ZED_SDK_v5.2_L4T36.3.zstd.run \
    && /tmp/ZED_SDK_v5.2_L4T36.3.zstd.run -- silent skip_tools skip_hub \
    && rm /tmp/ZED_SDK_v5.2_L4T36.3.zstd.run \
    && rm -rf /var/lib/apt/lists/*

# --- ZED GStreamer Plugin ---
RUN apt-get update && apt-get install -y --no-install-recommends \
    libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev \
    libgstrtspserver-1.0-dev \
    && git clone https://github.com/stereolabs/zed-gstreamer.git /tmp/zed-gstreamer \
    && cd /tmp/zed-gstreamer && mkdir build && cd build \
    && cmake -DCMAKE_BUILD_TYPE=Release \
             -DCUDA_CUDA_LIBRARY=/usr/local/cuda/lib64/stubs/libcuda.so \
    .. \
    && make \
    && make install \
    && rm -rf /tmp/zed-gstreamer \
    && rm -rf /var/lib/apt/lists/*

# --- DEEPSTREAM ENVIRONMENT VARIABLES ---
ENV DS=/opt/nvidia/deepstream/deepstream-7.0
ENV LD_LIBRARY_PATH="$DS/lib:/usr/local/cuda/compat:/usr/local/cuda/lib64:/usr/lib/aarch64-linux-gnu:${LD_LIBRARY_PATH:-}"
ENV GST_PLUGIN_PATH="/usr/lib/aarch64-linux-gnu/gstreamer-1.0/deepstream:/usr/local/lib/aarch64-linux-gnu/gstreamer-1.0:/usr/local/lib/gstreamer-1.0"
RUN rm -f ~/.cache/gstreamer-1.0/registry.*
ENV GST_REGISTRY_REUSE_PLUGIN_SCANNER=0

# --- GLOBAL PYTHON DEPENDENCIES ---
RUN apt install -y python3-pip python3-gi gir1.2-gstreamer-1.0
WORKDIR /tmp
RUN wget https://github.com/NVIDIA-AI-IOT/deepstream_python_apps/releases/download/v1.1.11/pyds-1.1.11-py3-none-linux_aarch64.whl
RUN pip3 install --break-system-packages opencv-contrib-python pyyaml scipy pyds-1.1.11-py3-none-linux_aarch64.whl pyserial

# --- ROS 2 HUMBLE CORE INSTALLATION (NO SCRIPTS) ---
# 1. Set Locale
RUN apt update && apt install -y locales && locale-gen en_US en_US.UTF-8 && update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
ENV LANG=en_US.UTF-8

# 2. Add ROS 2 apt repository keys
RUN apt update && apt install -y software-properties-common curl \
    && add-apt-repository universe \
    && curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg \
    && echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null

# 3. Install ROS 2 Base and Colcon build tools
RUN apt update && apt install -y ros-humble-ros-base python3-colcon-common-extensions

# --- USER & PERMISSIONS SETUP ---
RUN echo "Defaults !fqdn" >> /etc/sudoers

ARG USERNAME=vscode
ARG USER_UID=1001
ARG USER_GID=$USER_UID
RUN groupadd --gid $USER_GID $USERNAME 2>/dev/null || true \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME --shell /bin/bash 2>/dev/null || true \
    && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

RUN usermod -aG dialout,video ${USERNAME}

USER $USERNAME
WORKDIR /home/$USERNAME

# --- WORKSPACE SOURCING ---
RUN mkdir -p /home/$USERNAME/workspace
RUN echo "source /opt/ros/humble/setup.bash" >> /home/$USERNAME/.bashrc
RUN echo "source /workspaces/daniels-wonderland/agrobot-pipeline/ros2_ws/install/setup.bash" >> /home/$USERNAME/.bashrc
RUN echo "export DISPLAY=:1001" >> /home/$USERNAME/.bashrc

ENV PYTHONWARNINGS="ignore"
RUN sudo updatedb

WORKDIR /home/$USERNAME/workspace
ENTRYPOINT ["/bin/bash"]