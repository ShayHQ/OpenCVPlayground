cmake_minimum_required(VERSION 3.8)

project(OpenCVPlayground)

find_package(OpenCV REQUIRED)

add_subdirectory(accessing-pixels)
add_subdirectory(CvtColor)
add_subdirectory(PresetWB)

add_executable(cvMain main.cpp)
target_link_libraries(cvMain pixelAccess customCvt reverseWB)
