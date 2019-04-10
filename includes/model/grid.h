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

#include "utils.h"

typedef struct TController TController;
typedef struct THex THex;
typedef enum color_name_t color_name_t;

typedef struct TGridModel {

    void(*Change_Start)(struct TGridModel*, int, int);

    void(*Change_Goal)(struct TGridModel*, int, int);

    void(*Random)(struct TGridModel*);

    int(*Empty_Distance)(struct TGridModel*, THex*, THex*);

    THex**(*Get_Neighbors)(struct TGridModel*, THex*, unsigned int);

    arrow_id_t(*Add_Arrow)(struct TGridModel*, THex*, THex*, color_name_t);

    void(*Remove_Arrow)(struct TGridModel*, arrow_id_t);

    text_id_t(*Add_Text)(struct TGridModel*, THex*, const char*);

    void(*Remove_Text)(struct TGridModel*, text_id_t);

    void(*Reset_Model)(struct TGridModel*, color_name_t);

    void(*Reset_Results)(struct TGridModel*);

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

int TGridModel_Empty_Distance(TGridModel *this, THex *hex1, THex *hex2);

THex **TGridModel_Get_Neighbors(TGridModel *this, THex *hex, unsigned int all);

arrow_id_t TGridModel_Add_Arrow(TGridModel *this, THex *hex1, THex *hex2, color_name_t color);

void TGridModel_Remove_Arrow(TGridModel *this, arrow_id_t arrow);

text_id_t TGridModel_Add_Text(TGridModel *this, THex *hex, const char *text);

void TGridModel_Remove_Text(TGridModel *this, text_id_t text);

void TGridModel_Reset_Model(TGridModel *this, color_name_t color);

void TGridModel_Reset_Results(TGridModel *this);

void TGridModel_New_Free(TGridModel *this);

#endif
