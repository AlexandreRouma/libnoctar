cmake_minimum_required(VERSION 3.13)
project(noctar)

file(GLOB_RECURSE SRC "src/*.c")

add_library(noctar SHARED ${SRC})

target_include_directories(noctar PUBLIC "include/")

# TODO: Remove this
target_include_directories(noctar PUBLIC "/home/ryzerth/noctar/sw/langford_driver/")
