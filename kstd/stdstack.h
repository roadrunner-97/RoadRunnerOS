#pragma once
#include <stdint.h>

/*
 * @brief return a pointer to the nth 32 bit value from the top of a downward-growing stack.
 * @param stack_top the pointer to the highest byte of the stack.
 * @param n the index of the element to return (0 is the topmost element)
 */
static inline uint32_t* stack_get_element_u32(void* stack_top, uint32_t n)
{
    return (uint32_t*)((uint32_t)stack_top & ~3u) - n; //round down to a multiple of 4 and then subtract n
}
