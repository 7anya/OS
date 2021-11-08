cmake_minimum_required(VERSION 3.20)
project(OS C)

set(CMAKE_C_STANDARD 99)

add_executable(OS PipeGuide/main.c GuideToConditionalWait/main.c "Round Robin/sharedMemoryC1.c" "Round Robin/sharedMemoryC2.c" "Round Robin/sharedMemoryC3.c")
