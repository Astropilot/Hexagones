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
#include "pathfinding/connected_components.h"
#include "model/grid.h"
#include "model/hex.h"
#include "struct/queue.h"

void connected_components_step(TGridModel *model, THex *x, int component[][MAP_HEIGHTY], int n);

void connected_components(TGridModel *model)
{
    int component[MAP_WIDTHX][MAP_HEIGHTY];
    int n = 0;
    int i, j;

    for (i = 0; i < MAP_WIDTHX; i++)
        for (j = 0; j < MAP_HEIGHTY; j++)
            component[i][j] = -1;

    for (i = 0; i < MAP_WIDTHX; i++) {
        for (j = 0; j < MAP_HEIGHTY; j++) {
            if (component[i][j] == -1 && model->hexs[i][j]->color != BLACK) {
                n++;
                connected_components_step(model, model->hexs[i][j], component, n);
            }
        }
    }
}

void connected_components_step(TGridModel *model, THex *x, int component[][MAP_HEIGHTY], int n)
{
    queue_t *waiting = create_queue();
    char str_component[12];

    push_queue(waiting, x);
    component[x->x][x->y] = n;
    sprintf(str_component, "%d", n);
    model->Add_Text(model, x, str_component);

    while (!is_queue_empty(waiting)) {
        THex *current = (THex*)pop_queue(waiting);
        THex **neighbors = model->Get_Neighbors(model, current, 0);
        int count_max = 0;
        THex *neighbor = neighbors[count_max];

        while (neighbor) {

            if (component[neighbor->x][neighbor->y] == -1) {
                component[neighbor->x][neighbor->y] = n;
                model->Add_Text(model, neighbor, str_component);
                push_queue(waiting, neighbor);
            }
            count_max++;
            if (count_max < 6)
                neighbor = neighbors[count_max];
            else
                neighbor = NULL;
        }
        free(neighbors);
    }
    free_queue(waiting);
}
