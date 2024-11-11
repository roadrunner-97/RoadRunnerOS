#pragma once

#include <stdint.h>

void outportb(uint16_t hardware_port, char data);
uint8_t read_byte_from_port(uint16_t hardware_port);
