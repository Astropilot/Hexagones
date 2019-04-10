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
#include "ui/window.h"
#include "controller.h"

int main(void)
{
    TController *controller = New_TController();
    TMainWindow *window = New_TMainWindow();

    int status = EXIT_FAILURE;

    if (window && controller) {
        window->controller = controller;
        controller->view = window;
        status = window->Start_View(window);
    }

    if (window)
        window->Free(window);
    if (controller)
        controller->Free(controller);

    (void)colors;
    return (status);
}
