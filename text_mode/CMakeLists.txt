add_library(text_mode text_mode.c)

target_link_libraries(text_mode rrstd gcc)
target_include_directories(text_mode PUBLIC .)
