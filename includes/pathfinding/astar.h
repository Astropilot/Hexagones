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
 * @file pathfinding/astar.h
 * @brief The A* algorithm.
 */

#ifndef PATHFINDING_ASTAR_H_
#define PATHFINDING_ASTAR_H_

typedef struct TGridModel TGridModel;

void astar(TGridModel *model);

#endif
