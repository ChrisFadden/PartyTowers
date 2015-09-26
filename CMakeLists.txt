cmake_minimum_required (VERSION 2.8.10)

project (partytowers)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -g")
add_subdirectory (src)
