#pragma once

#include "basic_framebuffer.h"

void kernel_fatal_error(char* message);
void kernel_warning(char* message);
void kernel_info(char* message);
void kernel_verbose(char* message);