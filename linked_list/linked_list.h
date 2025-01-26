#pragma once
#include "stdbool.h"

typedef struct linked_node_t
{
    struct linked_node_t* next;
    void* payload;
} linked_node_t;

typedef struct
{
    linked_node_t* first;
    int count;
} linked_t;

void linked_list_init(linked_t* list);
void linked_list_append(linked_t* list, void* payload);
int linked_list_get_size(linked_t* list);
void linked_list_dump(linked_t* list);
void* find_node_by_payload(linked_t* list, bool(*filter_function)(void*));
void linked_list_dump_with_context(linked_t* list, void(*context_function)(void*));


typedef struct
{
    linked_t* list;
    linked_node_t* current;
} circular_iterator_t;

void circular_iterator_init(circular_iterator_t* iterator, linked_t* list);
void* circular_iterator_get(circular_iterator_t* iterator);