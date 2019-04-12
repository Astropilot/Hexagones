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
#include "utils.h"

typedef struct THex THex;

/**
 * @brief An class representing the view of the hexagonal map.
 *
 * TMap is a class representing the view of the hexagonal map.
 */
typedef struct TMap {

    void(*Init_Map)(struct TMap*);                  /*!< Method to initialise the map on the window. */

    void(*Update_Hex)(struct TMap*, THex*);         /*!< Method for redrawing a tile in its entirety. */

    void(*Reset_Map)(struct TMap*, color_name_t);   /*!< Method to reset the map to its original state. */

    void(*Free)(struct TMap*);                      /*!< Free (ressources) method. */

    GtkWidget *widget;                              /*!< The GTK DrawingArea widget for drawing the map. */
    cairo_surface_t *surface;                       /*!< A cairo surface for all internal drawing operations. */
    TController *controller;                        /*!< The controller instance. */

} TMap ;

/**
 * @brief The constructor for create a TMap object.
 *
 * @return A memory allocated object of the map view.
 */
TMap* New_TMap(void);

/**
 * @brief Method to initialise the map on the window.
 *
 * @param this A pointer to the map view object.
 *
 * You do not have to call this method directly. You must use the
 * Init_Map method of the TMap structure like this:
 * map->Init_Map(map);
 */
void TMap_Init_Map(TMap *this);

/**
 * @brief Method for redrawing a tile in its entirety.
 *
 * @param this A pointer to the map view object.
 * @param hex The tile to redraw.
 *
 * You do not have to call this method directly. You must use the
 * Update_Hex method of the TMap structure like this:
 * map->Update_Hex(map, hex);
 */
void TMap_Update_Hex(TMap *this, THex *hex);

/**
 * @brief Method to reset the map to its original state.
 *
 * @param this A pointer to the map view object.
 * @param color The color to redraw all the tiles.
 *
 * You do not have to call this method directly. You must use the
 * Reset_Map method of the TMap structure like this:
 * map->Reset_Map(map, WHITE);
 */
void TMap_Reset_Map(TMap *this, color_name_t color);

/**
 * @brief Method to free all ressources take by the map view.
 *
 * @param this A pointer to the map view object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TMap structure like this:
 * map->Free(map);
 */
void TMap_New_Free(TMap *this);

#endif
