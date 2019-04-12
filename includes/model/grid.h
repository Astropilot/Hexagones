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
 * @file model/grid.h
 * @brief Header file of the Grid model class.
 */

#ifndef MODEL_GRID_H_
#define MODEL_GRID_H_

#include <gtk/gtk.h>

#include "ui/color/color.h"
#include "utils.h"

typedef struct TController TController;
typedef struct THex THex;

/**
 * @brief An class representing the model of the hexagonal map.
 *
 * TGridModel is a class representing the model of the hexagonal map.
 */
typedef struct TGridModel {

    void(*Change_Start)(struct TGridModel*, int, int);                          /*!< Method to change the start tile position. */

    void(*Change_Goal)(struct TGridModel*, int, int);                           /*!< Method to change the goal tile position. */

    void(*Random)(struct TGridModel*);                                          /*!< Method to randomly change the type of the tiles. */

    double(*Distance)(struct TGridModel*, THex*, THex*);                        /*!< Method to obtain the cost of moving between two neighbouring tiles. */

    double(*Empty_Distance)(struct TGridModel*, THex*, THex*);                  /*!< Method for obtaining the empty distance between two tiles. */

    THex**(*Get_Neighbors)(struct TGridModel*, THex*, unsigned int);            /*!< Method for obtaining the neighbors of a tile. */

    arrow_id_t(*Add_Arrow)(struct TGridModel*, THex*, THex*, color_name_t);     /*!< Method for displaying an arrow between two tiles. */

    void(*Remove_Arrow)(struct TGridModel*, arrow_id_t);                        /*!< Method for removing an arrow between two tiles. */

    text_id_t(*Add_Text)(struct TGridModel*, THex*, const char*);               /*!< Method for displaying an text on a tile. */

    void(*Remove_Text)(struct TGridModel*, text_id_t);                          /*!< Method for removing an text on a tile. */

    void(*Reset_Model)(struct TGridModel*, color_name_t);                       /*!< Method for resetting the model. */

    void(*Reset_Results)(struct TGridModel*);                                   /*!< Method for removing all the arrows and texts. */

    void(*Free)(struct TGridModel*);                                            /*!< Free (ressources) method. */

    TController *observator;        /*!< The controller instance. */
    THex ***hexs;                   /*!< The list of all the tiles on the map. */
    THex *start;                    /*!< The start tile. */
    THex *goal;                     /*!< The goal tile. */

} TGridModel ;

/**
 * @brief The constructor for create a TGridModel object.
 *
 * @param observator A pointer to the controller instance.
 * @return A memory allocated object of the grid model.
 */
TGridModel *New_TGridModel(TController *observator);


/**
 * @brief Method to change the start tile position.
 *
 * @param this A pointer to the grid model object.
 * @param x The new x position of the start tile.
 * @param y The new y position of the start tile.
 *
 * You do not have to call this method directly. You must use the
 * Change_Start method of the TGridModel structure like this:
 * model->Change_Start(model, 0, 0);
 */
void TGridModel_Change_Start(TGridModel *this, int x, int y);

/**
 * @brief Method to change the goal tile position.
 *
 * @param this A pointer to the grid model object.
 * @param x The new x position of the goal tile.
 * @param y The new y position of the goal tile.
 *
 * You do not have to call this method directly. You must use the
 * Change_Goal method of the TGridModel structure like this:
 * model->Change_Goal(model, 0, 0);
 */
void TGridModel_Change_Goal(TGridModel *this, int x, int y);

/**
 * @brief Method to randomly change the type of the tiles.
 *
 * @param this A pointer to the grid model object.
 *
 * You do not have to call this method directly. You must use the
 * Random method of the TGridModel structure like this:
 * model->Random(model);
 */
void TGridModel_Random(TGridModel *this);

/**
 * @brief Method to obtain the cost of moving between two neighbouring tiles.
 *
 * @param this A pointer to the grid model object.
 * @param hex1 The first tile.
 * @param hex2 The second tile.
 * @return The distance between the two neighbouring tiles.
 *
 * You do not have to call this method directly. You must use the
 * Distance method of the TGridModel structure like this:
 * model->Distance(model, hex1, hex2);
 */
double TGridModel_Distance(TGridModel *this, THex *hex1, THex *hex2);

/**
 * @brief Method for obtaining the empty distance between two tiles.
 *
 * @param this A pointer to the grid model object.
 * @param hex1 The first tile.
 * @param hex2 The second tile.
 * @return The empty distance between the two tiles.
 *
 * You do not have to call this method directly. You must use the
 * Empty_Distance method of the TGridModel structure like this:
 * model->Empty_Distance(model, hex1, hex2);
 */
double TGridModel_Empty_Distance(TGridModel *this, THex *hex1, THex *hex2);

/**
 * @brief Method for obtaining the neighbors of a tile.
 *
 * @param this A pointer to the grid model object.
 * @param hex The tile.
 * @param all If all is 1, the function also returns the walls.
 * @return A list of neighbors.
 *
 * You do not have to call this method directly. You must use the
 * Get_Neighbors method of the TGridModel structure like this:
 * model->Get_Neighbors(model, hex1, 0);
 */
THex **TGridModel_Get_Neighbors(TGridModel *this, THex *hex, unsigned int all);

/**
 * @brief Method for displaying an arrow between two tiles.
 *
 * @param this A pointer to the grid model object.
 * @param hex1 The source tile.
 * @param hex2 The destination tile.
 * @param color The color name of the arrow.
 * @return A unique ID representing the arrow.
 *
 * You do not have to call this method directly. You must use the
 * Add_Arrow method of the TGridModel structure like this:
 * model->Add_Arrow(model, hex1, hex2, BLUE);
 */
arrow_id_t TGridModel_Add_Arrow(TGridModel *this, THex *hex1, THex *hex2, color_name_t color);

/**
 * @brief Method for removing an arrow between two tiles.
 *
 * @param this A pointer to the grid model object.
 * @param arrow The ID of the arrow to remove.
 *
 * You do not have to call this method directly. You must use the
 * Remove_Arrow method of the TGridModel structure like this:
 * model->Remove_Arrow(model, arrow_id);
 */
void TGridModel_Remove_Arrow(TGridModel *this, arrow_id_t arrow);


/**
 * @brief Method for displaying an text (label) on a tile.
 *
 * @param this A pointer to the grid model object.
 * @param hex The tile concerned.
 * @param text The text to add.
 * @return A unique ID representing the label.
 *
 * You do not have to call this method directly. You must use the
 * Add_Text method of the TGridModel structure like this:
 * model->Add_Text(model, hex1, "MyText");
 */
text_id_t TGridModel_Add_Text(TGridModel *this, THex *hex, const char *text);


/**
 * @brief Method for removing an text on a tile.
 *
 * @param this A pointer to the grid model object.
 * @param text The ID of the label to remove.
 *
 * You do not have to call this method directly. You must use the
 * Remove_Text method of the TGridModel structure like this:
 * model->Remove_Text(model, label_id);
 */
void TGridModel_Remove_Text(TGridModel *this, text_id_t text);

/**
 * @fn void TGridModel_Reset_Model(TGridModel *this, color_name_t color)
 * @brief Method for resetting the model.
 *
 * @param this A pointer to the grid model object.
 * @param color The color to apply to all tiles.
 *
 * You do not have to call this method directly. You must use the
 * Reset_Model method of the TGridModel structure like this:
 * model->Reset_Model(model, WHITE);
 */
void TGridModel_Reset_Model(TGridModel *this, color_name_t color);

/**
 * @fn void TGridModel_Reset_Results(TGridModel *this)
 * @brief Method for removing all the arrows and texts.
 *
 * @param this A pointer to the grid model object.
 *
 * You do not have to call this method directly. You must use the
 * Reset_Results method of the TGridModel structure like this:
 * model->Reset_Results(model);
 */
void TGridModel_Reset_Results(TGridModel *this);

/**
 * @fn void TGridModel_New_Free(TGridModel *this)
 * @brief Method to free all ressources take by the grid model.
 *
 * @param this A pointer to the grid model object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TGridModel structure like this:
 * model->Free(model);
 */
void TGridModel_New_Free(TGridModel *this);

#endif
