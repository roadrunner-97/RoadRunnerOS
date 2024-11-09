add_library(debugger debug.c)
target_link_libraries(debugger basic_framebuffer)
target_include_directories(debugger PUBLIC .)