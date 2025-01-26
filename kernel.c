#include "basic_framebuffer.h"
#include "descriptor_tables.h"
#include "interrupts.h"
#include "soft_timer.h"
#include "keyboard.h"
#include "memory.h"
#include "pages.h"
#include "stdmem.h"
#include "processes.h"
#include "linked_list.h"

#define MAGIC_BREAK asm volatile ("xchgw %bx, %bx");

extern void* _kernel_start;
extern void* _kernel_end;

void magic_loop1()
{
	int i = 0;
	while(true)
	{
		kprintf("task 1 says hello! %d\n", i++);
		spin_wait(2000);
	}
}

void magic_loop2()
{
	int i = 0;
	while(true)
	{
		kprintf("task 2 says hello! %d\n", i++);
		spin_wait(500);
	}
}


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

	uint32_t aligned_start = (uint32_t)round_up_to_page_address(&_kernel_end);
	kmemory_space_assign((void*)aligned_start, 0x100000);

	page_directory_entry_t* system_directory = create_page_directory();

	identity_map(system_directory, 0, &_kernel_end);

	// /* enable MMU here */
	// set_active_page_directory(system_directory);
	// multiprocessing_init();
	// create_process("task2", magic_loop2);
	// magic_loop1();

	linked_t* blah = (linked_t*)kmemory_assign_chunk(sizeof(linked_t));
	linked_list_init(blah);
	linked_list_append(blah, (void*)0);
	linked_list_append(blah, (void*)0);
	linked_list_append(blah, (void*)0);
	linked_list_append(blah, (void*)0);
	linked_list_dump(blah);
	for(;;);
}