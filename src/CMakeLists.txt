include(FetchContent)
include(CheckIncludeFile)
add_executable(game main.cpp vulkanapp.cpp drawableObject.cpp GameManager.cpp)
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
find_package(Slang CONFIG HINTS "${VulkanSDK_ROOT}/lib/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${VULKAN_SDK}/cmake")
find_package (Vulkan REQUIRED)


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
  
target_include_directories(game PRIVATE SYSTEM
  SYSTEM "${stb_SOURCE_DIR}"
  SYSTEM "${tinyobjloader_SOURCE_DIR}"
  SYSTEM "${glm_SOURCE_DIR}"
  SYSTEM "${ktx_SOURCE_DIR}/include"               
  SYSTEM "${FETCHCONTENT_BASE_DIR}/ktx-src/include" 
  SYSTEM "${tinygltf_SOURCE_DIR}"
  #SYSTEM "${vulkan_hpp_SOURCE_DIR}/include" 
  SYSTEM "${VulkanSDK_ROOT}/include"
)

target_compile_definitions(game PUBLIC
        VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1
        VULKAN_HPP_NO_STRUCT_CONSTRUCTORS=1
)
target_link_libraries(
  game
  PRIVATE
  glfw
  GL
  Vulkan::Vulkan
  ${Vulkan_LIBRARIES}
)


add_custom_command(TARGET game POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/shader"
    COMMAND "${VulkanSDK_ROOT}/bin/glslc" "${CMAKE_SOURCE_DIR}/src/shader/shader.frag" -o "${CMAKE_BINARY_DIR}/shader/frag.spv"
    COMMAND "${VulkanSDK_ROOT}/bin/glslc" "${CMAKE_SOURCE_DIR}/src/shader/shader.vert" -o "${CMAKE_BINARY_DIR}/shader/vert.spv"
    #COMMAND "${VulkanSDK_ROOT}/bin/slangc" "${CMAKE_SOURCE_DIR}/src/shader/shader.slang" -target spirv -profile spirv_1_4 -emit-spirv-directly -fvk-use-entrypoint-name -entry vertMain -entry fragMain -o "${CMAKE_BINARY_DIR}/shaders/slang.spv"
)
  
    
    
target_compile_features(game PUBLIC cxx_std_23)
target_compile_options(game PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
      -Wall;-Wextra;-Wpedantic;-Werror>
  )
    
    
