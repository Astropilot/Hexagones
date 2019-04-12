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
 * @file pathfinding/bellman_ford.h
 * @brief The Bellman Ford algorithm.
 */

#ifndef PATHFINDING_BELLMAN_FORD_H_
#define PATHFINDING_BELLMAN_FORD_H_

typedef struct TGridModel TGridModel;

/**
 * @brief Function that triggers the Bellman-Ford algorithm from the model.
 *
 * @param model A pointer to the model instance.
 */
void bellman_ford(TGridModel *model);

#endif
