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
 * @file pathfinding/dijkstra.h
 * @brief The A* algorithm.
 */

#ifndef PATHFINDING_DIJKSTRA_H_
#define PATHFINDING_DIJKSTRA_H_

typedef struct TGridModel TGridModel;

void dijkstra(TGridModel *model);

#endif
