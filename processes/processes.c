#include "processes.h"
#include "memory.h"
#include "basic_framebuffer.h"
#include "stdmem.h"
#include "interrupts.h"

process_t* current_process;
process_t* other_process; /* will replace with a proper linked list sometime */
process_t* init_process;
int process_count = 0;

void switch_process()
{
    ack_PIT();
    uint32_t esp, ebp, eip;
    asm volatile("mov %%esp, %0" : "=r"(esp));
    asm volatile("mov %%ebp, %0" : "=r"(ebp));
    eip = _get_eip();

    /* as an explanation of this.. 
    when switch_process is called, we push the return address of the process on its stack.
    when we call get_eip, it allows us to get the current EIP which will be pointing at this 
    next line of code
    ... finish in a bit */
    if(eip == 0)
    {
        return;
    }

    current_process->eip = eip;
    current_process->ebp = ebp;
    current_process->esp = esp;

    /* replace this with a call to the scheduler later on */
    if(current_process->pid == 0)
    {
        current_process = other_process;
    } else {
        current_process = init_process;
    }

    eip = current_process->eip;
    esp = current_process->esp;
    ebp = current_process->ebp;

    if(current_process->state == PRE_START)
    {
        current_process->state = STARTED;
        kenable_interrupts();
    }
    _process_springboard(eip, ebp, esp);
}

int create_process(char* process_name, void* process_start)
{
    process_t* new_process = kmemory_assign_chunk(sizeof(process_t));
    memset(new_process, 0, sizeof(process_t));
    new_process->process_name = process_name;
    new_process->pid = process_count++;
    new_process->stack_base = kmemory_assign_chunk(1024) + 1024;
    new_process->eip = (uint32_t)process_start;
    new_process->esp = (uint32_t)new_process->stack_base;
    new_process->ebp = (uint32_t)new_process->stack_base;
    new_process->state = PRE_START;
    other_process = new_process;
    return new_process->pid;
}

void multiprocessing_init()
{
    process_t* init_proc = kmemory_assign_chunk(sizeof(process_t));
    memset(init_proc, 0, sizeof(process_t));
    init_proc->process_name = "init process";
    init_proc->pid = 0;
    init_proc->state = PRE_START;
    current_process = init_proc;
    init_process = init_proc;
    process_count++;
}

int get_process_count()
{
    return process_count;
}