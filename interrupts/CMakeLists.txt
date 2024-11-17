add_library(interrupts interrupt_requests.s interrupts.s interrupts.c)
target_include_directories(interrupts PUBLIC .)
target_include_directories(interrupts PRIVATE private)
target_link_libraries(interrupts basic_framebuffer rrstd)