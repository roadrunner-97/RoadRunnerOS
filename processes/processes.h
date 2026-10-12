#pragma once
#include "pages.h"
#include "stdint.h"

#define USER_STACK_SIZE 4096
/* this needs to be rounded down to 0xFFFFFFFC for 32 bit numbers*/
#define USER_STACK_ROOT 0xFFFFFFFC
#define USER_STACK_PAGE 0xFFFFF000

/* at some point i will derive the page(s) from the root and size :) */
#define KERNEL_STACK_SIZE 4096
#define KERNEL_STACK_ROOT 0xFFFFDFFC
#define KERNEL_STACK_PAGE 0xFFFFD000

typedef enum
{
    PRE_START,
    STARTED,
    PAUSED,
    KILLED
} proc_lifecycle_t;

typedef struct{
    char* process_name;
    uint32_t pid;
    void* user_stack_root;
    void* kernel_stack_root;
    uint32_t ebp, esp, eip;
    proc_lifecycle_t state;
    page_directory_entry_t* page_directory;
} process_t;

/**
 * @brief set up the necessary structures for multiprocessing, and turn the current context into a process.
 */
void multiprocessing_init();

/**
 * @brief save the current execution context, select the next execution context, and resume execution of that context.
 */
void switch_process();

/**
 * @brief create a new process.
 * @param process_name the name of the new process.
 * @param process_start function pointer to the new process.
 * @return the PID of the new process.
 * process_start must not return, if it does, things go wrong.
 */
int create_process(char* process_name, void* process_start);\

/**
 * @brief function that catches the EIP of a process. explained in some more detail in the implementation.
 * @return the EIP of the current process.
 */
uint32_t _get_eip();

/**
 * @brief the final jump into the execution context of the new process.
 * @param eip the eip of the process being jumped into
 * @param ebp the ebp of the process being jumped into
 * @param esp the esp of the process being jumped into
 * @param cr3 the cr3 of the process being jumped into
 * @param enable_interrupts whether to enable interrupts (used on first start of a process)
 */
void _process_springboard(uint32_t eip, uint32_t ebp, uint32_t esp, uint32_t cr3, bool starting);

/**
 * @brief call this to indicate that your process doesn't need the rest of the time allocated to it currently.
 */
void _yield();

/**
 * @brief get the total number of processes.
 * @return the number of processes.
 */
int get_process_count();

/**
 * @brief show the PID name, and state of all known processes.
 */
void dump_processes();