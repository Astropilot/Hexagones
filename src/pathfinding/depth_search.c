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

#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "pathfinding/depth_search.h"
#include "model/grid.h"
#include "model/hex.h"
#include "struct/queue.h"

void depth_search_step(TGridModel *model, THex *x, THex *predecessor[][MAP_HEIGHTY], int known[][MAP_HEIGHTY]);

void depth_search(TGridModel *model)
{
    int i, j;
    THex *predecessor[MAP_WIDTHX][MAP_HEIGHTY];
    int known[MAP_WIDTHX][MAP_HEIGHTY];

    for (i = 0; i < MAP_WIDTHX; i++) {
        for (j = 0; j < MAP_HEIGHTY; j++) {
            predecessor[i][j] = NULL;
            known[i][j] = 0;
        }
    }

    depth_search_step(model, model->start, predecessor, known);

    THex *current = model->goal;

    while (predecessor[current->x][current->y]) {
        model->Add_Arrow(model, predecessor[current->x][current->y], current, RED);
        current = predecessor[current->x][current->y];
    }
    (void)colors;
}

void depth_search_step(TGridModel *model, THex *x, THex *predecessor[][MAP_HEIGHTY], int known[][MAP_HEIGHTY])
{
    THex **neighbors = model->Get_Neighbors(model, x, 0);
    int count_max = 0;
    THex *neighbor = neighbors[count_max];

    known[x->x][x->y] = 1;
    while (neighbor) {

        if (known[neighbor->x][neighbor->y] == 0) {

            predecessor[neighbor->x][neighbor->y] = x;

            model->Add_Arrow(model, x, neighbor, BLUE);
            depth_search_step(model, neighbor, predecessor, known);
        }

        count_max++;
        if (count_max < 6)
            neighbor = neighbors[count_max];
        else
            neighbor = NULL;
    }
    free(neighbors);
}
