add_library(basic_framebuffer basic_framebuffer.c)

target_link_libraries(basic_framebuffer rrstd gcc)
target_include_directories(basic_framebuffer PUBLIC .)
