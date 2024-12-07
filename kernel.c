#include "basic_framebuffer.h"
#include "descriptor_tables.h"
#include "interrupts.h"
#include "soft_timer.h"
#include "keyboard.h"
#include "memory.h"

#define MAGIC_BREAK asm volatile ("xchgw %bx, %bx");

extern void* _kernel_start;
extern void* _kernel_end;
extern void* _kernel_size;

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
	uint32_t aligned_start = align_to((uint32_t)&_kernel_end, 1024);
	kmemory_space_assign((void*)aligned_start, 50000);
	void* p1 = kmemory_assign_chunk(100);
	void* p2 = kmemory_assign_chunk(100);
	void* p3 = kmemory_assign_chunk(100);
	void* p4 = kmemory_assign_chunk(100);

	kmemory_free_chunk(p2);
	kmemory_free_chunk(p3);
	void* p5 = kmemory_assign_chunk(200);

	kprintf("1-5: %d, %d, %d, %d, %d\n", p1, p2, p3, p4, p5);
	for(;;);
}