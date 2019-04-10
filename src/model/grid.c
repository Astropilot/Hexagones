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
#include <string.h>

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
    this->Empty_Distance = TGridModel_Empty_Distance;
    this->Get_Neighbors = TGridModel_Get_Neighbors;
    this->Add_Arrow = TGridModel_Add_Arrow;
    this->Remove_Arrow = TGridModel_Remove_Arrow;
    this->Add_Text = TGridModel_Add_Text;
    this->Remove_Text = TGridModel_Remove_Text;
    this->Reset_Model = TGridModel_Reset_Model;
    this->Reset_Results = TGridModel_Reset_Results;
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

int TGridModel_Empty_Distance(TGridModel *this, THex *hex1, THex *hex2)
{
    (void)*this;
    (void)*hex1;
    (void)*hex2;
    return (0);
}

THex **TGridModel_Get_Neighbors(TGridModel *this, THex *hex, unsigned int all)
{
    THex **neighbors = malloc(6 * sizeof(THex*));
    int count = 0;
    int xv, yv;
    int i;
    int_pair_t coords[6] = {
        {-1, -1 + hex->x % 2},
        {-1, 0 + hex->x % 2},
        {1, -1 + hex->x % 2},
        {1, 0 + hex->x % 2},
        {0, -1},
        {0, 1}
    };

    for(i = 0; i < 6; i++)
        neighbors[i] = NULL;
    for(i = 0; i < 6; i++) {
        xv = hex->x + coords[i].p1;
        yv = hex->y + coords[i].p2;
        if (xv >= 0 && xv < MAP_WIDTHX && yv >= 0 && yv < MAP_HEIGHTY) {
            if (all || this->hexs[xv][yv]->color != BLACK) {
                neighbors[count] = this->hexs[xv][yv];
                count++;
            }
        }
    }
    return (neighbors);
}

arrow_id_t TGridModel_Add_Arrow(TGridModel *this, THex *hex1, THex *hex2, color_name_t color)
{
    unsigned int uid = 0;
    unsigned int uid2 = 0;

    //TODO: Optimize
    if (hex1->x == hex2->x && hex1->y > hex2->y) {
        uid = 0;
        uid2 = 3;
    }
    if (hex1->x == hex2->x && hex1->y < hex2->y) {
        uid = 3;
        uid2 = 0;
    }
    if (hex1->y == hex2->y && hex1->x < hex2->x) {
        uid = 1;
        uid2 = 4;
    }
    if (hex1->y == hex2->y && hex1->x > hex2->x) {
        uid = 5;
        uid2 = 2;
    }
    if (hex1->x < hex2->x && hex1->y < hex2->y) {
        uid = 2;
        uid2 = 5;
    }
    if (hex1->x < hex2->x && hex1->y > hex2->y) {
        uid = 4;
        uid2 = 1;
    }

    hex1->arrows[uid].is_arrow = 1;
    hex1->arrows[uid].hex_src = hex1;
    hex1->arrows[uid].hex_dst = hex2;
    hex1->arrows[uid].arrow_color = color;
    hex1->arrows[uid].uid_src = uid;
    hex1->arrows[uid].uid_dst = uid2;

    hex2->arrows[uid2].is_arrow = 1;
    hex2->arrows[uid2].hex_src = hex1;
    hex2->arrows[uid2].hex_dst = hex2;
    hex2->arrows[uid2].arrow_color = color;
    hex2->arrows[uid2].uid_src = uid;
    hex2->arrows[uid2].uid_dst = uid2;

    this->observator->Update_Hex(this->observator, hex1);
    return (hex1->arrows[uid]);
}

void TGridModel_Remove_Arrow(TGridModel *this, arrow_id_t arrow)
{
    THex *hex_src = arrow.hex_src;
    THex *hex_dst = arrow.hex_dst;

    hex_src->arrows[arrow.uid_src].is_arrow = 0;
    hex_src->arrows[arrow.uid_src].hex_src = NULL;
    hex_src->arrows[arrow.uid_src].hex_dst = NULL;

    hex_dst->arrows[arrow.uid_dst].is_arrow = 0;
    hex_dst->arrows[arrow.uid_dst].hex_src = NULL;
    hex_dst->arrows[arrow.uid_dst].hex_dst = NULL;

    this->observator->Update_Hex(this->observator, hex_dst);
    this->observator->Update_Hex(this->observator, hex_src);
}

text_id_t TGridModel_Add_Text(TGridModel *this, THex *hex, const char *text)
{
    free(hex->label.text);
    hex->label.text = strdup(text);
    hex->label.hex = hex;

    this->observator->Update_Hex(this->observator, hex);
    return (hex->label);
}

void TGridModel_Remove_Text(TGridModel *this, text_id_t text)
{
    THex *hex = text.hex;

    free(hex->label.text);
    hex->label.text = NULL;

    this->observator->Update_Hex(this->observator, hex);
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
    this->Reset_Results(this);
}

void TGridModel_Reset_Results(TGridModel *this)
{
    int x, y, i;

    for (x = 0; x < MAP_WIDTHX; x++) {
        for (y = 0; y < MAP_HEIGHTY; y++) {
            for (i = 0; i < 6; i++) {
                this->hexs[x][y]->arrows[i].is_arrow = 0;
                this->hexs[x][y]->arrows[i].hex_src = NULL;
                this->hexs[x][y]->arrows[i].hex_dst = NULL;
            }
            free(this->hexs[x][y]->label.text);
            this->hexs[x][y]->label.text = NULL;
            this->observator->Update_Hex(this->observator, this->hexs[x][y]);
        }
    }
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
