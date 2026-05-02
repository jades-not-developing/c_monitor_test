cmake_minimum_required(VERSION 4.0)
project(c_monitor_test C)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_C_STANDARD 23)

set(SRC_FILES src/main.c
              src/clock.c
              src/canvas/canvas.c
              src/sdl_instance.c
        src/timer_sdl.c
              src/fs.c)

#TODO: create GLFW_BACKEND
if (SDL_BACKEND)
    message(STATUS "Compiling with SDL2 backend")
    add_definitions(-DSDL_BACKEND=1)
    set(SRC_FILES ${SRC_FILES} src/canvas/canvas_sdl.c
                               src/timer_sdl.c
                               src/sdl_instance.c)
else()
    message(FATAL_ERROR "No backend specified, try building with the SDL_BACKEND flag set")
endif()

add_executable(c_monitor_test ${SRC_FILES})

target_link_libraries(c_monitor_test SDL2::SDL2)
target_include_directories(c_monitor_test PRIVATE include)