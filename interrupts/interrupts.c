#include "debug.h"
#include "interrupts_internal.h"

#define MAGIC_BREAK asm volatile ("xchgw %bx, %bx");

void _fault_handler(regs_t *r)
{
    if(r->int_no == 0){
        kernel_fatal_error("\nInterrupted with ISR");
        kernel_fatal_error_int(r->int_no);
        kernel_fatal_error(": ");
        kernel_fatal_error(exception_friendly_names[r->int_no]);
        kernel_fatal_error("\n");
    }
    for(;;);
}

void kdisable_interrupts()
{
    asm volatile ("cli");
}

void kenable_interrupts()
{
    asm volatile ("sti");
}