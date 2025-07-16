FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04

COPY installpremake.sh /tmp/installpremake.sh

RUN chmod +x /tmp/installpremake.sh && \
    if ! command -v premake5 >/dev/null 2>&1; then \
      /tmp/installpremake.sh; \
    fi && \
    rm -f /tmp/installpremake.sh


RUN premake5 --version

