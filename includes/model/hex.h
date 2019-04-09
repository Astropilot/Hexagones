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
 * @file model/hex.h
 * @brief Header file of the Hex model class.
 */

#ifndef MODEL_HEX_H_
#define MODEL_HEX_H_

#include <gtk/gtk.h>

#include "ui/color.h"

typedef struct TController TController;

typedef struct THex {

    void(*Change_Color)(struct THex*, color_name_t, unsigned int);

    void(*Free)(struct THex*);              /*!< Free (ressources) method. */

    int x;
    int y;
    color_name_t color;
    TController *observator;

} THex ;

THex *New_THex(int x, int y, TController *observator);

void THex_Change_Color(THex *this, color_name_t color, unsigned int notify);

void THex_New_Free(THex *this);

typedef struct TGraphModel {

    int(*Heuristic)(struct TGraphModel*, THex*, THex*);

    void(*Reset_Model)(struct TGraphModel*, color_name_t color);

    void(*Free)(struct TGraphModel*);       /*!< Free (ressources) method. */

    TController *observator;
    THex **hexs;
    THex *start;
    THex *goal;

} TGraphModel ;


TGraphModel *New_TGraphModel(void);

void TGraphModel_New_Free(TGraphModel *this);

#endif
