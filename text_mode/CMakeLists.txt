if(USE_TEXT_FB)
    add_library(text_mode text_mode_80x25.c)
else()
    add_library(text_mode text_mode_vga.c)
endif()

target_link_libraries(text_mode rrstd gcc soft_timer)
target_include_directories(text_mode PUBLIC .)
target_include_directories(text_mode PRIVATE private)