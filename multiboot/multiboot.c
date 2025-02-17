#include "multiboot.h"
#include "private/multiboot_internal.h"
#include "text_mode.h"

uint32_t multiboot_addr = 0;

void set_multiboot_header_address(void* multiboot_header_address)
{
    multiboot_addr = (uint32_t)multiboot_header_address;
}

void parse_multiboot_header()
{
    kprintf("multiboot flags: %d\n", *(uint32_t*)multiboot_addr);
}