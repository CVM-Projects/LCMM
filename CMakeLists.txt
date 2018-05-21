cmake_minimum_required(VERSION 3.0)
project(LCMM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++14")

include_directories(include)
aux_source_directory(source LCMM_SOURCE_FILES)

add_library(lcmm STATIC ${LCMM_SOURCE_FILES} include)
