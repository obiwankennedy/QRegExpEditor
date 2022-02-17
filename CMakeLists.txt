cmake_minimum_required(VERSION 3.16)

project(RegExpEditor)

add_subdirectory(src)
add_subdirectory(bin)

option(TEST "Enable testing" OFF)


if(TEST)
enable_testing(true)
add_subdirectory(tests)
endif()
