#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Hardware text mode color constants. */
typedef enum {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
} color_t;

#define COL_BG_ERROR   VGA_COLOR_RED
#define COL_FG_ERROR   VGA_COLOR_WHITE

#define COL_BG_WARNING VGA_COLOR_BROWN
#define COL_FG_WARNING VGA_COLOR_WHITE

#define COL_BG_INFO    VGA_COLOR_BLUE
#define COL_FG_INFO    VGA_COLOR_WHITE

size_t strlen(const char* str);
void terminal_initialize(void);
void terminal_draw_char(char c, color_t fg, color_t bg, size_t x, size_t y);
void terminal_putchar(char c, color_t fg, color_t bg);
void terminal_info_putchar(char c, color_t fg, color_t bg, int info_column, int info_row);
void terminal_write(const char* data, size_t size, color_t fg, color_t bg);
void newline_handle();
void render_info_int(int num, color_t fg, color_t bg, int info_row, int start_info_column);
void terminal_info_writestring(const char* data, int info_row, int start_info_column);
void kprintf(char* formatter, ...);
