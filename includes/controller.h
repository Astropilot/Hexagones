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

typedef struct TMainWindow TMainWindow;

typedef struct TController {

    void(*Free)(struct TController*);       /*!< Free (ressources) method. */

    TMainWindow *view;
    //TModel *model;

} TController ;


TController* New_TController(void);

void TController_New_Free(TController *this);

#endif
