cmake_minimum_required(VERSION 3.22)
project(hal_bootloader_jump)

add_library(hal_bootloader_jump INTERFACE)

# ヘッダーファイルのインクルードパスを指定
target_include_directories(hal_bootloader_jump INTERFACE
    include
)

target_sources(hal_bootloader_jump INTERFACE
    src/jump.c
)