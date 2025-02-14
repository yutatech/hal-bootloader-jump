cmake_minimum_required(VERSION 3.22)
project(hal_bootloader_jump)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    include
)

target_sources(${PROJECT_NAME} INTERFACE
    src/jump.c
)