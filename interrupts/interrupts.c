#include "debug.h"
#include "interrupts_internal.h"
#include "interrupts.h"
#include "stdhardware.h"

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
    // if(r->int_no == 0){
    //     kernel_fatal_error("\nInterrupted with ISR");
    //     kernel_fatal_error_int(r->int_no);
    //     kernel_fatal_error(": ");
    //     kernel_fatal_error(exception_friendly_names[r->int_no]);
    //     kernel_fatal_error("\n");
    // }
    // for(;;);
}

irq_handler_t irq_handlers[16] = 
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

void install_irq_handler(int irq_index, irq_handler_t irq_handler)
{
    irq_handlers[irq_index] = irq_handler;
    kernel_info("installed irq ");
    kernel_info_int(irq_index);
    kernel_info("!\n");
}

void _irq_handler(regs_t *r)
{
    if(irq_handlers[r->int_no - 32])
    {
        irq_handlers[r->int_no - 32](r);
    }
    else
    {
        kernel_warning("unhandled IRQ ");
        kernel_warning_int(r->int_no);
        kernel_warning(" !!!!!\n");
    }

    if(r->int_no >= 40)
    {
        write_byte_to_port(SLAVE_PIC_ADDRESS, 0x20);
    }
    write_byte_to_port(MASTER_PIC_ADDRESS, 0x20);
}

