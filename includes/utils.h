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

#define M_PI 3.14159265358979323846 /*!< The actual value of PI. */

#include "ui/color/color.h"

typedef struct THex THex;

/**
 * @brief A structure representing a pair of integers.
 */
typedef struct int_pair_t {
    int p1;     /*!< The first integer. */
    int p2;     /*!< The second integer. */
} int_pair_t ;

/**
 * @brief A structure representing a unique ID for tile arrows.
 */
typedef struct arrow_id_t {
    unsigned int is_arrow;      /*!< A boolean to know if arrow is present. */
    THex *hex_src;              /*!< The tile where the arrow start. */
    THex *hex_dst;              /*!< The tile where the arrow end. */
    color_name_t arrow_color;   /*!< The color name of the arrow. */
    unsigned int uid_src;       /*!< A internal ID for the tile source side. */
    unsigned int uid_dst;       /*!< A internal ID for the tile destination side. */
} arrow_id_t;

/**
 * @brief A structure representing a unique ID for tile labels.
 */
typedef struct text_id_t {
    char *text;     /*!< The text in the label (can be NULL, no label). */
    THex *hex;      /*!< The tile concerned. */
} text_id_t;

/**
 * @brief Return a random integer between a min and a max given.
 *
 * @param min The minimum value.
 * @param max The maximum value.
 * @return A random integer.
 */
int rand_range_int(int min, int max);

#endif
