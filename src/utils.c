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

#include <stdlib.h>
#include <time.h>

#include "utils.h"

int rand_range_int(int min, int max)
{
    static int rand_init = 0;

    if (!rand_init) {
        srand((unsigned int)time(NULL));
        rand_init = 1;
    }
    return ( rand() % (max + 1 - min) ) + min;
}
