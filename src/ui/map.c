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
#include "ui/map.h"
#include "controller.h"

static TMap *singleton_instance = NULL;

TMap* New_TMap(void)
{
    TMap *this = singleton_instance;

    if (!this)
        this = malloc(sizeof(TMap));
    else
        return (this);

    if(!this) return (NULL);

    this->Init_Map = TMap_Init_Map;
    this->Free = TMap_New_Free;
    singleton_instance = this;
    return (this);
}

static gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    guint width, height;
    GtkStyleContext *context;
    int i, j;

    context = gtk_widget_get_style_context(widget);

    width = gtk_widget_get_allocated_width(widget);
    height = gtk_widget_get_allocated_height(widget);

    gtk_render_background(context, cr, 0, 0, width, height);

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);

    for(i = 0; i < MAP_WIDTHX; i++) {
        for (j = 0; j < MAP_HEIGHTY; j++) {
            int x = 2*MAP_HEX_UNIT+ (3*MAP_HEX_UNIT+1)*i;
            int y = 2*MAP_HEX_UNIT +(4*MAP_HEX_UNIT+1)*j +(2*MAP_HEX_UNIT)*(i%2);

            cairo_set_source_rgb(cr, 0, 0, 0);
            cairo_set_line_width(cr, 1);

            cairo_line_to(cr, x+2*MAP_HEX_UNIT, y);
            cairo_line_to(cr, x+MAP_HEX_UNIT, y+2*MAP_HEX_UNIT);
            cairo_line_to(cr, x- MAP_HEX_UNIT, y+2*MAP_HEX_UNIT);
            cairo_line_to(cr, x-2*MAP_HEX_UNIT, y);
            cairo_line_to(cr, x-MAP_HEX_UNIT, y-2*MAP_HEX_UNIT);
            cairo_line_to(cr, x+MAP_HEX_UNIT, y-2*MAP_HEX_UNIT);
            cairo_line_to(cr, x+2*MAP_HEX_UNIT, y);

            cairo_close_path(cr);
            cairo_stroke_preserve(cr);
            cairo_set_source_rgb(cr, 1, 1, 1);
            cairo_fill(cr);
        }
    }

    (void)data;
    return FALSE;
}

void TMap_Init_Map(TMap *this)
{
    this->widget = gtk_drawing_area_new();

    gtk_widget_set_size_request(this->widget, MAP_WIDTH, MAP_HEIGHT);
    g_signal_connect(G_OBJECT(this->widget), "draw", G_CALLBACK(draw_callback), NULL);
}

void TMap_New_Free(TMap *this)
{
    free(this);
}
