#include "debug.h"
#include "basic_framebuffer.h"

void kernel_fatal_error(char* message)
{
    terminal_writestring_color("Kernel fatal error: ", VGA_COLOR_WHITE, VGA_COLOR_RED);
    terminal_writestring_color(message, VGA_COLOR_WHITE, VGA_COLOR_RED);
    // while(1==1){}
}

void kernel_warning(char* message)
{
    terminal_writestring_color("Kernel warning: ", VGA_COLOR_WHITE, VGA_COLOR_BROWN);
    terminal_writestring_color(message, VGA_COLOR_WHITE, VGA_COLOR_BROWN);
}

void kernel_info(char* message)
{
    terminal_writestring_color("Kernel info: ", VGA_COLOR_WHITE, VGA_COLOR_BLUE);
    terminal_writestring_color(message, VGA_COLOR_WHITE, VGA_COLOR_BLUE);
}

void kernel_verbose(char* message)
{
    terminal_writestring_color("Kernel verbose: ", VGA_COLOR_WHITE, VGA_COLOR_GREEN);
    terminal_writestring_color(message, VGA_COLOR_WHITE, VGA_COLOR_GREEN);
}