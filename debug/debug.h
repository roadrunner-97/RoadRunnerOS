#pragma once

#include "basic_framebuffer.h"

#define COL_BG_ERROR   VGA_COLOR_RED
#define COL_FG_ERROR   VGA_COLOR_WHITE

#define COL_BG_WARNING VGA_COLOR_BROWN
#define COL_FG_WARNING VGA_COLOR_WHITE

#define COL_BG_INFO    VGA_COLOR_BLUE
#define COL_FG_INFO    VGA_COLOR_WHITE

void kernel_fatal_error(char* message);
void kernel_fatal_error_int(int);
void kernel_warning(char* message);
void kernel_warning_int(int num);
void kernel_info(char* message);
void kernel_info_int(int num);
void kernel_verbose(char* message);