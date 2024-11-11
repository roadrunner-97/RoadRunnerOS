#include "basic_framebuffer.h"
#include "debug.h"
#include "descriptor_tables.h"
#include "interrupts.h"

#define MAGIC_BREAK asm volatile ("xchgw %bx, %bx");

void timer_handler(regs_t* r)
{
	(void)r;
	terminal_writestring("Kernel code handles PIT interrupt :)\n");
}

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
	terminal_writestring("Booted RoadrunnerOS 1.0 \"meep meep\"\n");
	gdt_initialise();
	idt_initialise();
	irq_initialise();
	install_irq_handler(0x00, timer_handler);
	MAGIC_BREAK
	kenable_interrupts();
	for(int i = 3; i >= 0; i--){
		terminal_writestring("12 / ");
		render_int(i);
		terminal_writestring(" = ");
		render_int(12/i);
		terminal_writestring("\n");
	}
	terminal_writestring("\n did we survive?\n");
	for(;;);
}