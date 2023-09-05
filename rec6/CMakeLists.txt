cmake_minimum_required(VERSION 3.22)
project(rec8_p5)

option(ENABLE_AVX OFF)
if(${ENABLE_AVX})
    add_compile_options("-mavx512f")
endif()

set(CMAKE_CXX_STANDARD 17)

add_executable(rec8_p5 main.cpp)
