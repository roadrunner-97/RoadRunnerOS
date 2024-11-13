add_library(keyboard keyboard.c)
target_link_libraries(keyboard rrstd interrupts soft_timer basic_framebuffer)
target_include_directories(keyboard PUBLIC .)
target_include_directories(keyboard PRIVATE private)