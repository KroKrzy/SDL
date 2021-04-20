cmake_minimum_required(VERSION 3.0)

project(sdl LANGUAGES C)

add_executable(sdl main.c)

install(TARGETS sdl RUNTIME DESTINATION bin)
