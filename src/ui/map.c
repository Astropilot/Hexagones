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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "main.h"
#include "ui/map.h"
#include "ui/color.h"
#include "controller.h"

#define M_PI 3.14159265358979323846

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
    this->Draw_Hexagone = TMap_Draw_Hexagone;
    this->Add_Arrow = TMap_Add_Arrow;
    this->Reset_Map = TMap_Reset_Map;
    this->Free = TMap_New_Free;
    this->surface = NULL;
    this->widget = NULL;
    this->controller = NULL;
    singleton_instance = this;
    return (this);
}

static void find_closest_hex(gdouble x, gdouble y, int *i, int *j)
{
    int ii, jj;

    int rx = (int)round(x);
    int ry = (int)round(y);

    int imin, jmin = -1;
    double min = 99999999;
    for(ii = 0; ii < MAP_WIDTHX; ii++) {
        for (jj = 0; jj < MAP_HEIGHTY; jj++) {
            int xx = 2*MAP_HEX_UNIT+ (3*MAP_HEX_UNIT+1)*ii;
            int yy = 2*MAP_HEX_UNIT +(4*MAP_HEX_UNIT+1)*jj +(2*MAP_HEX_UNIT)*(ii%2);
            double distance = sqrt(pow(xx - rx, 2) + pow(yy - ry, 2));
            if (distance < (MAP_HEX_UNIT*2) && distance < min) {
                min = distance;
                imin = ii;
                jmin = jj;
            }
        }
    }
    *i = imin;
    *j = jmin;
}

static void draw_hexagone(GtkWidget *widget, int i, int j, rgb_color_t bg_color, unsigned int redraw)
{
    cairo_t *cr;
    rgb_color_t fg_color = colors[BLACK];
    int x = 2*MAP_HEX_UNIT+ (3*MAP_HEX_UNIT+1)*i;
    int y = 2*MAP_HEX_UNIT +(4*MAP_HEX_UNIT+1)*j +(2*MAP_HEX_UNIT)*(i%2);

    cr = cairo_create(singleton_instance->surface);

    // Draw hexagone here.
    cairo_set_source_rgb(cr, fg_color.r, fg_color.g, fg_color.b);
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
    cairo_set_source_rgb(cr, bg_color.r, bg_color.g, bg_color.b);
    cairo_fill(cr);

    cairo_destroy(cr);

    if (redraw)
        gtk_widget_queue_draw_area(widget,
            x-2*MAP_HEX_UNIT, y-2*MAP_HEX_UNIT,
            (x+2*MAP_HEX_UNIT) - (x-2*MAP_HEX_UNIT), (y+2*MAP_HEX_UNIT) - (y-2*MAP_HEX_UNIT)
        );
}

static void draw_arrow(GtkWidget *widget, int i1, int j1, int i2, int j2, rgb_color_t color, unsigned int redraw)
{
    cairo_t *cr;
    int x1 = 2*MAP_HEX_UNIT+ (3*MAP_HEX_UNIT+1)*i1;
    int y1 = 2*MAP_HEX_UNIT +(4*MAP_HEX_UNIT+1)*j1 +(2*MAP_HEX_UNIT)*(i1%2);
    int x2 = 2*MAP_HEX_UNIT+ (3*MAP_HEX_UNIT+1)*i2;
    int y2 = 2*MAP_HEX_UNIT +(4*MAP_HEX_UNIT+1)*j2 +(2*MAP_HEX_UNIT)*(i2%2);

    double angle = atan2(y2 - y1, x2 - x1) + M_PI;

    double arr_x1 = x2 + 10 * cos(angle - 0.4);
    double arr_y1 = y2 + 10 * sin(angle - 0.4);
    double arr_x2 = x2 + 10 * cos(angle + 0.4);
    double arr_y2 = y2 + 10 * sin(angle + 0.4);
    double arr_x3 = x2 + 10 * cos(angle);
    double arr_y3 = y2 + 10 * sin(angle);

    cr = cairo_create(singleton_instance->surface);

    // Draw arrow here.
    cairo_set_line_width(cr, 4);

    cairo_move_to(cr, x1, y1);
    cairo_line_to(cr, arr_x3, arr_y3);
    cairo_close_path(cr);
    cairo_set_source_rgb(cr, color.r, color.g, color.b);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr, color.r, color.g, color.b);
    cairo_fill(cr);

    cairo_set_line_width(cr, 1);
    cairo_move_to(cr, x2, y2);
    cairo_line_to(cr, arr_x1, arr_y1);
    cairo_line_to(cr, arr_x2, arr_y2);

    cairo_close_path(cr);
    cairo_set_source_rgb(cr, color.r, color.g, color.b);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr, color.r, color.g, color.b);
    cairo_fill(cr);

    cairo_destroy(cr);

    if (redraw)
        gtk_widget_queue_draw(widget);
}

static void draw_text(GtkWidget *widget, int i, int j, const char *text, unsigned int redraw)
{
    cairo_t *cr;
    rgb_color_t text_color = colors[BLACK];
    int x = 2*MAP_HEX_UNIT+ (3*MAP_HEX_UNIT+1)*i - MAP_HEX_UNIT;
    int y = 2*MAP_HEX_UNIT +(4*MAP_HEX_UNIT+1)*j +(2*MAP_HEX_UNIT)*(i%2);

    cr = cairo_create(singleton_instance->surface);

    // Draw text here.
    cairo_set_source_rgb(cr, text_color.r, text_color.g, text_color.b);
    cairo_set_font_size(cr, 11);
    cairo_move_to(cr, x, y);
    cairo_show_text(cr, text);

    cairo_destroy(cr);

    x += MAP_HEX_UNIT;
    if (redraw)
        gtk_widget_queue_draw_area(widget,
            x-2*MAP_HEX_UNIT, y-2*MAP_HEX_UNIT,
            (x+2*MAP_HEX_UNIT) - (x-2*MAP_HEX_UNIT), (y+2*MAP_HEX_UNIT) - (y-2*MAP_HEX_UNIT)
        );
}

static gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    cairo_set_source_surface(cr, singleton_instance->surface, 0, 0);
    cairo_paint(cr);

    (void)*widget;
    (void)data;
    return (FALSE);
}

static gboolean config_event_callback(GtkWidget *widget, GdkEventConfigure *event, gpointer data)
{
    cairo_t *cr;
    rgb_color_t bg_color = colors[BLACK];
    int i, j;

    if (singleton_instance->surface)
        cairo_surface_destroy(singleton_instance->surface);

    singleton_instance->surface = gdk_window_create_similar_surface(
        gtk_widget_get_window(widget),
        CAIRO_CONTENT_COLOR,
        gtk_widget_get_allocated_width(widget),
        gtk_widget_get_allocated_height(widget)
    );

    cr = cairo_create(singleton_instance->surface);
    cairo_set_source_rgb(cr, bg_color.r, bg_color.g, bg_color.b);
    cairo_paint(cr);
    cairo_destroy(cr);

    for(i = 0; i < MAP_WIDTHX; i++) {
        for (j = 0; j < MAP_HEIGHTY; j++) {
            draw_hexagone(widget, i, j, colors[WHITE], 0);
        }
    }

    (void)*event;
    (void)data;
    return (TRUE);
}

static gboolean press_callback(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    if (!singleton_instance->surface) return (FALSE);

    if (event->button == GDK_BUTTON_PRIMARY) {
        int i, j;

        find_closest_hex(event->x, event->y, &i, &j);
        if (i != -1 && j != -1) {
            singleton_instance->controller->On_LeftClick(
                singleton_instance->controller, i, j
            );
        }
    }

    (void)*widget;
    (void)data;
    return (TRUE);
}

static gboolean motion_callback(GtkWidget *widget, GdkEventMotion *event, gpointer data)
{
    if (!singleton_instance->surface) return (FALSE);

    if (event->state & GDK_BUTTON1_MASK) {
        int i, j;

        find_closest_hex(event->x, event->y, &i, &j);
        if (i != -1 && j != -1) {
            singleton_instance->controller->On_LeftClick(
                singleton_instance->controller, i, j
            );
        }
    }

    (void)*widget;
    (void)data;
    return (TRUE);
}

void TMap_Init_Map(TMap *this)
{
    this->widget = gtk_drawing_area_new();

    gtk_widget_set_size_request(this->widget, MAP_WIDTH, MAP_HEIGHT);

    g_signal_connect(G_OBJECT(this->widget), "draw",
        G_CALLBACK(draw_callback), NULL
    );
    g_signal_connect(G_OBJECT(this->widget), "configure-event",
        G_CALLBACK(config_event_callback), NULL
    );
    g_signal_connect(G_OBJECT(this->widget), "motion-notify-event",
        G_CALLBACK(motion_callback), NULL
    );
    g_signal_connect(G_OBJECT(this->widget), "button-press-event",
        G_CALLBACK(press_callback), NULL
    );

    gtk_widget_set_events(this->widget,
        gtk_widget_get_events (this->widget)
        | GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK
    );
}

void TMap_Draw_Hexagone(TMap *this, int x, int y, color_name_t color)
{
    draw_hexagone(this->widget, x, y, colors[color], 1);
}

void TMap_Add_Arrow(TMap *this, int x1, int y1, int x2, int y2, color_name_t color)
{
    draw_arrow(this->widget, x1, y1, x2, y2, colors[color], 1);
}

void TMap_Reset_Map(TMap *this, color_name_t color)
{
    int i, j;

    for(i = 0; i < MAP_WIDTHX; i++) {
        for (j = 0; j < MAP_HEIGHTY; j++) {
            draw_hexagone(this->widget, i, j, colors[color], 1);
        }
    }
}

void TMap_New_Free(TMap *this)
{
    if (this) {
        if (this->surface)
          cairo_surface_destroy(this->surface);
    }
    free(this);
    singleton_instance = NULL;
}
