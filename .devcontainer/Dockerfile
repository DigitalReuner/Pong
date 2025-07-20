FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04


# COPY insalldependencies.sh /tmp/insalldependencies.sh

# RUN chmod +x /tmp/insalldependencies.sh && \
#     /tmp/insalldependencies.sh; \
#     rm -f /tmp/insalldependencies.sh1

RUN sudo apt-get -y update && sudo apt-get install  -y libgl1-mesa-dri \
    libglx-mesa0 \
    mesa-utils \
    libvulkan1 \
    mesa-vulkan-drivers \
    vulkan-tools \
    vulkan-validationlayers \
    libglfw3 \
    libglfw3-dev \
    libxkbcommon-dev \
    libgl1-mesa-dri 


