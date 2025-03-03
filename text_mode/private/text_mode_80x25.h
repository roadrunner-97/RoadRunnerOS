#pragma once
#include "../text_mode.h"
typedef struct __attribute__((packed)) {
	uint8_t glyph;
	color_t fg: 4;
	color_t bg: 4;
} text_element_t;
_Static_assert(sizeof(text_element_t) == 2, "you fucked up buddy");

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define INDEX(x, y) ((y) * VGA_WIDTH + (x))
