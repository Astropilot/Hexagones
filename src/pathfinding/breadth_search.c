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
#include "pathfinding/breadth_search.h"
#include "model/grid.h"
#include "model/hex.h"
#include "struct/queue.h"

void breadth_search(TGridModel *model)
{
    int i, j;
    THex *start = model->start;

    THex *predecessor[MAP_WIDTHX][MAP_HEIGHTY];
    int distance[MAP_WIDTHX][MAP_HEIGHTY];

    for (i = 0; i < MAP_WIDTHX; i++) {
        for (j = 0; j < MAP_HEIGHTY; j++) {
            predecessor[i][j] = NULL;
            distance[i][j] = 99999999;
        }
    }
    distance[start->x][start->y] = 0;

    queue_t *waiting = create_queue();
    push_queue(waiting, start);

    while (!is_queue_empty(waiting)) {
        THex *current = (THex*)pop_queue(waiting);
        THex **neighbors = model->Get_Neighbors(model, current, 0);
        int count_max = 0;
        THex *neighbor = neighbors[count_max];

        while (neighbor) {

            if (distance[neighbor->x][neighbor->y] == 99999999) {
                char str_distance[12];

                push_queue(waiting, neighbor);
                distance[neighbor->x][neighbor->y] = distance[current->x][current->y] + 1;
                predecessor[neighbor->x][neighbor->y] = current;

                model->Add_Arrow(model, current, neighbor, GRAY);
                sprintf(str_distance, "%d", distance[neighbor->x][neighbor->y]);
                model->Add_Text(model, neighbor, str_distance);
            }
            count_max++;
            if (count_max < 6)
                neighbor = neighbors[count_max];
            else
                neighbor = NULL;
        }
        free(neighbors);
    }

    THex *current = model->goal;

    while (predecessor[current->x][current->y]) {
        model->Add_Arrow(model, predecessor[current->x][current->y], current, RED);
        current = predecessor[current->x][current->y];
    }
    (void)colors;
    free_queue(waiting);
}
