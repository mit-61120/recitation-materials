cmake_minimum_required(VERSION 3.20)
project(main CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp
        ast/Visitor.cpp PrettyPrinter.cpp
        execute/FindGlobals.cpp execute/Interpreter.cpp execute/LValueResolver.cpp
        )
