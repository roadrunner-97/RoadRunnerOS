#include "basic_framebuffer.h"
#include "descriptor_tables.h"
#include "interrupts.h"
#include "soft_timer.h"
#include "keyboard.h"

#define MAGIC_BREAK asm volatile ("xchgw %bx, %bx");

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
	terminal_info_writestring("Booted RoadrunnerOS 1.0 \"meep meep\"\n", 0, 0);
	gdt_initialise();
	idt_initialise();
	irq_initialise();
	initialise_timers();
	initialise_keyboard();
	kenable_interrupts();
	kprintf("Hello world, I am %s, and I am %d years old \n", "Raffi", 27);
	for(;;);
}