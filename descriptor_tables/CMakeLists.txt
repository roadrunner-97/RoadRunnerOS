add_library(gdt descriptor_tables.s descriptor_tables.c)
target_link_libraries(gdt gcc debugger rrstd interrupts)
target_include_directories(gdt PUBLIC .)
target_include_directories(gdt PRIVATE private)