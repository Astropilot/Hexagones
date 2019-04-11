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
#include "model/grid.h"
#include "ui/window.h"
#include "ui/palette.h"
#include "ui/map.h"
#include "controller.h"

static TMainWindow *singleton_instance = NULL;

static void activate(GtkApplication* app, gpointer user_data);
static gboolean callback_menuitem(GtkMenuItem *item, gpointer user_data);

static char *map_actions[] = {
    "All white",
    "All black",
    "Clear results",
    "Random",
    NULL
};

static char *algo_actions[] = {
    "Depth-first Search",
    "Breadth-first Search",
    "Connected components",
    "Bellman-Ford",
    "Dijkstra",
    "A-star",
    NULL
};

TMainWindow* New_TMainWindow(void)
{
    TMainWindow *this = singleton_instance;

    if (!this)
        this = malloc(sizeof(TMainWindow));
    else
        return (this);

    if(!this) return (NULL);

    this->Start_View = TMainWindow_Start_View;
    this->Free = TMainWindow_New_Free;
    this->palette = New_TPalette();
    this->map = New_TMap();
    this->menu_items = NULL;
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
    GtkWidget *menu;
    GtkWidget *menu_root;
    GtkWidget *menu_item;

    GtkWidget *main_grid;
    int menu_item_idx = 0;

    singleton_instance->window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(singleton_instance->window), "Hexagones");

    app_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(singleton_instance->window), app_box);

    menubar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(app_box), menubar, FALSE, FALSE, 0);

    menu = gtk_menu_new();
    menu_root = gtk_menu_item_new_with_label("Map");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_root), menu);

    char **map_action = map_actions;
    singleton_instance->menu_items = malloc(10 * sizeof(GtkWidget*));
    while (*map_action) {
        menu_item = gtk_menu_item_new_with_label(*map_action);
        gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);
        g_signal_connect(menu_item, "activate", G_CALLBACK(callback_menuitem), NULL);
        singleton_instance->menu_items[menu_item_idx] = menu_item;
        menu_item_idx++;
        map_action++;
    }
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_root);

    menu = gtk_menu_new();
    menu_root = gtk_menu_item_new_with_label("Algorithms");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_root), menu);

    char **algo_action = algo_actions;
    while (*algo_action) {
        menu_item = gtk_menu_item_new_with_label(*algo_action);
        gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);
        g_signal_connect(menu_item, "activate", G_CALLBACK(callback_menuitem), NULL);
        singleton_instance->menu_items[menu_item_idx] = menu_item;
        menu_item_idx++;
        algo_action++;
    }
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_root);

    main_grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(app_box), main_grid, FALSE, FALSE, 0);

    singleton_instance->palette->controller = singleton_instance->controller;
    singleton_instance->palette->Init_Palette(singleton_instance->palette);

    gtk_grid_attach(GTK_GRID(main_grid),
        singleton_instance->palette->widget, 0, 0, 1, 1
    );

    singleton_instance->map->controller = singleton_instance->controller;
    singleton_instance->map->Init_Map(singleton_instance->map);

    gtk_grid_attach(GTK_GRID(main_grid),
        singleton_instance->map->widget, 1, 0, 1, 1
    );

    gtk_widget_show_all(singleton_instance->window);

    TGridModel *model = New_TGridModel(singleton_instance->controller);
    singleton_instance->controller->model = model;
    (void)user_data;
}

static gboolean callback_menuitem(GtkMenuItem *item, gpointer user_data)
{
    int i;

    for (i = 0; i < 10; i++) {
        gtk_widget_set_sensitive(
            singleton_instance->menu_items[i],
            FALSE
        );
    }
    singleton_instance->controller->On_MenuChange(
        singleton_instance->controller,
        gtk_menu_item_get_label(item)
    );
    for (i = 0; i < 10; i++) {
        gtk_widget_set_sensitive(
            singleton_instance->menu_items[i],
            TRUE
        );
    }
    (void)user_data;
    (void)colors;
    return (FALSE);
}

void TMainWindow_New_Free(TMainWindow *this)
{
    if (this) {
        free(this->menu_items);
        this->palette->Free(this->palette);
        this->map->Free(this->map);
    }
    free(this);
    singleton_instance = NULL;
}
