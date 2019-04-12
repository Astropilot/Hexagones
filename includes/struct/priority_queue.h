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

/**
 * @file priority_queue.h
 * @brief Header file of the priority queue data structure.
 */

#ifndef STRUCT_PRIORITY_QUEUE_H_
#define STRUCT_PRIORITY_QUEUE_H_

/**
 * @brief Represents a node in a priority queue.
 *
 * priority_queue_node_t represents a node in a priority queue.
 */
typedef struct priority_queue_node_t {

    void *data;                             /*!< The data in the queue. */
    struct priority_queue_node_t *next;     /*!< The next element in the queue. */
    struct priority_queue_node_t *prev;     /*!< The previous element in the queue. */

} priority_queue_node_t ;

/**
 * @brief Represents a priority queue.
 *
 * priority_queue_t represents a priority queue.
 */
typedef struct priority_queue_t {

    int(*compare)(void*, void*);            /*!< The compare function for priority. */
    priority_queue_node_t *head;            /*!< The head of the queue. */
    unsigned int size;                      /*!< The size of the queue. */

} priority_queue_t ;

/**
 * @fn priority_queue_t *create_priority_queue(int(*compare)(void*, void*))
 * @brief Function to create a new priority queue.
 *
 * @param compare The comparison function that will be used to order the elements.
 * @return Return a new priority queue or NULL if the creation failed.
 */
priority_queue_t *create_priority_queue(int(*compare)(void*, void*));

/**
 * @fn unsigned int push_priority_queue(priority_queue_t *pqueue, void *data)
 * @brief Function to push a new element in a priority queue.
 *
 * @param pqueue The priority queue.
 * @param data The element to add.
 * @return Returns 1 if the addition was successful, 0 if not.
 */
unsigned int push_priority_queue(priority_queue_t *pqueue, void *data);

/**
 * @fn unsigned int decrease_priority_queue(priority_queue_t *pqueue, void *data)
 * @brief Function to re-sort an element whose priority has changed.
 *
 * @param pqueue The priority queue.
 * @param data The element to re-sort.
 * @return Returns 1 if the element has been sorted, 0 if not.
 */
unsigned int decrease_priority_queue(priority_queue_t *pqueue, void *data);

/**
 * @fn void *pop_priority_queue(priority_queue_t *pqueue)
 * @brief Function to pop a element of a priority queue.
 *
 * @param pqueue The priority queue.
 * @return Returns the element with the highest priority.
 */
void *pop_priority_queue(priority_queue_t *pqueue);

/**
 * @fn unsigned int is_present_in_priority_queue(priority_queue_t *pqueue, void *data)
 * @brief Function to check if a element is in a priority queue.
 *
 * @param pqueue The priority queue.
 * @param data The element whose presence is to be checked.
 * @return Returns 1 if the element is present, 0 if not.
 */
unsigned int is_present_in_priority_queue(priority_queue_t *pqueue, void *data);

/**
 * @fn unsigned int is_priority_queue_empty(priority_queue_t *pqueue)
 * @brief Function to check if priority queue is empty.
 *
 * @param pqueue The priority queue.
 * @return Returns 1 if the priority queue is empty, 0 if not.
 */
unsigned int is_priority_queue_empty(priority_queue_t *pqueue);

/**
 * @fn void free_priority_queue(priority_queue_t *pqueue)
 * @brief Function to free up resources in a priority queue.
 *
 * @param pqueue The priority queue.
 */
void free_priority_queue(priority_queue_t *pqueue);

#endif
