cmake_minimum_required(VERSION 3.21)

project(roadrunnerOS C ASM)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
   set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif()


set(CMAKE_C_FLAGS "-m32 -fno-stack-protector -nostdlib -ffreestanding -nostdlib -g")
set(CMAKE_ASM_FLAGS "-m32")
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_CURRENT_SOURCE_DIR}/extras/linker.ld")
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_subdirectory(bootcode)
add_subdirectory(kstd)
add_subdirectory(text_mode)
add_subdirectory(descriptor_tables)
add_subdirectory(interrupts)
add_subdirectory(soft_timer)
add_subdirectory(keyboard)
add_subdirectory(memory)
add_subdirectory(processes)
add_subdirectory(linked_list)
add_subdirectory(multiboot)

add_executable(kernel kernel.c)
target_link_libraries(kernel booter gcc text_mode multiboot gdt soft_timer keyboard memory processes linked_list)
set_target_properties(kernel PROPERTIES OUTPUT_NAME "rros.bin")