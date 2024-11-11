#pragma once
#include <stdint.h>


struct ptr_with_size_t{
    uint16_t len;
    uint32_t base;
} __attribute__((packed));

typedef struct __attribute__((packed))
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} gdt_entry_t;

_Static_assert(sizeof(gdt_entry_t) == 8, "gdt_entry_t has grown?");

typedef struct __attribute__((packed))
{
    uint16_t base_low;
    uint16_t sel; /* ? */
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
} idt_entry_t;

_Static_assert(sizeof(idt_entry_t) == 8, "idt_entry_t has grown?");

extern void _gdt_set_asm(); /* defined in gdt.s */
extern void _idt_set_asm();
