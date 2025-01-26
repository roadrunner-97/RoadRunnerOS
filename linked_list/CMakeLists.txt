add_library(linked_list linked_list.c)
target_link_libraries(linked_list memory)
target_include_directories(linked_list PUBLIC .)