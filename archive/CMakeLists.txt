cmake_minimum_required(VERSION 3.18)
project(reading)

set(CMAKE_CXX_STANDARD 20)

add_executable(reading src/ext_file.cpp)
# add_executable(svm src/SVM.cpp)

add_library(headers src/constants.h src/fft_utils.h src/fft_utils.cpp )
target_link_libraries(reading tbb headers)

find_package(TBB REQUIRED COMPONENTS tbb)
find_package(eigen3_cmake_module REQUIRED)