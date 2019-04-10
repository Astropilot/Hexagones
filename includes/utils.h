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
 * @file utils.h
 */

#ifndef UTILS_H_
#define UTILS_H_

#define M_PI 3.14159265358979323846

#include "ui/color.h"

typedef struct THex THex;

typedef struct arrow_id_t {
    unsigned int is_arrow;
    THex *hex_src;
    THex *hex_dst;
    color_name_t arrow_color;
    unsigned int uid_src;
    unsigned int uid_dst;
} arrow_id_t;

/*typedef struct text_id_t {
    char *text;
    THex *hex;
    color_name_t text_color;
} text_id_t;*/

/**
 * @fn int rand_range_int(int min, int max)
 * @brief Return a random integer between a min and a max given.
 *
 * @param min The minimum value.
 * @param max The maximum value.
 * @return A random integer.
 */
int rand_range_int(int min, int max);

#endif
