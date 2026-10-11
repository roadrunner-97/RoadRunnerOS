#include "pages.h"
#include "memory.h"
#include "text_mode.h"
#include "memory_internal.h"
#include "interrupts.h"
#include "paging_tests.h"
#include "stdmem.h"

page_directory_entry_t* page_directory;

void page_tables_self_test()
{
    run_paging_tests();
}


void set_active_page_directory(page_directory_entry_t* active_directory)
{
    page_directory = active_directory;
    _enable_paging();
}

void handle_page_fault_interrupt()
{
    kprintf("page fault!!!!!\n");
}

void initialise_pagefault_handler()
{
    kprintf("registering page fault handler interrupt\n");
    install_irq_handler(14, (irq_handler_t)&handle_page_fault_interrupt);
}

int get_page_directory_offset(void* address)
{
    return (((uint32_t)address) >> 22) & PAGE_DIR_SPAN;
}

int get_page_table_offset(void* address)
{
    return (((uint32_t)address) >> 12) & PAGE_TABLE_SPAN;
}

void* get_pointer_from_page_address(uint32_t page_address)
{
    return (void*)(page_address << 12);
}

uint32_t get_page_address_from_pointer(void* p_page)
{
    return ((uint32_t)(p_page)) >> 12;
}

page_directory_entry_t* create_page_directory()
{
    page_directory_entry_t* empty_directory = kmemory_assign_page_aligned_chunk(sizeof(page_directory_entry_t) * 1024);
    for(int i = 0; i < 1024; i++)
    {   /* i know i could memset all 1024 at once but this is more explicit*/
        memset(&empty_directory[i], 0, sizeof(page_directory_entry_t));
    }
    return empty_directory;
}

page_table_entry_t* create_new_page_table(page_directory_entry_t* directory, int directory_idx)
{
    if(directory[directory_idx].present == true)
    {
        return (page_table_entry_t*) get_pointer_from_page_address(directory[directory_idx].page_table_addr);
    } else {
        page_table_entry_t* empty_table = kmemory_assign_page_aligned_chunk(sizeof(page_table_entry_t) * 1024);
        directory[directory_idx].present = true;
        directory[directory_idx].write_allowed = true;
        directory[directory_idx].page_table_addr = get_page_address_from_pointer(empty_table);
        for(int i = 0; i < 1024; i++)
        {
            /* i know i could memset all 1024 at once but this is more explicit*/
            memset(&empty_table[i], 0, sizeof(page_table_entry_t));
        }
        return empty_table;
    }
}

void map_virtual_page_to_physical_page(page_directory_entry_t* directory, void* virtual_page, void* physical_page, bool user_accessible_page)
{
    int directory_idx = get_page_directory_offset(virtual_page);
    int table_idx = get_page_table_offset(virtual_page);

    if(directory[directory_idx].present == false)
    {
        create_new_page_table(directory, directory_idx);
    }

    page_table_entry_t* needed_page_table = (page_table_entry_t*)get_pointer_from_page_address(directory[directory_idx].page_table_addr);
    needed_page_table[table_idx].present = true;
    needed_page_table[table_idx].write_allowed = true;
    needed_page_table[table_idx].page_frame_addr = get_page_address_from_pointer(physical_page);

    /* now handle permissions. if this is a user accessible page, we need to mark not only the entry in the page table, but also
     * in the page directory which contains this page table as user accessible. */
    if(user_accessible_page)
    {
        directory[directory_idx].user_mode = true;
        needed_page_table[table_idx].user_mode = true;
    } else {
        needed_page_table[table_idx].user_mode = false;
        /* don't demote the directory to user_mode=false because other tables may still need user_mode=true */
    }
}

void identity_map(page_directory_entry_t* directory, void* start_address, void* end_address, bool user_accessible_map)
{
    void* start_page_aligned = round_down_to_page_address(start_address);
    void* end_page_aligned = round_up_to_page_address(end_address);
    // kprintf("identity mapping from %d to %d\n", start_page_aligned, end_page_aligned);
    for(void* p_page = start_page_aligned; p_page <= end_page_aligned; p_page+=4096)
    {
        map_virtual_page_to_physical_page(directory, p_page, p_page, user_accessible_map);
    }
}
