cmake_minimum_required(VERSION 3.3)
project(c)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")

FILE(GLOB FlatSources *.c)
FILE(GLOB SubSources */*.c)

include_directories(/Applications/mcb32tools.app/Contents/Resources/Toolchain/include/)

set(SOURCE_FILES ${FlatSources} ${SubSources})
add_executable(c ${SOURCE_FILES})