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
#include "pathfinding/dijkstra.h"
#include "model/grid.h"
#include "model/hex.h"
#include "controller.h"
#include "utils.h"
#include "struct/priority_queue.h"

static double distance[MAP_WIDTHX][MAP_HEIGHTY];

static int compare_node(void *n1, void *n2)
{
    THex *node1 = (THex*)n1;
    THex *node2 = (THex*)n2;
    double distance_node1 = distance[node1->x][node1->y];
    double distance_node2 = distance[node2->x][node2->y];

    if (distance_node1 < distance_node2)
        return (1);
    else if (distance_node1 == distance_node2)
        return (0);
    return (-1);
}

void dijkstra(TGridModel *model)
{
    int i, j;
    THex *predecessor[MAP_WIDTHX][MAP_HEIGHTY];
    priority_queue_t *waiting = create_priority_queue(compare_node);
    arrow_id_t arrows[MAP_WIDTHX][MAP_HEIGHTY];
    text_id_t texts[MAP_WIDTHX][MAP_HEIGHTY];

    for (i = 0; i < MAP_WIDTHX; i++) {
        for (j = 0; j < MAP_HEIGHTY; j++) {
            predecessor[i][j] = NULL;
            distance[i][j] = -1;
            arrows[i][j].is_arrow = 0;
            texts[i][j].text = NULL;
        }
    }
    push_priority_queue(waiting, model->start);
    distance[model->start->x][model->start->y] = 0;

    while (!is_priority_queue_empty(waiting)) {
        THex *current = (THex*)pop_priority_queue(waiting);

        if (current->x == model->goal->x && current->y == model->goal->y)
            break;

        THex **neighbors = model->Get_Neighbors(model, current, 0);
        int count_max = 0;
        THex *neighbor = neighbors[count_max];

        while (neighbor) {
            model->observator->Update_Screen(model->observator);

            if ( (distance[current->x][current->y] != -1) &&
                 (  distance[neighbor->x][neighbor->y] == -1 ||
                    distance[current->x][current->y] + model->Distance(model, current, neighbor) < distance[neighbor->x][neighbor->y]
                 )
                ) {
                char str_distance[12];

                distance[neighbor->x][neighbor->y] = distance[current->x][current->y] + model->Distance(model, current, neighbor);
                if (!is_present_in_priority_queue(waiting, neighbor))
                    push_priority_queue(waiting, neighbor);
                else
                    decrease_priority_queue(waiting, neighbor);

                predecessor[neighbor->x][neighbor->y] = current;
                if (arrows[neighbor->x][neighbor->y].is_arrow)
                    model->Remove_Arrow(model, arrows[neighbor->x][neighbor->y]);
                arrows[neighbor->x][neighbor->y] = model->Add_Arrow(model, current, neighbor, GRAY);
                if (texts[neighbor->x][neighbor->y].text)
                    model->Remove_Text(model, texts[neighbor->x][neighbor->y]);
                sprintf(str_distance, "%d", (int)distance[neighbor->x][neighbor->y]);
                texts[neighbor->x][neighbor->y] = model->Add_Text(model, neighbor, str_distance);
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

    while (current && !(current->x == model->start->x && current->y == model->start->y)) {
        if (predecessor[current->x][current->y])
            model->Add_Arrow(model, predecessor[current->x][current->y], current, RED);
        current = predecessor[current->x][current->y];
        model->observator->Update_Screen(model->observator);
    }

    free_priority_queue(waiting);
    (void)colors;
}
