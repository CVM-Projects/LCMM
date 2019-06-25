cmake_minimum_required(VERSION 3.0)
project(LCMM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(include)
aux_source_directory(source LCMM_SOURCE_FILES)

add_library(lcmm STATIC ${LCMM_SOURCE_FILES} include)
set_property(TARGET lcmm PROPERTY CXX_STANDARD 14)
