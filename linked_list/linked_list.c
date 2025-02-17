#include "linked_list.h"
#include "memory.h"
#include "text_mode.h"

void linked_list_init(linked_t* list)
{
    list->first = (linked_node_t*)0;
    list->count = 0;
}

linked_node_t* linked_list_get_leaf(linked_t* list)
{
    if(!list->first)
    {
        kprintf("tried to call get-leaf on empty list\n");
        return (linked_node_t*)0;
    }

    linked_node_t* current = list->first;
    int index = 1;

    while(!(current->next))
    {
        current = current->next;
        index++;
    }
    return current;
}

void linked_list_append(linked_t* list, void* payload)
{
    linked_node_t* new_node = kmemory_assign_chunk(sizeof(linked_node_t));
    new_node->payload = payload;
    new_node->next = (linked_node_t*)0;
    if(!list->first)
    {
        list->first = new_node;
    } else {
        linked_node_t* leaf_node = list->first;
        while(leaf_node->next)
        {
            leaf_node = leaf_node->next;
        }
        leaf_node->next = new_node;
    }
    list->count++;
}

int linked_list_get_size(linked_t* list)
{
    return list->count;
}

void linked_list_dump_with_context(linked_t* list, void(*context_function)(void*))
{
    if(list->count == 0 || !list->first)
    {
        kprintf("list is empty!\n");
        return;
    }
    linked_node_t* current = (linked_node_t*)list->first;

    int idx = 0;
    while((current)){
        kprintf("index %d -> ", idx++);
        context_function(current->payload);
        current = current->next;
    }
}

void linked_list_dump(linked_t* list)
{
    if(list->count == 0 || !list->first)
    {
        kprintf("list is empty!\n");
        return;
    }

    linked_node_t* current = list->first;
    int idx = 1;

    while((current->next))
    {
        kprintf("element %d at location %h points to %h\n", idx++, current, current->next);
        current = current->next;
    }
    kprintf("leaf node %d at location %h\n", idx, current);
}

void* find_node_by_payload(linked_t* list, bool(*filter_function)(void*))
{
    if(!list->first)
    {
        return (void*)0;
    }
    linked_node_t* current = list->first;
    while(current->next)
    {
        if(filter_function(current->payload))
        {
            return current->payload;
        }
        current = current->next;
    }
    return (void*)0;
}

void circular_iterator_init(circular_iterator_t* iterator, linked_t* list)
{
    if(!list->first || list->count == 0)
    {
        kprintf("the list must contain at least 1 element to be used as an iterator");
    }
    iterator->list = list;
    iterator->current = list->first;
}

void* circular_iterator_get(circular_iterator_t* iterator)
{
    void* retval = iterator->current->payload;
    if(iterator->current->next)
    {
        iterator->current = iterator->current->next;
    } else
    {
        if(!iterator->list->first)
        {
            kprintf("this list no longer has at least one element");
            for(;;);
        }
        iterator->current = iterator->list->first;
    }
    return retval;
}