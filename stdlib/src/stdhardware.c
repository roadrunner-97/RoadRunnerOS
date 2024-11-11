#include "stdhardware.h"
#include <stdint.h>

void write_byte_to_port(uint16_t hardware_port, uint8_t out_byte)
{ /* don't fully understand this but it writes a byte to a given port */
    asm volatile ("outb %1, %0" : : "dN" (hardware_port), "a" (out_byte));
}

uint8_t read_byte_from_port(uint16_t hardware_port)
{
    uint8_t in_byte = 0;
    asm volatile ("inb %1, %0" : "=a" (in_byte) : "dN" (hardware_port));
    return in_byte;
}