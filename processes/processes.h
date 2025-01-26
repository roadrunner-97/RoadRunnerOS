#pragma once
#include "stdint.h"

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
    void* stack_base;
    uint32_t ebp, esp, eip;
    proc_lifecycle_t state;
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
 */
void _process_springboard();

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