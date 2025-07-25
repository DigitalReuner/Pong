include(FetchContent)
add_executable(game main.cpp vulkanapp.cpp)
set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})



set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${VULKAN_SDK}/cmake")


find_package(PkgConfig REQUIRED)
#find_package(Vulkan REQUIRED)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG latest
  )
FetchContent_MakeAvailable(glfw)

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


# Vulkan-Headers
FetchContent_Declare(
  VulkanHeaders
  GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git
  GIT_TAG "main"
)
FetchContent_MakeAvailable(VulkanHeaders)

# Vulkan-Loader
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



target_include_directories(game PRIVATE
  "${stb_SOURCE_DIR}"
  "${tinyobjloader_SOURCE_DIR}"
  ${VulkanHeaders_SOURCE_DIR}/include
)
target_link_libraries(
  game
  PRIVATE
  glfw
  GL
  vulkan
  ${Vulkan_LIBRARIES}
)
 
    
    
    
target_compile_features(game PUBLIC cxx_std_23)
target_compile_options(game PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
      -Wall;-Wextra;-Wpedantic;-Werror>
  )
    
    
target_include_directories(game PRIVATE "${stb_SOURCE_DIR}" "${tinyobjloader_SOURCE_DIR}")