#pragma once

#include <stdint.h>


#define MASTER_PIC_ADDRESS 0x20
#define SLAVE_PIC_ADDRESS 0xA0

void write_byte_to_port(uint16_t hardware_port, uint8_t out_byte);
uint8_t read_byte_from_port(uint16_t hardware_port);
