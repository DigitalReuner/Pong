cmake_minimum_required(VERSION 3.22)

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

project(pong
    VERSION 0.0.1
    LANGUAGES C CXX)

set(CMake_export_Compile_Options ON)

add_subdirectory(src)

set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/external")

include(FetchContent)
FetchContent_Declare(
  VulkanSDK
    URL        "https://sdk.lunarg.com/sdk/download/1.4.321.1/linux/vulkansdk-linux-x86_64-1.4.321.1.tar.xz"
    SOURCE_DIR "${FETCHCONTENT_BASE_DIR}/vulkansdk")


FetchContent_MakeAvailable(VulkanSDK)

