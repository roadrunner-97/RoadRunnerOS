#include "debug.h"
#include "basic_framebuffer.h"

void kernel_fatal_error(char* message)
{
    terminal_writestring_color(message, VGA_COLOR_WHITE, VGA_COLOR_RED);
}

void kernel_fatal_error_int(int num)
{
    render_int_color(num, VGA_COLOR_WHITE, VGA_COLOR_RED);
}

void kernel_warning(char* message)
{
    terminal_writestring_color(message, VGA_COLOR_WHITE, VGA_COLOR_BROWN);
}

void kernel_warning_int(int num)
{
    render_int_color(num, VGA_COLOR_WHITE, VGA_COLOR_BROWN);
}

void kernel_info(char* message)
{
    terminal_writestring_color(message, VGA_COLOR_WHITE, VGA_COLOR_BLUE);
}

void kernel_info_int(int num)
{
    render_int_color(num, VGA_COLOR_WHITE, VGA_COLOR_BLUE);
}
