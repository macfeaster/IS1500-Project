cmake_minimum_required(VERSION 3.3)
project(c)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")

FILE(GLOB MyCSources *.c)

include_directories(/Applications/mcb32tools.app/Contents/Resources/Toolchain/include/)

set(SOURCE_FILES ${MyCSources})
add_executable(c ${SOURCE_FILES})