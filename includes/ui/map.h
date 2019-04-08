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

    void(*Free)(struct TMap*);          /*!< Free (ressources) method. */

    GtkWidget *widget;
    TController *controller;

} TMap ;


TMap* New_TMap(void);

void TMap_Init_Map(TMap *this);

void TMap_New_Free(TMap *this);

#endif
