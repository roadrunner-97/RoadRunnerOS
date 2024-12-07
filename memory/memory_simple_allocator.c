#include <stdint.h>
#include "basic_framebuffer.h"
#include "memory.h"

void* mem_space_begin = 0;
void* mem_space_end = 0;
uint32_t mem_space_size = 0;

#define MIN_FREE_SIZE_TO_SPLIT_ON 16
#define PREFIX_SIZE (sizeof(block_prefix_t))

uint32_t align_to(uint32_t base, uint32_t align)
{
    return align * ((base/align) + 1);
}

void kmemory_space_assign(void* start, uint32_t len)
{
    if(mem_space_begin != 0 || mem_space_size != 0 || mem_space_end != 0)
    {
        kprintf("%#tried to setup a kernel heap when one already exists!\n", COL_BG_ERROR, COL_FG_ERROR);
    }
    mem_space_begin = (uint8_t*)start;
    mem_space_size = len;
    mem_space_end = mem_space_begin + mem_space_size;
    block_prefix_t* first_block = (block_prefix_t*)mem_space_begin;
    first_block->is_block_free = FREE;
    first_block->block_length = mem_space_size - PREFIX_SIZE;
    kprintf("%#allocated a heap of size %d from %d to %d\n", COL_BG_INFO, COL_FG_INFO, (int)mem_space_size, (int)mem_space_begin, (int)mem_space_end);
}

static block_prefix_t* get_next_block_prefix(block_prefix_t* current_block)
{
    return (block_prefix_t*)((void*)current_block + PREFIX_SIZE + current_block->block_length);
}

void* kmemory_assign_chunk(uint32_t size_request)
{
    // kprintf("attempting to assign %d bytes\n", size_request);
    block_prefix_t* block_under_test = (block_prefix_t*)mem_space_begin;
    while(((void*)block_under_test + PREFIX_SIZE + size_request) < mem_space_end)
    {
        if(block_under_test->is_block_free == USED)
        {
            /* not free so we'll bump to the next block.*/
            block_under_test = get_next_block_prefix(block_under_test);
        }
        else if(block_under_test->is_block_free == FREE)
        {
            if(block_under_test->block_length < (size_request))
            {
                /* not big enough so we'll bump to the next block */
                block_under_test = get_next_block_prefix(block_under_test);
            } else
            {
                block_under_test->is_block_free = USED;
                /* the block is no longer free and now we need to decide if we split it or not.*/
                if(block_under_test->block_length - size_request >= MIN_FREE_SIZE_TO_SPLIT_ON)
                {
                    /* in this case the remaining space is more than MIN_FREE_SIZE_TO_SPLIT_ON */
                    block_prefix_t* new_block = ((block_prefix_t*)((void*)block_under_test + PREFIX_SIZE + size_request));
                    // kprintf("splitting the existing block at %d\n", new_block);
                    /*new_block is the beginning of the new block which we're creating. */
                    new_block->is_block_free = FREE;
                    new_block->block_length = block_under_test->block_length - PREFIX_SIZE - size_request;
                    block_under_test->block_length = size_request;
                }
                return (void*)((uint32_t)block_under_test + PREFIX_SIZE);
            }
        }
        else
        {
            kprintf("%# encountered invalid heap prefix at %d\n", COL_BG_ERROR, COL_FG_ERROR, (uint32_t)block_under_test);
            return 0;
        }
    }
    return 0;
}


/**
 * @brief walk the heap and recombine any fragmented free space.
 */
static void recombine_fragments()
{
    block_prefix_t* current_block = (block_prefix_t*)mem_space_begin;
    block_prefix_t* next_block = get_next_block_prefix(current_block);
    while((void*)current_block <= (void*)mem_space_end && (void*)next_block <= (void*)mem_space_end)
    {
        if(current_block->is_block_free == FREE && next_block->is_block_free  == FREE)
        {
            current_block->block_length += PREFIX_SIZE + next_block->block_length;
        }
        current_block = next_block;
        next_block = get_next_block_prefix(current_block);
    }
}

/**
 * @brief free a given block of memory that was previously requested via malloc.
 * @param the location of memory to be freed.
 * @return the size of the freed block. should always be at least the size of the allocated block, or 0 if an error occured.
 */
uint32_t kmemory_free_chunk(void* loc)
{
    block_prefix_t* block_under_test = (block_prefix_t*)mem_space_begin;
    while((void*)block_under_test <= loc){
        if((uint32_t)block_under_test + PREFIX_SIZE == (uint32_t)loc)
        {
            block_under_test->is_block_free = FREE;
            /* do recombination and stuff here */
            recombine_fragments();
            return block_under_test->block_length;
        }
        block_under_test = get_next_block_prefix(block_under_test);
    }
    kprintf("%#failed to release at %d!!\n", COL_BG_ERROR, COL_FG_ERROR, (uint32_t)loc);
    return 0;
}

