#include "descriptor_tables.h"
#include "descriptor_tables_internal.h"
#include "debug.h"
#include "interrupts.h"
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
    kdisable_interrupts();
    _gdt_set_asm();
    kernel_info("GDT loaded\n");
}

extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();

idt_entry_t idts[256];
struct ptr_with_size_t pws_idt;

void set_idt_entry(uint8_t index, uint32_t base, uint16_t sel, uint8_t flags)
{
    idts[index].base_low = (base & 0xFFFF);
    idts[index].base_high = (base >> 16) & 0xFFFF;

    idts[index].sel = sel;

    idts[index].always0 = 0;
    idts[index].flags = flags  | 0x60;
}

void idt_initialise()
{
    // memset(&idts[0], 0x00, sizeof(idt_entry_t) * 256);

    set_idt_entry(0, (uint32_t)_isr0, 0x08, 0x8E);
    set_idt_entry(1, (uint32_t)_isr1, 0x08, 0x8E);
    set_idt_entry(2, (uint32_t)_isr2, 0x08, 0x8E);
    set_idt_entry(3, (uint32_t)_isr3, 0x08, 0x8E);
    set_idt_entry(4, (uint32_t)_isr4, 0x08, 0x8E);
    set_idt_entry(5, (uint32_t)_isr5, 0x08, 0x8E);
    set_idt_entry(6, (uint32_t)_isr6, 0x08, 0x8E);
    set_idt_entry(7, (uint32_t)_isr7, 0x08, 0x8E);
    set_idt_entry(8, (uint32_t)_isr8, 0x08, 0x8E);
    set_idt_entry(9, (uint32_t)_isr9, 0x08, 0x8E);
    set_idt_entry(10, (uint32_t)_isr10, 0x08, 0x8E);
    set_idt_entry(11, (uint32_t)_isr11, 0x08, 0x8E);
    set_idt_entry(12, (uint32_t)_isr12, 0x08, 0x8E);
    set_idt_entry(13, (uint32_t)_isr13, 0x08, 0x8E);
    set_idt_entry(14, (uint32_t)_isr14, 0x08, 0x8E);
    set_idt_entry(15, (uint32_t)_isr15, 0x08, 0x8E);
    set_idt_entry(16, (uint32_t)_isr16, 0x08, 0x8E);
    set_idt_entry(17, (uint32_t)_isr17, 0x08, 0x8E);
    set_idt_entry(18, (uint32_t)_isr18, 0x08, 0x8E);
    set_idt_entry(19, (uint32_t)_isr19, 0x08, 0x8E);
    set_idt_entry(20, (uint32_t)_isr20, 0x08, 0x8E);
    set_idt_entry(21, (uint32_t)_isr21, 0x08, 0x8E);
    set_idt_entry(22, (uint32_t)_isr22, 0x08, 0x8E);
    set_idt_entry(23, (uint32_t)_isr23, 0x08, 0x8E);
    set_idt_entry(24, (uint32_t)_isr24, 0x08, 0x8E);
    set_idt_entry(25, (uint32_t)_isr25, 0x08, 0x8E);
    set_idt_entry(26, (uint32_t)_isr26, 0x08, 0x8E);
    set_idt_entry(27, (uint32_t)_isr27, 0x08, 0x8E);
    set_idt_entry(28, (uint32_t)_isr28, 0x08, 0x8E);
    set_idt_entry(29, (uint32_t)_isr29, 0x08, 0x8E);
    set_idt_entry(30, (uint32_t)_isr30, 0x08, 0x8E);
    set_idt_entry(31, (uint32_t)_isr31, 0x08, 0x8E);

    pws_idt.base = (uint32_t)&idts;
    pws_idt.len = (256 * sizeof(idt_entry_t)) - 1;
    kdisable_interrupts();
    _idt_set_asm();
    kernel_info("IDT Loaded!\n");
}