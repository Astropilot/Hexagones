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
 * @file ui/color/color_names.h
 * @brief Some predefined colors.
 */

#ifndef UI_COLOR_NAME_H_
#define UI_COLOR_NAME_H_

#include "ui/color/color.h"

static rgba_color_t colors[] = {
    [WHITE] = {1.0, 1.0, 1.0, 1.0},
    [BLACK] = {0.0, 0.0, 0.0, 1.0},
    [BLUE] = {0.0, 0.0, 1.0, 1.0},
    [RED] = {1.0, 0.0, 0.0, 1.0},
    [GREEN] = {0.0, 1.0, 0.0, 1.0},
    [YELLOW] = {1.0, 1.0, 0.0, 1.0},
    [MAGENTA] = {1.0, 0.0, 1.0, 1.0},
    [GRAY] = {0.5, 0.5, 0.5, 0.5}
};  /*!< A list of predefined colors. */

#endif
