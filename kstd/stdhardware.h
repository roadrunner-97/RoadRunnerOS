#pragma once

#include <stdint.h>


#define MASTER_PIC_ADDRESS 0x20
#define SLAVE_PIC_ADDRESS 0xA0

#define PIT_BASE_ADDRESS 0x40
#define PIT_CHANNEL_ZERO PIT_BASE_ADDRESS
#define PIT_CHANNEL_ONE  ((PIT_BASE_ADDRESS) + 1)
#define PIT_CHANNEL_TWO  ((PIT_BASE_ADDRESS) + 2)
#define PIT_CONFIG_REG   ((PIT_BASE_ADDRESS) + 3)

void write_byte_to_port(uint16_t hardware_port, uint8_t out_byte);
uint8_t read_byte_from_port(uint16_t hardware_port);
