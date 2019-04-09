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

#include <gtk/gtk.h>
#include <stdlib.h>

#include "main.h"
#include "controller.h"
#include "model/grid.h"
#include "model/hex.h"
#include "ui/color.h"
#include "utils.h"

static TGridModel *singleton_instance = NULL;

static void TGridModel_Init(TGridModel *this);

TGridModel *New_TGridModel(TController *observator)
{
    TGridModel *this = singleton_instance;

    if (!this)
        this = malloc(sizeof(TGridModel));
    else
        return (this);

    if(!this) return (NULL);

    this->Change_Start = TGridModel_Change_Start;
    this->Change_Goal = TGridModel_Change_Goal;
    this->Random = TGridModel_Random;
    this->Heuristic = TGridModel_Heuristic;
    this->Reset_Model = TGridModel_Reset_Model;
    this->Free = TGridModel_New_Free;
    this->observator = observator;
    TGridModel_Init(this);
    singleton_instance = this;
    return (this);
}

static void TGridModel_Init(TGridModel *this)
{
    int x, y;

    this->hexs = malloc(sizeof(THex**) * MAP_WIDTHX);
    for (x = 0; x < MAP_WIDTHX; x++) {
        this->hexs[x] = malloc(sizeof(THex*) * MAP_HEIGHTY);
        for (y = 0; y < MAP_HEIGHTY; y++) {
            this->hexs[x][y] = New_THex(x, y, this->observator);
        }
    }
    this->start = this->hexs[0][MAP_HEIGHTY-1];
    this->start->Change_Color(this->start, MAGENTA, 1);
    this->goal = this->hexs[MAP_WIDTHX-1][0];
    this->goal->Change_Color(this->goal, RED, 1);
    (void)colors;
}

void TGridModel_Change_Start(TGridModel *this, int x, int y)
{
    this->start->Change_Color(this->start, WHITE, 1);
    this->start = this->hexs[x][y];
    this->start->Change_Color(this->start, MAGENTA, 1);
}

void TGridModel_Change_Goal(TGridModel *this, int x, int y)
{
    this->goal->Change_Color(this->goal, WHITE, 1);
    this->goal = this->hexs[x][y];
    this->goal->Change_Color(this->goal, RED, 1);
}

void TGridModel_Random(TGridModel *this)
{
    int x, y;
    color_name_t colours[] = {WHITE, BLUE, GREEN, YELLOW, BLACK};

    for (x = 0; x < MAP_WIDTHX; x++) {
        for (y = 0; y < MAP_HEIGHTY; y++) {
            if (this->hexs[x][y] != this->start && this->hexs[x][y] != this->goal) {
                color_name_t rnd_color = colours[rand_range_int(0, 4)];

                this->hexs[x][y]->Change_Color(this->hexs[x][y], rnd_color, 1);
            }
        }
    }
}

int TGridModel_Heuristic(TGridModel *this, THex *hex1, THex *hex2)
{
    (void)*this;
    (void)*hex1;
    (void)*hex2;
    return (0);
}

void TGridModel_Reset_Model(TGridModel *this, color_name_t color)
{
    int x, y;

    for (x = 0; x < MAP_WIDTHX; x++) {
        for (y = 0; y < MAP_HEIGHTY; y++) {
            this->hexs[x][y]->Change_Color(this->hexs[x][y], color, 1);
        }
    }
    this->start->Change_Color(this->start, MAGENTA, 1);
    this->goal->Change_Color(this->goal, RED, 1);
}

void TGridModel_New_Free(TGridModel *this)
{
    if (this) {
        int x, y;
        for (x = 0; x < MAP_WIDTHX; x++) {
            for (y = 0; y < MAP_HEIGHTY; y++) {
                free(this->hexs[x][y]);
            }
            free(this->hexs[x]);
        }
    }
    free(this);
}
