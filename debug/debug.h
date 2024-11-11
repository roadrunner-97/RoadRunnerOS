#pragma once

#include "basic_framebuffer.h"

void kernel_fatal_error(char* message);
void kernel_fatal_error_int(int);
void kernel_warning(char* message);
void kernel_warning_int(int num);
void kernel_info(char* message);
void kernel_info_int(int num);
void kernel_verbose(char* message);