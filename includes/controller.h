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

/**
 * @brief An class representing the controller.
 *
 * TMap is a class representing the controller.
 */
typedef struct TController {

    void(*On_MenuChange)(struct TController*, const char*);     /*!< Method for handling the main menu change callback. */

    void(*On_PaletteChange)(struct TController*, const char*);  /*!< Method for handling the palette choice change callback. */

    void(*On_LeftClick)(struct TController*, int, int);         /*!< Method for handling the left click on map callback. */

    void(*Update_Hex)(struct TController*, THex*);              /*!< Method for ask the view to redraw a tile. */

    void(*Update_Screen)(struct TController*);                  /*!< Method for ask the view to process the events pool. */

    void(*Free)(struct TController*);                           /*!< Free (ressources) method. */

    TMainWindow *view;          /*!< The view instance. */
    TGridModel *model;          /*!< The model instance. */
    char *hex_choice;           /*!< The actual hexagone type choice for drawing on left click. */

} TController ;

/**
 * @brief The constructor for create a TController object.
 *
 * @return A memory allocated object of the controller.
 */
TController* New_TController(void);

/**
 * @brief Method for handling the main menu change callback.
 *
 * @param this A pointer to the controller object.
 * @param label The label clicked by the user.
 *
 * You do not have to call this method directly. You must use the
 * On_MenuChange method of the TController structure like this:
 * controller->On_MenuChange(controller, "MyLabel");
 */
void TController_On_MenuChange(TController *this, const char *label);

/**
 * @brief Method for handling the palette choice change callback.
 *
 * @param this A pointer to the controller object.
 * @param label The palette choice clicked by the user.
 *
 * You do not have to call this method directly. You must use the
 * On_PaletteChange method of the TController structure like this:
 * controller->On_PaletteChange(controller, "MyChoice");
 */
void TController_On_PaletteChange(TController *this, const char *label);


/**
 * @brief Method for handling the left click on map callback.
 *
 * @param this A pointer to the controller object.
 * @param x The x position of the tile clicked.
 * @param y The y position of the tile clicked.
 *
 * You do not have to call this method directly. You must use the
 * On_LeftClick method of the TController structure like this:
 * controller->On_LeftClick(controller, 0, 1);
 */
void TController_On_LeftClick(TController *this, int x, int y);

/**
 * @brief Method for ask the view to redraw a tile.
 *
 * @param this A pointer to the controller object.
 * @param hex The tile to redraw.
 *
 * You do not have to call this method directly. You must use the
 * Update_Hex method of the TController structure like this:
 * controller->Update_Hex(controller, hex);
 */
void TController_Update_Hex(TController *this, THex *hex);

/**
 * @brief Method for ask the view to process the events pool.
 *
 * @param this A pointer to the controller object.
 *
 * You do not have to call this method directly. You must use the
 * Update_Screen method of the TController structure like this:
 * controller->Update_Screen(controller);
 */
void TController_Update_Screen(TController *this);

/**
 * @brief Method to free all ressources take by the controller.
 *
 * @param this A pointer to the controller object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TController structure like this:
 * controller->Free(controller);
 */
void TController_New_Free(TController *this);

#endif
