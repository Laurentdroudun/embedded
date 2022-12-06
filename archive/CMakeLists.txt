cmake_minimum_required(VERSION 3.18)
project(reading)

set(CMAKE_CXX_STANDARD 20)

add_executable(reading src/main.cpp)
# add_executable(flo_reading src/flo_main.cpp)

<<<<<<< HEAD
add_library(headers src/constants.h src/fft_utils.h src/fft_utils.cpp)
target_link_libraries(reading tbb headers)
=======

target_link_libraries(reading tbb)
target_link_libraries(flo_reading tbb)
>>>>>>> 18145e64e374e4165da188424003566373dadd7f
find_package(TBB REQUIRED COMPONENTS tbb)