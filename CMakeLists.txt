cmake_minimum_required(VERSION 3.22)

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

project(pong
    VERSION 0.0.1
    LANGUAGES C CXX)

set(CMake_export_Compile_Options ON)
execute_process(
  COMMAND ln -s "${CMAKE_BUILD_DIR}/compile_commands.json" "${CMAKE_SOURCE_DIR}/"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)



add_subdirectory(src)



