cmake_minimum_required(VERSION 3.15)
project(zadanieDiament C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(sop-cake main.c)

target_compile_options(sop-cake PRIVATE
    -Wall
    -Wextra
    -g
    -fsanitize=address,undefined
    -fno-omit-frame-pointer
)

target_link_options(sop-cake PRIVATE
    -fsanitize=address,undefined
)