cmake_minimum_required(VERSION 3.21)

project(roadrunnerOS C ASM)

set(CMAKE_C_FLAGS "-m32 -fno-stack-protector -nostdlib -ffreestanding -nostdlib -Wall -Wextra -Werror -g")
set(CMAKE_ASM_FLAGS "-m32")
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_CURRENT_SOURCE_DIR}/extras/linker.ld")

add_subdirectory(bootcode)
add_subdirectory(kstd)
add_subdirectory(basic_framebuffer)
add_subdirectory(descriptor_tables)
add_subdirectory(interrupts)
add_subdirectory(soft_timer)
add_subdirectory(keyboard)
add_subdirectory(memory)
add_subdirectory(processes)

add_executable(kernel kernel.c)
target_link_libraries(kernel booter gcc basic_framebuffer gdt soft_timer keyboard memory processes)
set_target_properties(kernel PROPERTIES OUTPUT_NAME "rros.bin")