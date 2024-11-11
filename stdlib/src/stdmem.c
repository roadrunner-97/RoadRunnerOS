#include "stdmem.h"

void memcpy(void* dest, void* src, size_t size)
{
    uint8_t* p_dest = (uint8_t*)dest;
    uint8_t* p_src = (uint8_t*)src;
    for(size_t i = 0; i < size; i++)
    {
        p_dest[i] = p_src[i];
    }
}

void memset(void* dest, uint8_t infill, size_t size)
{
    uint8_t* p_dest = (uint8_t*)dest;
    for(size_t i = 0; i < size; i++)
    {
        p_dest[i] = infill;
    }
}