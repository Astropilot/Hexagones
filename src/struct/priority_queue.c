/*******************************************************************************
* PROJECT: Hexagones
*
* AUTHOR: Yohann Martin
*
* DATE CREATED: 07/04/2019
*
* Copyright (c) 2019 Yohann MARTIN (@Astropilot). All rights reserved.
*
* Licensed under the MIT License. See LICENSE file in the project root for full
* license information.
*******************************************************************************/

#include <stdlib.h>

#include "struct/priority_queue.h"

priority_queue_t *create_priority_queue(int(*compare)(void*, void*))
{
    priority_queue_t *pqueue = malloc(sizeof(priority_queue_t));

    if (!pqueue || !compare) {
        if (pqueue) free(pqueue);
        return (NULL);
    }
    pqueue->compare = compare;
    pqueue->size = 0;
    pqueue->head = NULL;
    return (pqueue);
}

unsigned int push_priority_queue(priority_queue_t *pqueue, void *data)
{
    if (!pqueue || !data) return (0);

    priority_queue_node_t *item = malloc(sizeof(priority_queue_node_t));

    if (!item) return (0);

    item->data = data;
    item->next = NULL;
    item->prev = NULL;

    if (pqueue->size == 0)
        pqueue->head = item;
    else {
        if (pqueue->compare(pqueue->head->data, data) < 0) {
            item->next = pqueue->head;
            pqueue->head->prev = item;
            pqueue->head = item;
        } else {
            priority_queue_node_t *current = pqueue->head;

            while (current->next && pqueue->compare(current->next->data, data) > 0)
                current = current->next;

            item->next = current->next;
            if (current->next)
                current->next->prev = item;
            item->prev = current;
            current->next = item;
        }
    }

    pqueue->size++;
    return (1);
}

unsigned int decrease_priority_queue(priority_queue_t *pqueue, void *data)
{
    if (!pqueue || !data || pqueue->size == 0) return (0);

    priority_queue_node_t *current = pqueue->head;
    priority_queue_node_t *previous = NULL;

    while (current && current->data != data)
        current = current->next;

    if (!current) return (0);

    previous = current->prev;
    while (previous && pqueue->compare(previous->data, data) < 0)
        previous = previous->prev;

    if (current->next)
        current->next->prev = current->prev;
    if (current->prev)
        current->prev->next = current->next;
    current->next = NULL;
    current->prev = NULL;

    current->prev = previous;
    if (previous) {
        current->next = previous->next;
        current->next->prev = current;
        previous->next = current;
    } else {
        pqueue->head->prev = current;
        current->next = pqueue->head;
        pqueue->head = current;
    }

    return (1);
}

void *pop_priority_queue(priority_queue_t *pqueue)
{
    priority_queue_node_t *item;
    void *data;

    if (is_priority_queue_empty(pqueue)) return (NULL);
    item = pqueue->head;
    pqueue->head = item->next;
    pqueue->size--;
    data = item->data;
    free(item);

    return (data);
}

unsigned int is_present_in_priority_queue(priority_queue_t *pqueue, void *data)
{
    if (!pqueue || !data || pqueue->size == 0) return (0);

    priority_queue_node_t *current = pqueue->head;

    while (current) {
        if (current->data == data)
            return (1);
        current = current->next;
    }
    return (0);
}

unsigned int is_priority_queue_empty(priority_queue_t *pqueue)
{
    if (!pqueue) return (0);

    return (pqueue->size == 0);
}

void free_priority_queue(priority_queue_t *pqueue)
{
    while (!is_priority_queue_empty(pqueue)) {
        pop_priority_queue(pqueue);
    }
    free(pqueue);
}
