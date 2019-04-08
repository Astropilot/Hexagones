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
 * @file ui/window.h
 * @brief Header file of the Main Window class.
 */

#ifndef UI_WINDOW_H_
#define UI_WINDOW_H_

#include <gtk/gtk.h>

#include "controller.h"

typedef struct TPalette TPalette;
typedef struct TMap TMap;

typedef struct TMainWindow {

    int(*Start_View)(struct TMainWindow*);

    void(*Free)(struct TMainWindow*);       /*!< Free (ressources) method. */

    GtkApplication *app;
    GtkWidget *window;
    TPalette *palette;
    TMap *map;
    TController *controller;
    GtkWidget **menu_items;

} TMainWindow ;


TMainWindow* New_TMainWindow(void);

int TMainWindow_Start_View(TMainWindow *this);

void TMainWindow_New_Free(TMainWindow *this);

#endif
