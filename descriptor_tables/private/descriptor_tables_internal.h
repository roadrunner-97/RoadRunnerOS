#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "stdbitfield.h"


/* access byte defines */
#define GDT_ENTRY_PRESENT_BIT_LOCATION 7
#define RING_NUMBER_BIT_LOCATION       5
#define RING_NUMBER_SIZE               FIELD_OF_ONES(2)
#define DESCRIPTOR_TYPE_LOCATION       4
#define EXECUTABLE_BIT_LOCATION        3
#define DIRECTION_CONFORMING_BIT_LOCATION 2
#define READABLE_WRITEABLE_BIT_LOCATION   1
#define ACCESSED_BIT_LOCATION             0


/* granularity byte defines */
#define GRANULARITY_BIT_LOCATION       7
#define OPERAND_SIZE_BIT_LOCATION      6
#define LONG_MODE_CODE_BIT_LOCATION    5

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


/**
 * @brief construct the byte used to set granularity of the GDTs.
 * @param granularity if false, we use byte segment granularity, if true, we use 4KiB segment sizes.
 * @param operand_size if false, define a 16 bit segment, if true, define a 32 bit segment.
 * @param long_mode_code false for everything other than a 64 bit code segment. if set, operand_size must be cleared.
 */
uint8_t generate_granularity_byte(bool granularity, bool operand_size, bool long_mode_code);


/**
 * @brief construct the access byte for the GDTs
 * @param gdt_entry_present this shouldn't even be a param lol it disables the entry if you clear it.
 * @param ring_number we only ever use ring 0 (supervisor) or ring 3 (user) modes.
 * @param descriptor_type if true, defines a code/data segment, if false, defines a system segment (TSS).
 * @param executable if false, defines a data segment, if true defines a code segment (which is executable).
 * @param direction_conforming for a data segment, true grows down, false grows up. 
                               for code, if false, the ring level has to be exact,
 *                                       if true, the segment is like a 'greater than or equal to' in terms of privileges.
 * @param read_write for code, false=reading disallowed, true=reading allowed. 
                     for data, false = writing disabled, true=writing enabled. 
 * @param accessed just set this to false i guess. 
 */
uint8_t generate_access_byte(bool gdt_entry_present, uint8_t ring_number, bool descriptor_type,
                             bool executable, bool direction_conforming, bool read_write, bool accessed);