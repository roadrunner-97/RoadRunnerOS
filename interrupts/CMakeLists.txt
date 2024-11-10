add_library(interrupts interrupts.s interrupts.c)
target_include_directories(interrupts PUBLIC .)
target_include_directories(interrupts PRIVATE private)
target_link_libraries(interrupts debugger)