add_library(multiboot multiboot.c)
target_include_directories(multiboot PUBLIC .)
target_include_directories(multiboot PRIVATE private)
target_link_libraries(multiboot text_mode)