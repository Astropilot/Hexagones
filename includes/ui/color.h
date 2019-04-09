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
 * @file color.h
 * @brief Colors utils.
 */

#ifndef UI_COLOR_H_
#define UI_COLOR_H_

typedef enum color_name_t {
    WHITE,
    BLACK,
    BLUE,
    RED,
    GREEN,
    YELLOW,
    MAGENTA
} color_name_t ;

typedef struct rgb_color_t {
    double r;
    double g;
    double b;
} rgb_color_t ;

static rgb_color_t colors[] = {
    [WHITE] = {1.0, 1.0, 1.0},
    [BLACK] = {0.0, 0.0, 0.0},
    [BLUE] = {0.0, 0.0, 1.0},
    [RED] = {1.0, 0.0, 0.0},
    [GREEN] = {0.0, 1.0, 0.0},
    [YELLOW] = {1.0, 1.0, 0.0},
    [MAGENTA] = {1.0, 0.0, 1.0}
};

#endif
