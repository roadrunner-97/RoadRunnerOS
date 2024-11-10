#include "basic_framebuffer.h"
#include "stdmem.h"
#include "stdmaths.h"

#define MAGIC_BREAK asm volatile ("xchgw %bx, %bx");



size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

static size_t terminal_row;
static size_t terminal_column;
static text_element_t* buffer;

static color_t fg_default = VGA_COLOR_BLACK;
static color_t bg_default = VGA_COLOR_WHITE;

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	buffer = (text_element_t*) 0xB8000;

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			buffer[INDEX(x,y)].bg = bg_default;
			buffer[INDEX(x,y)].fg = fg_default;
			buffer[INDEX(x,y)].glyph = ' ';
		}
	}
}

void newline_handle()
{
	terminal_column = 0;
	if(terminal_row >= VGA_HEIGHT - 1)
	{
		memcpy(&buffer[INDEX(0, 0)], &buffer[INDEX(0, 1)], sizeof(text_element_t) * VGA_WIDTH * (VGA_HEIGHT-1));
		for(int x = 0; x < VGA_WIDTH; x++)
		{
			buffer[INDEX(x, (VGA_HEIGHT-1))].glyph = ' ';
		}
	}
	else
	{
		terminal_row++;
	}
}

void terminal_draw_char(char c, color_t fg, color_t bg, size_t x, size_t y) 
{
	buffer[INDEX(x,y)].bg = bg;
	buffer[INDEX(x,y)].fg = fg;
	buffer[INDEX(x,y)].glyph = c;
}

void terminal_putchar(char c, color_t fg, color_t bg)
{
	terminal_draw_char(c,
					   fg,
					   bg,
					   terminal_column,
					   terminal_row);

	if (++terminal_column == VGA_WIDTH) {
        newline_handle();
	}
}

void terminal_write(const char* data, size_t size, color_t fg, color_t bg)
{
	for (size_t i = 0; i < size; i++)
	{
		if(data[i] == '\n')
		{
            newline_handle();
		}
		else
		{
			terminal_putchar(data[i], fg, bg);
		}
	}
}

void render_int_color(int num, color_t fg, color_t bg)
{
    if(num < 0){
        terminal_putchar('-', fg, bg);
        num *= -1;
    }
    int i = 1;
    while(power(10, i) <= num){i++;}
    i--;
    for(; i >= 0; i--)
    {
        int digit = num / power(10, i);
        terminal_putchar('0' + digit, fg, bg);
        num -= digit * power(10, i);
    }
}

void render_int(int num)
{
	render_int_color(num, fg_default, bg_default);
}



void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data), fg_default, bg_default);
}

void terminal_writestring_color(const char* data, color_t fg, color_t bg)
{
	terminal_write(data, strlen(data), fg, bg);
}