#include "interrupts_internal.h"
#include "interrupts.h"
#include "stdhardware.h"
#include "text_mode.h"

#define MAGIC_BREAK asm volatile ("xchgw %bx, %bx");

void kdisable_interrupts()
{
    asm volatile ("cli");
}

void kenable_interrupts()
{
    asm volatile ("sti");
}

char* exception_friendly_names[] = 
{
    "Division by Zero",
    "Debug exception",
    "Non-Maskable Interrupt Exception",
    "Breakpoint Exception",
    "Into Detected Overflow Exception",
    "Out of Bounds Exception",
    "Invalid Opcode Exception",
    "No Coprocessor Exception",
    "Double Fault Exception",
    "Coprocessor Segment Overrun Exception",
    "Bad TSS Exception",
    "Segment Not Present Exception",
    "Stack Fault Exception",
    "General Protection Fault Exception",
    "Page Fault Exception",
    "Unknown Interrupt Exception",
    "Coprocessor Fault Exception",
    "Alignment Check Exception (486+)",
    "Machine Check Exception (Pentium/586+)",
};


void _fault_handler(regs_t *r)
{
    (void)r;
}

irq_handler_t irq_handlers[16] = 
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

void install_irq_handler(int irq_index, irq_handler_t irq_handler)
{
    irq_handlers[irq_index] = irq_handler;
    kprintf("%#installed irq %d!\n", COL_FG_INFO, COL_BG_INFO, irq_index);
}

void ack_PIT()
{
    write_byte_to_port(SLAVE_PIC_ADDRESS, 0x20);
}

void _irq_handler(regs_t *r)
{
    if(r->int_no >= 40)
    {
        write_byte_to_port(SLAVE_PIC_ADDRESS, 0x20);
    }
    write_byte_to_port(MASTER_PIC_ADDRESS, 0x20);

    if(irq_handlers[r->int_no - 32])
    {
        irq_handlers[r->int_no - 32](r);
    }
    else
    {
        kprintf("%#unhandled IRQ %d!!!\n", COL_FG_WARNING, COL_BG_WARNING, r->int_no);
    }
}

