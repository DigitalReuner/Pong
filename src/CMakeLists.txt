include(FetchContent)
include(CheckIncludeFile)
add_executable(game main.cpp vulkanapp.cpp drawableObject.cpp)
set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})



set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${VULKAN_SDK}/cmake")


find_package(PkgConfig REQUIRED)
#find_package(Vulkan REQUIRED)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG latest
  )
check_include_file("wayland-client-core.h" HAVE_WAYLAND_HEADERS)

if (NOT HAVE_WAYLAND_HEADERS)
  message(STATUS "Wayland not found – disabling Wayland support in GLFW")
  set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "Disable Wayland in GLFW" FORCE)
else()
  message(STATUS "Wayland found – enabling Wayland support in GLFW")
  set(GLFW_BUILD_WAYLAND ON CACHE BOOL "Enable Wayland in GLFW" FORCE)
endif()
FetchContent_MakeAvailable(glfw)
FetchContent_Declare(
  glm
  GIT_REPOSITORY  https://github.com/g-truc/glm.git
  GIT_TAG "master"
)
FetchContent_MakeAvailable(glm)



FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
  )
FetchContent_MakeAvailable(stb)
  
FetchContent_Declare(
  tinyobjloader
  GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
  GIT_TAG "release"
  )
FetchContent_MakeAvailable(tinyobjloader)


set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/external")
include(FetchContent)
FetchContent_Declare(
  VulkanSDK
    URL        "https://sdk.lunarg.com/sdk/download/1.4.321.1/linux/vulkansdk-linux-x86_64-1.4.321.1.tar.xz"
    SOURCE_DIR "${FETCHCONTENT_BASE_DIR}/vulkansdk")
FetchContent_MakeAvailable(VulkanSDK)
FetchContent_Declare(
  VulkanHeaders
  GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git
  GIT_TAG "main"
)
FetchContent_MakeAvailable(VulkanHeaders)
FetchContent_Declare(
  VulkanLoader
  GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Loader.git
  GIT_TAG "main"
)
set(BUILD_WSI_XCB OFF CACHE BOOL "" FORCE)
set(BUILD_WSI_XLIB ON CACHE BOOL "" FORCE)
set(BUILD_WSI_WAYLAND OFF CACHE BOOL "" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_LOADER_STATIC ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(VulkanLoader)
  
target_include_directories(game PUBLIC
  "${stb_SOURCE_DIR}"
  "${tinyobjloader_SOURCE_DIR}"
  "${FETCHCONTENT_BASE_DIR}/vulkansdk/x86_64/include"
  "${glm_SOURCE_DIR}"
)
target_link_libraries(
  game
  PRIVATE
  glfw
  GL
  vulkan
  ${Vulkan_LIBRARIES}
)


add_custom_command(TARGET game POST_BUILD 
COMMAND mkdir "${CMAKE_BINARY_DIR}/shader" -p
COMMAND "${FETCHCONTENT_BASE_DIR}/vulkansdk/x86_64/bin/glslc" "${CMAKE_SOURCE_DIR}/src/shader/shader.frag" -o "${CMAKE_BINARY_DIR}/shader/frag.spv"
COMMAND "${FETCHCONTENT_BASE_DIR}/vulkansdk/x86_64/bin/glslc" "${CMAKE_SOURCE_DIR}/src/shader/shader.vert" -o "${CMAKE_BINARY_DIR}/shader/vert.spv"
)
  
    
    
target_compile_features(game PUBLIC cxx_std_23)
target_compile_options(game PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
      -Wall;-Wextra;-Wpedantic;-Werror>
  )
    
    
