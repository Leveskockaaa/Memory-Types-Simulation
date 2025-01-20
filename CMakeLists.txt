cmake_minimum_required(VERSION 3.22.1)
project(prog2_nagy_hazi)

set(CMAKE_CXX_STANDARD 14)

include_directories(code/prog2_nagy_hazi)

add_executable(prog2_nagy_hazi
    code/prog2_nagy_hazi/define.h
    code/prog2_nagy_hazi/gtest_lite.h
    code/prog2_nagy_hazi/jporta_test.cpp
    code/prog2_nagy_hazi/memory.cpp
    code/prog2_nagy_hazi/memory.h
    code/prog2_nagy_hazi/memtrace.cpp
    code/prog2_nagy_hazi/memtrace.h
    code/prog2_nagy_hazi/peripheral.cpp
    code/prog2_nagy_hazi/peripheral.h
    code/prog2_nagy_hazi/processor.cpp
    code/prog2_nagy_hazi/processor.h
    code/prog2_nagy_hazi/serializable.h)