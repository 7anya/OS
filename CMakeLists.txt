cmake_minimum_required(VERSION 3.20)
project(OS C)

set(CMAKE_C_STANDARD 99)

add_executable(OS c1.c c2.c c3.c main.c PipeGuide/main.c)
