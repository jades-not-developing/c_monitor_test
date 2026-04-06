cmake_minimum_required(VERSION 4.0)
project(c_monitor_test C)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_C_STANDARD 23)

add_executable(c_monitor_test
              src/main.c
              src/clock.c
              src/canvas.c
              src/sdl_instance.c)
target_link_libraries(c_monitor_test SDL2::SDL2)
target_include_directories(c_monitor_test PRIVATE include)