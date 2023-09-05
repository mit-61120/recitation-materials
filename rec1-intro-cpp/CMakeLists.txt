cmake_minimum_required(VERSION 3.22)
project(examples)

set(CMAKE_CXX_STANDARD 20)

add_executable(example1 example1.cpp)
add_executable(example2 example2.cpp)
add_executable(example3 example3.cpp)
add_executable(example3-prompt example3-prompt.cpp)

add_executable(example4-prompt example4-prompt.cpp User.cpp)
add_executable(example4 example4.cpp User.cpp)
add_executable(example5 example5.cpp)
add_executable(example6 example6.cpp)
add_executable(example7 example7.cpp)

add_executable(example8-prompt example8-prompt.cpp)
add_executable(example8 example8.cpp)
