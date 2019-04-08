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

static TMainWindow *singleton_instance = NULL;

static void activate(GtkApplication* app, gpointer user_data);
static void all_white(void);

TMainWindow* New_TMainWindow()
{
    TMainWindow *this = singleton_instance;

    if (!this)
        this = malloc(sizeof(TMainWindow));
    else
        return (this);

    if(!this) return (NULL);

    this->Start_View = TMainWindow_Start_View;
    this->Free = TMainWindow_New_Free;
    singleton_instance = this;
    return (this);
}

int TMainWindow_Start_View(TMainWindow *this)
{
    int status;

    this->app = gtk_application_new("astropilot.hexagones", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(this->app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(this->app), 0, NULL);
    g_object_unref(this->app);

    return (status);
}

static void activate(GtkApplication* app, gpointer user_data)
{
    GtkWidget *menubar;
    GtkWidget *app_box;
    GtkWidget *menu_all_white;

    singleton_instance->window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(singleton_instance->window), "Hexagones");
    gtk_window_set_default_size(GTK_WINDOW(singleton_instance->window), WIN_WIDTH, WIN_HEIGHT);

    app_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(singleton_instance->window), app_box);

    menubar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(app_box), menubar, FALSE, FALSE, 0);

    menu_all_white = gtk_menu_item_new_with_label("Tout blanc");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_all_white);

    g_signal_connect(menu_all_white, "activate", G_CALLBACK(all_white), NULL);

    gtk_widget_show_all(singleton_instance->window);
    (void)user_data;
}

static void all_white()
{
    g_print("All white\n");
}

void TMainWindow_New_Free(TMainWindow *this)
{
    free(this);
}
