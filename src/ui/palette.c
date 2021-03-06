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
#include "ui/palette.h"
#include "controller.h"

static TPalette *singleton_instance = NULL;

static gboolean callback_palettechoice(GtkWidget *button, gpointer user_data);

static char *hex_types[] = {
    "Wall",
    "Nothing",
    "Water",
    "Grass",
    "Sand",
    "Start",
    "Goal",
    NULL
};

TPalette* New_TPalette(void)
{
    TPalette *this = singleton_instance;

    if (!this)
        this = malloc(sizeof(TPalette));
    else
        return (this);

    if(!this) return (NULL);

    this->Init_Palette = TPalette_Init_Palette;
    this->Free = TPalette_New_Free;
    singleton_instance = this;
    return (this);
}

void TPalette_Init_Palette(TPalette *this)
{
    GtkWidget *radio_owner;
    GtkWidget *radio;
    char **hex_type = hex_types;

    this->widget = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);

    radio_owner = gtk_radio_button_new_with_label(NULL, *hex_type);
    hex_type++;
    g_signal_connect(GTK_TOGGLE_BUTTON(radio_owner), "toggled", G_CALLBACK(callback_palettechoice), NULL);

    gtk_box_pack_start(GTK_BOX(this->widget),
        radio_owner, FALSE, FALSE, 0
    );

    while (*hex_type) {
        radio = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_owner), *hex_type);

        gtk_box_pack_start(GTK_BOX(this->widget),
            radio, FALSE, FALSE, 0
        );
        g_signal_connect(GTK_TOGGLE_BUTTON(radio), "toggled", G_CALLBACK(callback_palettechoice), NULL);
        hex_type++;
    }
}

static gboolean callback_palettechoice(GtkWidget *button, gpointer user_data)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button))) {
        singleton_instance->controller->On_PaletteChange(
            singleton_instance->controller,
            gtk_button_get_label(GTK_BUTTON(button))
        );
    }
    (void)user_data;
    return (FALSE);
}

void TPalette_New_Free(TPalette *this)
{
    free(this);
    singleton_instance = NULL;
}
