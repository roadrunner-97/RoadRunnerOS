add_library(processes processes.c processes.s)
target_include_directories(processes PUBLIC .)
target_link_libraries(processes rrstd interrupts memory text_mode linked_list)