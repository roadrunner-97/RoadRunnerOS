add_library(keyboard keyboard.c)
target_link_libraries(keyboard rrstd interrupts soft_timer text_mode)
target_include_directories(keyboard PUBLIC .)
target_include_directories(keyboard PRIVATE private)