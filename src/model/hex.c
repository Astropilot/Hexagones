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

#include <gtk/gtk.h>
#include <stdlib.h>

#include "model/hex.h"
#include "controller.h"
#include "utils.h"
#include "ui/color.h"

THex *New_THex(int x, int y, TController *observator)
{
    THex *this = malloc(sizeof(THex));
    int i;

    if(!this) return (NULL);

    this->Change_Color = THex_Change_Color;
    this->Free = THex_New_Free;
    this->x = x;
    this->y = y;
    this->observator = observator;
    this->color = WHITE;
    this->arrows = malloc(6 * sizeof(arrow_id_t));
    for (i = 0; i < 6; i++)
        this->arrows[i].is_arrow = 0;
    //this->label.text = NULL;
    return (this);
}

void THex_Change_Color(THex *this, color_name_t color, unsigned int notify)
{
    if (!this) return;

    this->color = color;
    if (notify)
        this->observator->Update_Hex(this->observator, this);
    (void)colors;
}

void THex_New_Free(THex *this)
{
    if (this) {
        free(this->arrows);
    }
    free(this);
}
