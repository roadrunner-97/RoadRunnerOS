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

void multiprocessing_init();
void process_switch(int pid);
void switch_process();
int create_process(char* process_name, void* process_start);
uint32_t _get_eip();
void _process_springboard();
void _yield();
int get_process_count();
void dump_processes();
void blah();