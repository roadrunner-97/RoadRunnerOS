#include "debug.h"
#include "basic_framebuffer.h"

void kernel_fatal_error(char* message)
{
    terminal_writestring_color(message, COL_FG_ERROR, COL_BG_ERROR);
}

void kernel_fatal_error_int(int num)
{
    render_int_color(num, COL_FG_ERROR, COL_BG_ERROR);
}

void kernel_warning(char* message)
{
    terminal_writestring_color(message, COL_FG_WARNING, COL_BG_WARNING);
}

void kernel_warning_int(int num)
{
    render_int_color(num, COL_FG_WARNING, COL_BG_WARNING);
}

void kernel_info(char* message)
{
    terminal_writestring_color(message, COL_FG_INFO, COL_BG_INFO);
}

void kernel_info_int(int num)
{
    render_int_color(num, COL_FG_INFO, COL_BG_INFO);
}
