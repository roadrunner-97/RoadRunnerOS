cmake_minimum_required(VERSION 3.21)

project(roadrunnerOS C ASM)
set(CMAKE_C_COMPILER /usr/bin/i686-elf-gcc)

add_subdirectory(bootcode)
add_subdirectory(kernel)
