#include "basic_framebuffer.h"
#include "debug.h"
#include "descriptor_tables.h"
#include "interrupts.h"

#define MAGIC_BREAK asm volatile ("xchgw %bx, %bx");

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
	terminal_writestring("Booted RoadrunnerOS 1.0 \"meep meep\"\n");
	gdt_initialise();
	idt_initialise();
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