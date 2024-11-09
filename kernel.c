#include "basic_framebuffer.h"
#include "debug.h"
#include "descriptor_tables.h"

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
	terminal_writestring("Booted RoadrunnerOS 1.0 \"meep meep\"\n");
	gdt_initialise();
	idt_initialise();
}