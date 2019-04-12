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

/**
 * @brief An class representing the main window.
 *
 * TMap is a class representing the main window.
 */
typedef struct TMainWindow {

    int(*Start_View)(struct TMainWindow*);      /*!< Method to create the main window and these dependencies. */

    void(*Update_Screen)(struct TMainWindow*);  /*!< Method for process the window events pool. */

    void(*Free)(struct TMainWindow*);           /*!< Free (ressources) method. */

    GtkApplication *app;                        /*!< The GTK application. */
    GtkWidget *window;                          /*!< The GTK main widget. */
    TPalette *palette;                          /*!< The palette class. */
    TMap *map;                                  /*!< The UI map class. */
    TController *controller;                    /*!< The controller instance. */
    GtkWidget **menu_items;                     /*!< Internal variable for getting all main menu items. */

} TMainWindow ;

/**
 * @brief The constructor for create a TMainWindow object.
 *
 * @return A memory allocated object of the main window.
 */
TMainWindow* New_TMainWindow(void);

/**
 * @brief Method to create the main window and these dependencies.
 *
 * @param this A pointer to the main window object.
 * @return A boolean if the window has been created successfully.
 *
 * You do not have to call this method directly. You must use the
 * Start_View method of the TMainWindow structure like this:
 * window->Start_View(window);
 */
int TMainWindow_Start_View(TMainWindow *this);

/**
 * @brief Method for process the window events pool.
 *
 * @param this A pointer to the main window object.
 *
 * You do not have to call this method directly. You must use the
 * Update_Screen method of the TMainWindow structure like this:
 * window->Update_Screen(window);
 */
void TMainWindow_Update_Screen(TMainWindow *this);

/**
 * @brief Method to free all ressources take by the main window.
 *
 * @param this A pointer to the main window object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TMainWindow structure like this:
 * window->Free(window);
 */
void TMainWindow_New_Free(TMainWindow *this);

#endif
