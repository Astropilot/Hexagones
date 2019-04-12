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
 * @file main.h
 * @brief The globals Hexagones constants.
 *
 * This file define some globals constants.
 *
 */

#ifndef MAIN_H_
#define MAIN_H_

#define MAP_WIDTHX 45           /*!< The map width.*/
#define MAP_HEIGHTY 20          /*!< The map height.*/
#define MAP_HEX_UNIT 8          /*!< The unit of a hexagone.*/

#define MAP_HEIGHT (4*MAP_HEX_UNIT+1)*(MAP_HEIGHTY+0.5)     /*!< The map height in pixels. */
#define MAP_WIDTH  (3*MAP_HEX_UNIT+1)*(MAP_WIDTHX+0.5)      /*!< The map width in pixels. */

#endif
