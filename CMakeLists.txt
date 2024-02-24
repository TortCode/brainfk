cmake_minimum_required(VERSION 3.25)
project(brainfk)

set(CMAKE_CXX_STANDARD 17)

add_executable(brainfk main.cpp
        engine.cpp engine.h
        instruction.cpp instruction.h
        machine.cpp machine.h
        parser.cpp parser.h)
