FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04

ENV __GLX_VENDOR_LIBRARY_NAME=nvidia

RUN apt-get update && apt-get install -y --no-install-recommends \
      build-essential cmake git \
      libgl1-mesa-dev         \
      libvulkan-dev           \
      vulkan-tools            \
      libglm-dev\
      libx11-dev \
      libxrandr-dev \
      libxinerama-dev \
      libxcursor-dev \
      libxi-dev \
      libxext-dev \
      vulkan-validationlayers \
      mesa-utils

Run apt-get install -y --no-install-recommends libxcb1-dev \
      libx11-xcb-dev \
      libxcb-randr0-dev \
      libxcb-image0-dev \
      libxcb-keysyms1-dev \
      libxcb-shm0-dev \
      libxcb-icccm4-dev \
      libxcb-sync-dev \
      libxcb-xkb-dev \
      libxkbcommon-x11-dev

# RUN sudo apt-get -y update && sudo apt-get install  -y \
#     #mesa-utils \
#     libglm-dev\
#     libx11-dev \
#     libxrandr-dev \
#     libxinerama-dev \
#     libxcursor-dev \
#     libxi-dev \
#     libxext-dev \
#     libxfixes-dev \
#     libwayland-dev \
#     nvidia-driver-575 \
#     vulkan-tools\
#     vulkan-validationlayers\
     #libvulkan-dev


