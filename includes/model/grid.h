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
 * @file model/grid.h
 * @brief Header file of the Grid model class.
 */

#ifndef MODEL_GRID_H_
#define MODEL_GRID_H_

#include <gtk/gtk.h>

typedef struct TController TController;
typedef struct THex THex;
typedef enum color_name_t color_name_t;

typedef struct TGridModel {

    void(*Change_Start)(struct TGridModel*, int, int);

    void(*Change_Goal)(struct TGridModel*, int, int);

    void(*Random)(struct TGridModel*);

    int(*Heuristic)(struct TGridModel*, THex*, THex*);

    void(*Reset_Model)(struct TGridModel*, color_name_t);

    void(*Free)(struct TGridModel*);       /*!< Free (ressources) method. */

    TController *observator;
    THex ***hexs;
    THex *start;
    THex *goal;

} TGridModel ;


TGridModel *New_TGridModel(TController *observator);

void TGridModel_Change_Start(TGridModel *this, int x, int y);

void TGridModel_Change_Goal(TGridModel *this, int x, int y);

void TGridModel_Random(TGridModel *this);

int TGridModel_Heuristic(TGridModel *this, THex *hex1, THex *hex2);

void TGridModel_Reset_Model(TGridModel *this, color_name_t color);

void TGridModel_New_Free(TGridModel *this);

#endif
