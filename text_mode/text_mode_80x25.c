#include "text_mode.h"
#include "stdmem.h"
#include "stdmaths.h"
#include "stdarg.h"
#include "text_mode_80x25.h"

#define MAGIC_BREAK asm volatile ("xchgw %bx, %bx");


static size_t terminal_row;
static size_t terminal_column;

static text_element_t* buffer;

static color_t fg_default = VGA_COLOR_BLACK;
static color_t bg_default = VGA_COLOR_WHITE;

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void terminal_initialize(void) 
{
	terminal_row = 2;
	terminal_column = 0;
	buffer = (text_element_t*) 0xB8000;

	for (size_t y = 0; y < 2; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			buffer[INDEX(x,y)].bg = fg_default;
			buffer[INDEX(x,y)].fg = bg_default;
			buffer[INDEX(x,y)].glyph = ' ';
		}
	}

	for (size_t y = 2; y < VGA_HEIGHT; y++) {
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
		memcpy(&buffer[INDEX(0, 2)], &buffer[INDEX(0, 3)], sizeof(text_element_t) * VGA_WIDTH * (VGA_HEIGHT-1));
		for(int x = 0; x < VGA_WIDTH; x++)
		{
			buffer[INDEX(x, (VGA_HEIGHT-1))].glyph = ' ';
			buffer[INDEX(x, (VGA_HEIGHT-1))].bg = bg_default;
			buffer[INDEX(x, (VGA_HEIGHT-1))].fg = fg_default;
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

void terminal_info_putchar(char c, color_t fg, color_t bg, int info_column, int info_row)
{
	terminal_draw_char(c,
					   fg,
					   bg,
					   info_column,
					   info_row
	);
}

void terminal_putchar(char c, color_t fg, color_t bg)
{
	if(c == '\n')
	{
		newline_handle();
		return;
	}

	if(c == '\b')
	{
		if(terminal_column > 0)
		{
			terminal_column--;
		buffer[INDEX(terminal_column, terminal_row)].glyph = ' ';
		}
		return;
	}
	terminal_draw_char(c,
					   fg,
					   bg,
					   terminal_column,
					   terminal_row);

	if (++terminal_column == VGA_WIDTH) {
        newline_handle();
	}
}

void terminal_info_write(const char* data, size_t size, color_t fg, color_t bg, int info_row, int info_start_column)
{
	for(size_t i = info_start_column; i < size; i++)
	{
		if(data[i] == '\n')
		{	
			break;
		} else {
			terminal_info_putchar(data[i], fg, bg, i, info_row);
		}
	}
}

void terminal_write(const char* data, size_t size, color_t fg, color_t bg)
{
	for (size_t i = 0; i < size; i++)
	{
		terminal_putchar(data[i], fg, bg);
	}
}

void render_info_int(int num, color_t fg, color_t bg, int info_row, int start_info_column)
{
	int x = start_info_column;
    if(num < 0){
        terminal_info_putchar('-', bg, fg, x++, info_row);
        num *= -1;
    }
    int i = 1;
    while(power(10, i) <= num){i++;}
    i--;
    for(; i >= 0; i--)
    {
        int digit = num / power(10, i);
        terminal_info_putchar('0' + digit, bg, fg, x++, info_row);
        num -= digit * power(10, i);
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

void render_hex_colour(int num, color_t fg, color_t bg)
{
	if(num < 0)
	{
		terminal_putchar('-', fg, bg);
		num *= -1;
	}
	terminal_putchar('0', fg, bg);
	terminal_putchar('x', fg, bg);

	int i = 1;
	while(power(16, i) <= num){i++;}
	i--;
	for(; i>= 0; i--)
	{
		int digit = num / power(16, i);
		switch(digit)
		{
			case 10:
				terminal_putchar('A', fg, bg);
				break;
			case 11:
				terminal_putchar('B', fg, bg);
				break;
			case 12:
				terminal_putchar('C', fg, bg);
				break;
			case 13:
				terminal_putchar('D', fg, bg);
				break;
			case 14:
				terminal_putchar('E', fg, bg);
				break;
			case 15:
				terminal_putchar('F', fg, bg);
				break;
			default:
				terminal_putchar('0' + digit, fg, bg);
		}
		num -= digit * power(16, i);
	}
}

void terminal_info_writestring(const char* data, int info_row, int info_start_column)
{
	terminal_info_write(data, strlen(data), bg_default, fg_default, info_row, info_start_column);
}

void terminal_writestring_color(const char* data, color_t fg, color_t bg)
{
	terminal_write(data, strlen(data), fg, bg);
}

void kprintf(char* formatter, ...)
{
	color_t fg = VGA_COLOR_BLACK;
	color_t bg = VGA_COLOR_WHITE;
	va_list p_args;
	va_start(p_args, formatter); /* the first param here is the last named arg in the list. */
	size_t i = 0;
	while(i < strlen(formatter)){
		if(formatter[i] == '\0')
		{
			va_end(p_args);
			return;
		}

		if(formatter[i] == '%')
		{
			if(formatter[i+1] == 'd')
			{
				render_int_color(va_arg(p_args, uint32_t), fg, bg);
				i+=2;
			}
			else if(formatter[i+1] == 'h') {
				render_hex_colour(va_arg(p_args, uint32_t), fg, bg);
				i+=2;
			}
			else if(formatter[i+1] == 'c') {
				terminal_putchar((uint8_t)va_arg(p_args, int), fg, bg);
				i+=2;
			} else if(formatter[i+1] == 's') {
				terminal_writestring_color(va_arg(p_args, char*), fg, bg);
				i+=2;
			} else if(formatter[i+1] == '#') {
				fg = va_arg(p_args, color_t);
				bg = va_arg(p_args, color_t);
				i+=2;

			}
		} else {
			terminal_putchar(formatter[i], fg, bg);
			i++;
		}
	}
}