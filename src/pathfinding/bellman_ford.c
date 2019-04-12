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
#include "pathfinding/bellman_ford.h"
#include "model/grid.h"
#include "model/hex.h"
#include "controller.h"
#include "struct/queue.h"

unsigned int relax_edge(TGridModel *model, double distance[][MAP_HEIGHTY],
    THex *predecessor[][MAP_HEIGHTY], arrow_id_t arrows[][MAP_HEIGHTY],
    THex *hex1, THex *hex2
);

void bellman_ford(TGridModel *model)
{
    int i, j, k;
    THex *start = model->start;

    THex *predecessor[MAP_WIDTHX][MAP_HEIGHTY];
    double distance[MAP_WIDTHX][MAP_HEIGHTY];
    arrow_id_t arrows[MAP_WIDTHX][MAP_HEIGHTY];
    int n = MAP_WIDTHX * MAP_HEIGHTY;

    for (i = 0; i < MAP_WIDTHX; i++) {
        for (j = 0; j < MAP_HEIGHTY; j++) {
            predecessor[i][j] = NULL;
            distance[i][j] = 99999999;
            arrows[i][j].is_arrow = 0;
        }
    }
    distance[start->x][start->y] = 0;

    for(k = 0; k < n; k++) {
        unsigned int edge_relaxed = 0;

        for (i = 0; i < MAP_WIDTHX; i++) {
            for (j = 0; j < MAP_HEIGHTY; j++) {
                if (model->hexs[i][j]->color != BLACK) {
                    THex *hex = model->hexs[i][j];
                    THex **neighbors = model->Get_Neighbors(model, hex, 0);
                    int count_max = 0;
                    THex *neighbor = neighbors[count_max];

                    while (neighbor) {
                        int res = relax_edge(model, distance, predecessor, arrows, hex, neighbor);
                        model->observator->Update_Screen(model->observator);
                        if (res) edge_relaxed = 1;

                        count_max++;
                        if (count_max < 6)
                            neighbor = neighbors[count_max];
                        else
                            neighbor = NULL;
                    }
                    free(neighbors);
                }
            }
        }
        if (!edge_relaxed)
            break;
    }

    THex *current = model->goal;

    while (predecessor[current->x][current->y]) {
        model->Add_Arrow(model, predecessor[current->x][current->y], current, RED);
        current = predecessor[current->x][current->y];
        model->observator->Update_Screen(model->observator);
    }
    (void)colors;
}

unsigned int relax_edge(TGridModel *model, double distance[][MAP_HEIGHTY],
    THex *predecessor[][MAP_HEIGHTY], arrow_id_t arrows[][MAP_HEIGHTY],
    THex *hex1, THex *hex2
) {
    double tmp_distance = distance[hex1->x][hex1->y] + model->Distance(model, hex1, hex2);

    if (tmp_distance < distance[hex2->x][hex2->y]) {
        distance[hex2->x][hex2->y] = tmp_distance;
        predecessor[hex2->x][hex2->y] = hex1;
        if (arrows[hex2->x][hex2->y].is_arrow)
            model->Remove_Arrow(model, arrows[hex2->x][hex2->y]);
        arrows[hex2->x][hex2->y] = model->Add_Arrow(model, hex1, hex2, GRAY);
        return (1);
    }
    return (0);
}
