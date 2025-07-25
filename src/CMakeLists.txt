add_executable(game main.cpp vulkanapp.cpp)
set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${VULKAN_SDK}/cmake")

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(glfw3 3.3 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED)

target_include_directories(game PRIVATE ${GLFW_INCLUDE_DIRS} ${Vulkan_INCLUDE_DIR})
target_link_libraries(game
  PRIVATE
    glfw
    GL
    ${Vulkan_LIBRARIES}
)




target_compile_features(game PUBLIC cxx_std_23)
target_compile_options(game PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
     -Wall;-Wextra;-Wpedantic;-Werror>
)
# target_include_directories(game PUBLIC ../extern/glfw-3.4/include)
# target_link_libraries(game PUBLIC glfw)
include(FetchContent)
FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
  #SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/stb"
)
FetchContent_MakeAvailable(stb)

FetchContent_Declare(
  tinyobjloader
  GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
  GIT_TAG "release"
  #SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/tinyobjloader"
)
FetchContent_MakeAvailable(tinyobjloader)


target_include_directories(game PRIVATE "${stb_SOURCE_DIR}" "${tinyobjloader_SOURCE_DIR}")