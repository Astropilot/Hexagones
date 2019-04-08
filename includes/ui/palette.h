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
 * @file ui/palette.h
 * @brief Header file of the Palette class.
 */

#ifndef UI_PALETTE_H_
#define UI_PALETTE_H_

#include <gtk/gtk.h>

#include "controller.h"

typedef struct TPalette {

    void(*Init_Palette)(struct TPalette*);

    void(*Free)(struct TPalette*);          /*!< Free (ressources) method. */

    GtkWidget *widget;
    TController *controller;

} TPalette ;


TPalette* New_TPalette(void);

void TPalette_Init_Palette(TPalette *this);

void TPalette_New_Free(TPalette *this);

#endif
