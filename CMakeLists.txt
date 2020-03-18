cmake_minimum_required(VERSION 3.13)
project(BluePrint)

execute_process(COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/codegen/token_kind_generator.py)

include_directories(headers)
file(GLOB SOURCES src/*.cpp)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-DDEBUG_GRAPH -DDEBUG_NODE)

add_executable(BluePrint ${SOURCES})