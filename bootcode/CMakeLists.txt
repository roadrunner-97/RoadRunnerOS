enable_language(ASM)
set(CMAKE_ASM_COMPILER /usr/bin/i686-elf-as)
add_library(booter boot.s)