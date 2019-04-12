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
#include "ui/color/color.h"

typedef struct TController TController;

/**
 * @brief An class representing the model of a hexagonal tile.
 *
 * TGridModel is a class representing the model of a hexagonal tile.
 */
typedef struct THex {

    void(*Change_Color)(struct THex*, color_name_t, unsigned int);      /*!< Method for changing the color (type) of the tile. */

    void(*Free)(struct THex*);                                          /*!< Free (ressources) method. */

    int x;                          /*!< The position of the tile on the abscissa axis. */
    int y;                          /*!< The position of the tile on the y-axis. */
    color_name_t color;             /*!< The color (type) of the tile. */
    arrow_id_t *arrows;             /*!< The list of the possible 6 arrows on the tile. */
    text_id_t label;                /*!< A optionnal textual label on the tile. */
    TController *observator;        /*!< The controller instance. */

} THex ;

/**
 * @brief The constructor for create a THex object.
 *
 * @param x The x position of the tile.
 * @param y The y position of the tile.
 * @param observator A pointer to the controller instance.
 * @return A memory allocated object of the hexagonal tile.
 */
THex *New_THex(int x, int y, TController *observator);

/**
 * @brief Method for changing the color (type) of the tile.
 *
 * @param this A pointer to the tile object.
 * @param color The new color (type) of the tile.
 * @param notify Boolean to know if the view will redraw the tile.
 *
 * You do not have to call this method directly. You must use the
 * Change_Color method of the TGridModel structure like this:
 * hex->Change_Color(hex, GREEN, 1);
 */
void THex_Change_Color(THex *this, color_name_t color, unsigned int notify);

/**
 * @brief Method to free all ressources take by the tile.
 *
 * @param this A pointer to the tile object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the THex structure like this:
 * hex->Free(hex);
 */
void THex_New_Free(THex *this);

#endif
