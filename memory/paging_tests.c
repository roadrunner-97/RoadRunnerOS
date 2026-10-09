#include "paging_tests.h"
#include "pages.h"
#include "text_mode.h"
#include "memory.h"


void test_virtual_page_clash()
{
    page_directory_entry_t* p_page_table_A = create_page_directory();
    page_directory_entry_t* p_page_table_B = create_page_directory();

    identity_map(p_page_table_A, 0,(void*)0x200000); /* for the moment we need to map the kernel here*/
	identity_map(p_page_table_B, 0,(void*)0x200000);

    /* test that we have a random page with the same address that has different physical memory */
    void* test_page_A = kmemory_assign_page_aligned_chunk(4096);
    map_virtual_page_to_physical_page(p_page_table_A, (void*)0x400000, test_page_A); // give this page to the new process

    void* test_page_B = kmemory_assign_page_aligned_chunk(4096);
    map_virtual_page_to_physical_page(p_page_table_B, (void*)0x400000, test_page_B); // give this page to the new process

    set_active_page_directory(p_page_table_A);
    
    *(volatile uint32_t*)0x400000 = 0x0B0EBAAB;

    set_active_page_directory(p_page_table_B);

    *(volatile uint32_t*)0x400000 = 0x17AFBA5E;

    set_active_page_directory(p_page_table_A);

    if( *(volatile uint32_t*)0x400000 != 0x0B0EBAAB)
    {
        kprintf("Failed to maintain virtual address isolation!!!\n");
        kprintf("expected value: %h\n", 0x0B0EBAAB);
        kprintf("actual value: %h\n", *(volatile uint32_t*)0x400000);
        while(1);
    }
}



void run_paging_tests()
{
    test_virtual_page_clash();    
}