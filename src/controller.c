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

#include <gtk/gtk.h>
#include <stdlib.h>

#include "main.h"
#include "controller.h"

static TController *singleton_instance = NULL;

TController* New_TController()
{
    TController *this = singleton_instance;

    if (!this)
        this = malloc(sizeof(TController));
    else
        return (this);

    if(!this) return (NULL);

    this->Free = TController_New_Free;
    singleton_instance = this;
    return (this);
}

void TController_New_Free(TController *this)
{
    free(this);
}
