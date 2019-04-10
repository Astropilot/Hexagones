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
 * @file ui/map.h
 * @brief Header file of the Map class.
 */

#ifndef UI_MAP_H_
#define UI_MAP_H_

#include <gtk/gtk.h>

#include "controller.h"

typedef struct TMap {

    void(*Init_Map)(struct TMap*);

    void(*Draw_Hexagone)(struct TMap*, int, int, color_name_t);

    void(*Add_Arrow)(struct TMap*, int, int, int, int, color_name_t);

    void(*Reset_Map)(struct TMap*, color_name_t);

    void(*Free)(struct TMap*);          /*!< Free (ressources) method. */

    GtkWidget *widget;
    cairo_surface_t *surface;
    TController *controller;

} TMap ;


TMap* New_TMap(void);

void TMap_Init_Map(TMap *this);

void TMap_Draw_Hexagone(TMap *this, int x, int y, color_name_t color);

void TMap_Add_Arrow(TMap *this, int x1, int y1, int x2, int y2, color_name_t color);

void TMap_Reset_Map(TMap *this, color_name_t color);

void TMap_New_Free(TMap *this);

#endif
