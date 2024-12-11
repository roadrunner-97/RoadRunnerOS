add_library(memory memory_simple_allocator.c pages.c)
target_include_directories(memory PUBLIC .)
target_link_libraries(memory basic_framebuffer)