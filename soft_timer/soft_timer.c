#include "soft_timer.h"
#include "basic_framebuffer.h"
#include "interrupts.h"
#include "stdhardware.h"
#include "processes.h"

#include "soft_timer_internal.h"

#include <stdint.h>

uint64_t ticks;

void clock_process()
{
    while(true)
    {
        if(ticks % 5 == 0)
        {
            render_info_int(ticks/100, VGA_COLOR_BLACK, VGA_COLOR_WHITE, 1, 4);
        }
        _yield();
    }
}

void hard_timer_handler(regs_t* r)
{
	(void)r;
	ticks++;
    if(ticks % 20 == 0)
    {
        if(get_process_count())
        {
            switch_process();
        }
    }
}

void set_channel_zero_config(int ticks_per_second)
{
    int time_scale = 1193180 / ticks_per_second; /* the PIT runs at 1.193180MHz */

    write_byte_to_port(PIT_CONFIG_REG, 0x36);
    // write_byte_to_port(0x43, 0x36);
    write_byte_to_port(PIT_CHANNEL_ZERO, (time_scale & 0xFF));
    write_byte_to_port(PIT_CHANNEL_ZERO, ((time_scale >> 8) & 0xFF));
}

/**
 * @brief spin on the timer until the specified amount of ms has elapsed.
 * despite the parameter being in ms, the resolution is only 10ms.
 * 
 * @param ms number of ms to wait. this will snap to the lowest 10ms interval ie: 93ms -> 90ms.
 */
void spin_wait(int ms)
{
    uint64_t beginning = ticks;
    while((ticks - beginning)*10 < (uint64_t)ms){_yield();}
}

void initialise_timers()
{
    ticks = 0;
    set_channel_zero_config(100);
    install_irq_handler(0x00, hard_timer_handler);
    create_process("clock process", clock_process);
}