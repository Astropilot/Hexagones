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

#include "utils.h"
#include "ui/color.h"

typedef struct TController TController;

typedef struct THex {

    void(*Change_Color)(struct THex*, color_name_t, unsigned int);

    void(*Free)(struct THex*);              /*!< Free (ressources) method. */

    int x;
    int y;
    color_name_t color;
    arrow_id_t *arrows;
    text_id_t label;
    TController *observator;

} THex ;

THex *New_THex(int x, int y, TController *observator);

void THex_Change_Color(THex *this, color_name_t color, unsigned int notify);

void THex_New_Free(THex *this);

#endif
