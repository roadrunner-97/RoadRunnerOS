#include "stdmem.h"
#include "stdmaths.h"
#include "stdarg.h"
#include "text_mode_vga.h"
#include "text_mode.h"
#include "soft_timer.h"

size_t strlen(const char* str)
{
    size_t len = 0;
    while(str[len])
    {
        len++;
    }
    return len;
}

#define WIDTH 640
#define HEIGHT 480

#define INDEX(x, y) ((y) * WIDTH + (x))

static uint32_t terminal_row = 0;
static uint32_t terminal_column = 0;

typedef struct
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t _
} pixel_t;

void terminal_initialize()
{
    pixel_t* buffer = (pixel_t*)0xFD000000;

    for(int y = 0; y < HEIGHT; y++)
    {
        for(int x = 0; x < WIDTH; x++)
        {
            buffer[INDEX(x,y)].red = 0xFF;
            buffer[INDEX(x,y)].green = 0xFF;
            buffer[INDEX(x,y)].blue = 0xFF;
        }
    }
}

void terminal_draw_char(char c, color_t fg, color_t bg, size_t x, size_t y){}
void terminal_putchar(char c, color_t fg, color_t bg){}
void terminal_info_putchar(char c, color_t fg, color_t bg, int info_column, int info_row){}
void terminal_write(const char* data, size_t size, color_t fg, color_t bg){}
void newline_handle(){}
void render_info_int(int num, color_t fg, color_t bg, int info_row, int start_info_column){}
void terminal_info_writestring(const char* data, int info_row, int start_info_column){}
void kprintf(char* formatter, ...){}