cmake_minimum_required(VERSION 3.13)
project(BluePrint)

execute_process(COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/codegen/token_kind_generator.py)

include_directories(headers)
file(GLOB SOURCES src/*.cpp)

# include LLVM
execute_process(
        COMMAND llvm-config --cxxflags --ldflags --system-libs --libs core
        OUTPUT_VARIABLE LLVM_CONFIG
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(REGEX REPLACE "\n" " " LLVM_CONFIG "${LLVM_CONFIG}")
set(CMAKE_CXX_FLAGS "${LLVM_CONFIG}")
# end

set(CMAKE_CXX_STANDARD 14)
add_definitions(-DDEBUG_GRAPH -DDEBUG_NODE)

add_executable(BluePrint ${SOURCES})