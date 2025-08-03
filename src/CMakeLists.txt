include(FetchContent)
include(CheckIncludeFile)
set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/external")
add_executable(game 
  main.cpp
  #vulkanapp.cpp
  #drawableObject.cpp
)
set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})



if(DEFINED VULKAN_SDK AND NOT DEFINED VulkanSDK_ROOT)
  set(VulkanSDK_ROOT $ENV{VULKAN_SDK} CACHE PATH "Root of Vulkan build/install")
endif()
if(NOT DEFINED VulkanSDK_ROOT)
  set(VulkanSDK_ROOT "/opt/VulkanSDK/x86_64" CACHE PATH "Root of Vulkan build/install")
endif()
find_library(VULKAN_LIBRARY
  NAMES vulkan
  HINTS "${VulkanSDK_ROOT}/lib" "${VulkanSDK_ROOT}/lib64"
)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${VULKAN_SDK}/cmake")


find_package(PkgConfig REQUIRED)

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
FetchContent_Declare(
  ktx
  GIT_REPOSITORY https://github.com/KhronosGroup/KTX-Software.git
  GIT_TAG "main"
)
FetchContent_MakeAvailable(ktx)

FetchContent_Declare(
  tinygltf
  GIT_REPOSITORY https://github.com/syoyo/tinygltf.git
  GIT_TAG "release"
  )
FetchContent_MakeAvailable(tinygltf)

# # FetchContent_Declare(
# #   VulkanSDK
# #     URL        "https://sdk.lunarg.com/sdk/download/1.4.321.1/linux/vulkansdk-linux-x86_64-1.4.321.1.tar.xz"
# #     SOURCE_DIR "${FETCHCONTENT_BASE_DIR}/vulkansdk")
# # FetchContent_MakeAvailable(VulkanSDK)

# FetchContent_Declare(
#   VulkanHeaders
#   GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git
#   GIT_TAG "main"
# )
# FetchContent_MakeAvailable(VulkanHeaders)

# # FetchContent_Declare(
# #   VulkanLoader
# #   GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Loader.git
# #   GIT_TAG "main"
# # )
# # set(BUILD_WSI_XCB OFF CACHE BOOL "" FORCE)
# # set(BUILD_WSI_XLIB ON CACHE BOOL "" FORCE)
# # set(BUILD_WSI_WAYLAND OFF CACHE BOOL "" FORCE)
# # set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
# # set(BUILD_LOADER_STATIC ON CACHE BOOL "" FORCE)
# # FetchContent_MakeAvailable(VulkanLoader)
# FetchContent_Declare(
#   VulkanHpp
#   GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Hpp.git
#   GIT_TAG        "main"  # for reproducibility consider pinning to a specific tag/commit matching your SDK, e.g., v1.3.xxx
# )
# FetchContent_MakeAvailable(VulkanHpp)
  
target_include_directories(game PRIVATE SYSTEM
  SYSTEM "${stb_SOURCE_DIR}"
  SYSTEM "${tinyobjloader_SOURCE_DIR}"
  SYSTEM "${FETCHCONTENT_BASE_DIR}/vulkansdk/x86_64/include"
  SYSTEM "${glm_SOURCE_DIR}"
  SYSTEM "${ktx_SOURCE_DIR}/include"               
  SYSTEM "${FETCHCONTENT_BASE_DIR}/ktx-src/include" 
  SYSTEM "${tinygltf_SOURCE_DIR}"
  SYSTEM "${vulkan_hpp_SOURCE_DIR}/include" 
  SYSTEM "${VulkanSDK_ROOT}/include"
)

add_library(Vulkan::Vulkan UNKNOWN IMPORTED)
set_target_properties(Vulkan::Vulkan PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${VULKAN_INCLUDE_DIR}"
  IMPORTED_LOCATION "${VULKAN_LIBRARY}"
  INTERFACE_LINK_LIBRARIES ""  # adjust if you have extra dependencies
)

target_link_libraries(
  game
  PRIVATE
  glfw
  GL
  Vulkan::Vulkan
  ktx
  tinygltf  
)


set(GLSLC_EXECUTABLE "${VulkanSDK_ROOT}/bin/glslc")

add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/shaders"
    # COMMAND "${GLSLC_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/src/shaders/shader.frag" -o "${CMAKE_BINARY_DIR}/shaders/frag.spv"
    # COMMAND "${GLSLC_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/src/shaders/shader.vert" -o "${CMAKE_BINARY_DIR}/shaders/vert.spv"
    #COMMAND "${GLSLC_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/src/shaders/shader.slang" -o "${CMAKE_BINARY_DIR}/shaders/slang.spv"
    COMMAND "${VulkanSDK_ROOT}/bin/slangc" "${CMAKE_SOURCE_DIR}/src/shaders/shader.slang" -target spirv -profile spirv_1_4 -emit-spirv-directly -fvk-use-entrypoint-name -entry vertMain -entry fragMain -o "${CMAKE_BINARY_DIR}/shaders/slang.spv"
)

  
    
target_compile_features(game PUBLIC cxx_std_23)
# target_compile_options(game PRIVATE
#   $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
#   $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
#       -Wall;-Wextra;-Wpedantic;-Werror>
#   )
    
    
