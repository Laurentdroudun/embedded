cmake_minimum_required(VERSION 3.18)
project(reading)

set(CMAKE_CXX_STANDARD 20)

add_executable(reading src/main.cpp)
add_executable(flo_reading src/flo_main.cpp)

target_link_libraries(reading tbb)
find_package(TBB REQUIRED COMPONENTS tbb)