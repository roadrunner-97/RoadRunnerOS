#pragma once
#include "stdbool.h"

/**
 * @brief represents a single node in a linked list
*/
typedef struct linked_node_t
{
    struct linked_node_t* next;
    void* payload;
} linked_node_t;

/* represents the base of a linked list which can have 0 or more nodes attached */
typedef struct
{
    linked_node_t* first;
    int count;
} linked_t;

/**
 * @brief resets a linked list back to a state where it contains no nodes.
 * @param list a pointer to the linked list to reset.
 */
void linked_list_init(linked_t* list);

/**
 * @brief append a single element to a linked list.
 * @param list a pointer to the linked list to append to.
 * @param payload a freeform block of memory that the linked list points to.
 */
void linked_list_append(linked_t* list, void* payload);

/**
 * @brief return the number of nodes in a linked list.
 * @param list a pointer to the linked list to count.
 * @return the number of nodes, from 0->INT_MAX.
 */
int linked_list_get_size(linked_t* list);

/**
 * @brief display the relevant pointers and counts of a linked list.
 * @param list the list to display info for.
 */
void linked_list_dump(linked_t* list);

/**
 * @brief search a linked list using a filter function.
 * @param the list to search
 * @param filter_function a function pointer accepting a void* and returning a bool.
 * for every element in the linked list, this will execute filter_function on the payload
 * of the node. if the function returns true, the return value will be a pointer to the payload.
 * if not, or if the list is empty, it will return a null pointer.
 * intended use: filter function should cast the payload into a type it interprets, and return true
 * if the data is what you're looking for.
 * @return a pointer to the payload matching the criteria in filter_function, or null otherwise.
 */
void* find_node_by_payload(linked_t* list, bool(*filter_function)(void*));

/**
 * @brief dump the contents of the linked list, using a function that can interpet the payload data.
 * @param list the list to dump the contents of.
 * @param context_function a function that can intepret the payload and prints some info about it.
 */
void linked_list_dump_with_context(linked_t* list, void(*context_function)(void*));


/**
 * @brief a structure storing a linked list and one element of it.
 */
typedef struct
{
    linked_t* list;
    linked_node_t* current;
} circular_iterator_t;

/**
 * @brief reset the circular iterator to a clean state.
 * @param iterator the object which will be used as the iterator.
 * @param list the linked list the iterator will be backed onto.
 */
void circular_iterator_init(circular_iterator_t* iterator, linked_t* list);

/**
 * @brief get a new element from the iterator.
 * @param iterator the object to get a new element from.
 * @return the payload from an element in the linked list.
 * NB: the ordering and repetition of the payloads being returned is not
 * guaranteed here, but it can be assumed to be a round-robin type.
 */
void* circular_iterator_get(circular_iterator_t* iterator);