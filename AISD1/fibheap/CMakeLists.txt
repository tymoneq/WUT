cmake_minimum_required(VERSION 3.15)
project(fibheap CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(fibheap main.cpp fibheap.cpp)

if(NOT MSVC)
    target_compile_options(fibheap PRIVATE
        -g
        -O1
        -fno-omit-frame-pointer
        -fsanitize=address,undefined
    )
    target_link_options(fibheap PRIVATE
        -fsanitize=address,undefined
    )
endif()