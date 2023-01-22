add_library(reverseWB main.cpp)
target_link_libraries(reverseWB ${OpenCV_LIBS})
configure_file(./whiteCalibImage.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)