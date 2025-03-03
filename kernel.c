#include "text_mode.h"
#include "descriptor_tables.h"
#include "interrupts.h"
#include "soft_timer.h"
#include "keyboard.h"
#include "memory.h"
#include "pages.h"
#include "stdmem.h"
#include "processes.h"
#include "linked_list.h"
#include "multiboot.h"

#define MAGIC_BREAK asm volatile ("xchgw %bx, %bx");

extern void* _kernel_start;
extern void* _kernel_end;

void task1()
{
	int i = 0;
	while(true)
	{
		kprintf("task1: %d\n", i);
		spin_wait(500);
	}
}

void task2()
{
	int i = 0;
	while(true)
	{
		kprintf("task2: %d\n", i);
		spin_wait(500);
	}
}

void task_that_exits()
{
	for(int i = 0; i < 10; i++)
	{
		kprintf("exitable task says %d\n", i);
		spin_wait(2000);
	}
	return;
}

void kernel_main(void) 
{
	{ /* didn't want to risk clobbering the ebx register so i'm doing this
		in its own scope using a stack variable. */
		void* ebx_val = 0;
		asm volatile ("movl %%ebx, %0" : "=r"(ebx_val));
		set_multiboot_header_address(ebx_val);
	}

	/* Initialize terminal interface */
	// terminal_info_writestring("Booted RoadrunnerOS 1.0 \"meep meep\"\n", 0, 0);
	gdt_initialise();
	idt_initialise();
	irq_initialise();

	uint32_t aligned_start = (uint32_t)round_up_to_page_address(&_kernel_end);
	kmemory_space_assign((void*)aligned_start, 0x100000);
	multiprocessing_init(); /* we want to do this pretty quick to allow other stuff to spin up processes */

	page_directory_entry_t* system_directory = create_page_directory();

	identity_map(system_directory, 0, &_kernel_end);

	// /* enable MMU here */
	// // set_active_page_directory(system_directory);

	initialise_timers();

	initialise_keyboard();
	kenable_interrupts(); /* this is what starts the preemption thingy and ultimately gives us processes*/
	// // create_process("task 1", task1);
	// // create_process("task 2", task2);
	// // create_process("exiting task", task_that_exits);
	// parse_multiboot_header();

	terminal_initialize();
	for(;;);
}