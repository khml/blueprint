cmake_minimum_required(VERSION 3.13)
project(BluePrint)

include_directories(headers)
file(GLOB SOURCES src/*.cpp)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-DDEBUG_GRAPH -DDEBUG_NODE)

add_executable(BluePrint ${SOURCES})