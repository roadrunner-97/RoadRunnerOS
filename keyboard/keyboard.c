#include "keyboard.h"
#include "keyboard_internal.h"

#include "text_mode.h"
#include "stdhardware.h"
#include "interrupts.h"
#include "soft_timer.h"

char kbd_en_us_upper[128] =
{
    0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '|', 0, 0,
    0, 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, 0, 0,
    ' ',
};

char kbd_en_us_lower[128] =
{
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', 0, 0,
    0, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 0, 0,
    ' ',
};

bool shift = false;
bool ctrl = false;
bool alt = false;

void render_keystate()
{
    if(shift)
    {
        terminal_info_putchar('S', VGA_COLOR_WHITE, VGA_COLOR_RED, 0, 1);
    } else {
        terminal_info_putchar(' ', VGA_COLOR_WHITE, VGA_COLOR_RED, 0, 1);
    }

    if(ctrl)
    {
        terminal_info_putchar('C', VGA_COLOR_WHITE, VGA_COLOR_GREEN, 1, 1);
    } else {
        terminal_info_putchar(' ', VGA_COLOR_WHITE, VGA_COLOR_GREEN, 1, 1);
    }

    if(alt)
    {
        terminal_info_putchar('A', VGA_COLOR_WHITE, VGA_COLOR_BLUE, 2, 1);
    } else {
        terminal_info_putchar(' ', VGA_COLOR_WHITE, VGA_COLOR_BLUE, 2, 1);
    }
}

void keyboard_handler(regs_t* r)
{
    (void)r;
    uint8_t keycode;

    keycode = read_byte_from_port(0x60);
    if(keycode & KEYCODE_RELEASE_BIT)
    {
        switch(keycode){
            case (KEYCODE_RELEASE_BIT | KEY_SHIFT):
                shift = false;
                break;
            case (KEYCODE_RELEASE_BIT | KEY_CTRL):
                ctrl = false;
                break;
            case (KEYCODE_RELEASE_BIT | KEY_ALT):
                alt = false;
                break;
            default:
                break;
        }
    } else
    {
        switch(keycode){
            case KEY_SHIFT:
                shift = true;
                break;
            case KEY_CTRL:
                ctrl = true;
                break;
            case KEY_ALT:
                alt = true;
                break;
            default:
                if(shift){
                    terminal_putchar(kbd_en_us_upper[keycode], VGA_COLOR_BLACK, VGA_COLOR_WHITE);
                } else {
                    terminal_putchar(kbd_en_us_lower[keycode], VGA_COLOR_BLACK, VGA_COLOR_WHITE);
                }
                break;
        }
    }
    render_keystate();
}


void initialise_keyboard()
{
    install_irq_handler(0x01, keyboard_handler);
    render_keystate();
}