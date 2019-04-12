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
 * @file ui/color/color.h
 * @brief Colors utils.
 */

#ifndef UI_COLOR_H_
#define UI_COLOR_H_

/**
 * @brief Predefined color constants.
 *
 * color_name_t is a series of predefined color constants.
 */
typedef enum color_name_t {
    WHITE,      /*!< The white color. */
    BLACK,      /*!< The black color. */
    BLUE,       /*!< The blue color. */
    RED,        /*!< The red color. */
    GREEN,      /*!< The green color. */
    YELLOW,     /*!< The yellow color. */
    MAGENTA,    /*!< The magenta color. */
    GRAY        /*!< The gray color at 50% opacity. */
} color_name_t ;


/**
 * @brief structure representing a RGBA color.
 *
 * rgba_color_t is an RGBA color.
 */
typedef struct rgba_color_t {
    double r;       /*!< The proportion of red in the color. */
    double g;       /*!< The proportion of green in the color. */
    double b;       /*!< The proportion of blue in the color. */
    double a;       /*!< The opacity (alpha) of the color. */
} rgba_color_t ;

#endif
