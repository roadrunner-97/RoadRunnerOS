#include "descriptor_tables.h"
#include "descriptor_tables_internal.h"
#include "debug.h"
#include "stdmem.h"


gdt_entry_t gdts[3];
struct ptr_with_size_t pws_gdt;


void set_gdt_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    gdts[index].base_low = (base & 0xFFFF);
    gdts[index].base_middle = (base >> 16) & 0xFF;
    gdts[index].base_high = (base >> 24) & 0xFF;

    gdts[index].limit_low = (limit & 0xFFFF);
    gdts[index].granularity = ((limit >> 16) & 0x0F);

    gdts[index].granularity |= (granularity & 0xF0);
    gdts[index].access = access;
}

void gdt_initialise()
{
    set_gdt_entry(0, 0, 0,          0,    0);
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    pws_gdt.base = (uint32_t) &gdts[0];
    pws_gdt.len = 8 * 3;
    _gdt_set_asm();
    kernel_info("GDT loaded\n");
}

idt_entry_t idts[256];
struct ptr_with_size_t pws_idt;

void set_idt_entry(int index, uint32_t base, uint16_t sel, uint8_t flags)
{
    idts[index].base_low = (base & 0xFFFF);
    idts[index].base_high = (base >> 16) & 0xFFFF;

    idts[index].sel = sel;

    idts[index].always0 = 0;
    idts[index].flags = flags;
}

void idt_initialise()
{
    memset(&idts[0], 0x00, sizeof(idt_entry_t) * 256);
    _idt_set_asm();
    kernel_info("IDT Loaded!\n");
}