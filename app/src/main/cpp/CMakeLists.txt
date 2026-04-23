cmake_minimum_required(VERSION 3.22.1)

project("nativecalc")

add_library(
        nativecalc-core
        SHARED
        nativecalc-core.cpp)

find_library(
        android-log
        log)

target_link_libraries(
        nativecalc-core
        ${android-log})