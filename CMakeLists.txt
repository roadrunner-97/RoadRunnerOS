cmake_minimum_required(VERSION 3.21)

project(roadrunnerOS C ASM)
set(CMAKE_C_COMPILER /usr/bin/i686-elf-gcc)

set(CMAKE_C_FLAGS "-std=gnu99 -ffreestanding -O2 -nostdlib -Wall -Wextra")
set(CMAKE_C_COMPILER /usr/bin/i686-elf-gcc)
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_CURRENT_SOURCE_DIR}/extras/linker.ld")

add_subdirectory(bootcode)
add_subdirectory(stdlib)
add_subdirectory(basic_framebuffer)

add_executable(kernel kernel.c)
target_link_libraries(kernel booter gcc basic_framebuffer)
set_target_properties(kernel PROPERTIES OUTPUT_NAME "rros.bin")