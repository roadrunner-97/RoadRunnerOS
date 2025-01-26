add_library(soft_timer soft_timer.c)
target_include_directories(soft_timer PUBLIC .)
target_include_directories(soft_timer PRIVATE private)
target_link_libraries(soft_timer basic_framebuffer interrupts rrstd processes)