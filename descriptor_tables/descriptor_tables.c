#include "descriptor_tables.h"
#include "descriptor_tables_internal.h"
#include "interrupts.h"
#include "stdmem.h"
#include "stdhardware.h"
#include "basic_framebuffer.h"

gdt_entry_t gdts[3];
struct ptr_with_size_t pws_gdt;

uint8_t generate_access_byte(bool gdt_entry_present, uint8_t ring_number, bool descriptor_type, uint8_t type)
{
    uint8_t access_byte = 0;
    access_byte |= (uint8_t)(gdt_entry_present) << GDT_ENTRY_PRESENT_BIT_LOCATION;
    access_byte |= ((ring_number) & RING_NUMBER_SIZE) << RING_NUMBER_BIT_LOCATION;
    access_byte |= (uint8_t)(descriptor_type) << DESCRIPTOR_TYPE_LOCATION;
    access_byte |= type & TYPE_SIZE;
    return access_byte;
}

uint8_t generate_granularity_byte(bool granularity, bool operand_size)
{
    uint8_t granularity_byte = 0;
    granularity_byte |= (uint8_t)granularity << GRANULARITY_BIT_LOCATION;
    granularity_byte |= (uint8_t)operand_size << OPERAND_SIZE_BIT_LOCATION;
    return granularity_byte;
}

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
    set_gdt_entry(1, 0, 0x000FFFFF, generate_access_byte(true, 0, true, 10), generate_granularity_byte(true, true));
    set_gdt_entry(2, 0, 0x000FFFFF, generate_access_byte(true, 0, true, 2), generate_granularity_byte(true, true));

    pws_gdt.base = (uint32_t) &gdts[0];
    pws_gdt.len = (8 * 3) - 1;
    kdisable_interrupts();
    _gdt_set_asm();
    kprintf("%#GDT Loaded\n", COL_FG_INFO, COL_BG_INFO);
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
    _idt_set_asm();
    kprintf("%#IDT Loaded\n", COL_FG_INFO, COL_BG_INFO);
}

extern void _irq0();
extern void _irq1();
extern void _irq2();
extern void _irq3();
extern void _irq4();
extern void _irq5();
extern void _irq6();
extern void _irq7();
extern void _irq8();
extern void _irq9();
extern void _irq10();
extern void _irq11();
extern void _irq12();
extern void _irq13();
extern void _irq14();
extern void _irq15();


void irq_initialise()
{

    /* shamelessly copied. this block reconfigures the PICs to use IRQs 32-47 instead of the default 0-15 */
    write_byte_to_port(MASTER_PIC_ADDRESS, 0x11);
    write_byte_to_port(SLAVE_PIC_ADDRESS, 0x11);

    write_byte_to_port(MASTER_PIC_ADDRESS + 1, 0x20);
    write_byte_to_port(SLAVE_PIC_ADDRESS + 1, 0x28);

    write_byte_to_port(MASTER_PIC_ADDRESS + 1, 0x04);
    write_byte_to_port(SLAVE_PIC_ADDRESS + 1, 0x02);

    write_byte_to_port(MASTER_PIC_ADDRESS + 1, 0x01);
    write_byte_to_port(SLAVE_PIC_ADDRESS + 1, 0x01);

    write_byte_to_port(MASTER_PIC_ADDRESS + 1, 0x00);
    write_byte_to_port(SLAVE_PIC_ADDRESS + 1, 0x00);

    set_idt_entry(32, (uint32_t)_irq0, 0x08, 0x8E);
    set_idt_entry(33, (uint32_t)_irq1, 0x08, 0x8E);
    set_idt_entry(34, (uint32_t)_irq2, 0x08, 0x8E);
    set_idt_entry(35, (uint32_t)_irq3, 0x08, 0x8E);
    set_idt_entry(36, (uint32_t)_irq4, 0x08, 0x8E);
    set_idt_entry(37, (uint32_t)_irq5, 0x08, 0x8E);
    set_idt_entry(38, (uint32_t)_irq6, 0x08, 0x8E);
    set_idt_entry(39, (uint32_t)_irq7, 0x08, 0x8E);
    set_idt_entry(40, (uint32_t)_irq8, 0x08, 0x8E);
    set_idt_entry(41, (uint32_t)_irq9, 0x08, 0x8E);
    set_idt_entry(42, (uint32_t)_irq10, 0x08, 0x8E);
    set_idt_entry(43, (uint32_t)_irq11, 0x08, 0x8E);
    set_idt_entry(44, (uint32_t)_irq12, 0x08, 0x8E);
    set_idt_entry(45, (uint32_t)_irq13, 0x08, 0x8E);
    set_idt_entry(46, (uint32_t)_irq14, 0x08, 0x8E);
    set_idt_entry(47, (uint32_t)_irq15, 0x08, 0x8E);
    kprintf("%#IRQs Loaded\n", COL_FG_INFO, COL_BG_INFO);
}