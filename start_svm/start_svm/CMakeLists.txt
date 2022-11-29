cmake_minimum_required(VERSION 3.18)
project(start_svm)

set(CMAKE_CXX_STANDARD 20)

add_executable(start_svm main.cpp)

target_link_libraries(start_svm tbb)
find_package(TBB REQUIRED COMPONENTS tbb)