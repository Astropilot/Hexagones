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
 * @file controller.h
 * @brief Header file of the controller class.
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <gtk/gtk.h>

#include "utils.h"

typedef struct TMainWindow TMainWindow;
typedef struct TGridModel TGridModel;
typedef struct THex THex;

typedef struct TController {

    void(*On_MenuChange)(struct TController*, const char*);

    void(*On_PaletteChange)(struct TController*, const char*);

    void(*On_LeftClick)(struct TController*, int, int);

    void(*Update_Hex)(struct TController*, THex*);

    void(*Free)(struct TController*);       /*!< Free (ressources) method. */

    TMainWindow *view;
    TGridModel *model;
    char *hex_choice;

} TController ;


TController* New_TController(void);

void TController_On_MenuChange(TController *this, const char *label);

void TController_On_PaletteChange(TController *this, const char *label);

void TController_On_LeftClick(TController *this, int x, int y);

void TController_Update_Hex(TController *this, THex *hex);

void TController_New_Free(TController *this);

#endif
