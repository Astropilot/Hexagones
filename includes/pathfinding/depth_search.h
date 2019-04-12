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
 * @file pathfinding/depth_search.h
 * @brief The A* algorithm.
 */

#ifndef PATHFINDING_DEPTH_SEARCH_H_
#define PATHFINDING_DEPTH_SEARCH_H_

typedef struct TGridModel TGridModel;

/**
 * @brief Function that triggers the Depth-first search algorithm from the model.
 *
 * @param model A pointer to the model instance.
 */
void depth_search(TGridModel *model);

#endif
