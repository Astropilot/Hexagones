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

/**
 * @brief An class representing the palette of tile types.
 *
 * TMap is a class representing the palette of tile types.
 */
typedef struct TPalette {

    void(*Init_Palette)(struct TPalette*);  /*!< Initializes the graphical widget responsible for the palette. */

    void(*Free)(struct TPalette*);          /*!< Free (ressources) method. */

    GtkWidget *widget;                      /*!< The GTK widget for the palette. */
    TController *controller;                /*!< The controller instance. */

} TPalette ;

/**
 * @brief The constructor for create a TPalette object.
 *
 * @return A memory allocated object of the palette view.
 */
TPalette* New_TPalette(void);

/**
 * @brief Initializes the graphical widget responsible for the palette.
 *
 * @param this A pointer to the palette view object.
 *
 * You do not have to call this method directly. You must use the
 * Init_Palette method of the TPalette structure like this:
 * palette->Init_Palette(palette);
 */
void TPalette_Init_Palette(TPalette *this);

/**
 * @brief Method to free all ressources take by the palette view.
 *
 * @param this A pointer to the palette view object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TPalette structure like this:
 * palette->Free(palette);
 */
void TPalette_New_Free(TPalette *this);

#endif
