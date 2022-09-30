cmake_minimum_required(VERSION 3.20)
project(recitation5 CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(recitation5 main.cpp ast/Visitor.cpp PrettyPrinter.cpp execute/FindGlobals.cpp execute/Interpreter.cpp)