#include "keyboard.h"
#include "keyboard_internal.h"

#include "basic_framebuffer.h"
#include "stdhardware.h"
#include "interrupts.h"
#include "soft_timer.h"

char kbd_en_us[128] =
{
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', 0, 0,
    0, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 0, 0,
    ' ',
};

void keyboard_handler(regs_t* r)
{
    (void)r;
    uint8_t keycode;

    keycode = read_byte_from_port(0x60);
    if(keycode & KEYCODE_RELEASE_BIT)
    {
        /* do stuff here */
    } else
    {
        terminal_putchar(kbd_en_us[keycode], VGA_COLOR_BLACK, VGA_COLOR_WHITE);
    }
    // spin_wait(1);
}

void initialise_keyboard()
{
    install_irq_handler(0x01, keyboard_handler);
}