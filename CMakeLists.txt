cmake_minimum_required(VERSION 2.8)

PROJECT(example)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(density MACOSX_BUNDLE example.cxx)

target_link_libraries(density ${VTK_LIBRARIES})
