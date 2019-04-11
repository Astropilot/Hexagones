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
#include <string.h>

#include "main.h"
#include "controller.h"
#include "utils.h"
#include "model/grid.h"
#include "model/hex.h"
#include "ui/window.h"
#include "ui/map.h"
#include "ui/color.h"

#include "pathfinding/breadth_search.h"
#include "pathfinding/depth_search.h"
#include "pathfinding/connected_components.h"
#include "pathfinding/dijkstra.h"
#include "pathfinding/astar.h"

static TController *singleton_instance = NULL;

TController* New_TController(void)
{
    TController *this = singleton_instance;

    if (!this)
        this = malloc(sizeof(TController));
    else
        return (this);

    if(!this) return (NULL);

    this->On_MenuChange = TController_On_MenuChange;
    this->On_PaletteChange = TController_On_PaletteChange;
    this->On_LeftClick = TController_On_LeftClick;
    this->Update_Hex = TController_Update_Hex;
    this->Free = TController_New_Free;
    this->hex_choice = strdup("Black");
    singleton_instance = this;
    return (this);
}

void TController_On_MenuChange(TController *this, const char *label)
{
    if (!this || !label) return;

    printf("[Controller] Menu item selected: %s\n", label);

    if (strcmp(label, "All white") == 0) {
        this->view->map->Reset_Map(this->view->map, WHITE);
        this->model->Reset_Model(this->model, WHITE);
    }
    if (strcmp(label, "All black") == 0) {
        this->view->map->Reset_Map(this->view->map, BLACK);
        this->model->Reset_Model(this->model, BLACK);
    }
    if (strcmp(label, "Clear results") == 0) {
        this->model->Reset_Results(this->model);
    }
    if (strcmp(label, "Random") == 0) {
        this->model->Random(this->model);
    }
    if (strcmp(label, "Depth-first Search") == 0) {
        depth_search(this->model);
    }
    if (strcmp(label, "Breadth-first Search") == 0) {
        breadth_search(this->model);
    }
    if (strcmp(label, "Connected components") == 0) {
        connected_components(this->model);
    }
    if (strcmp(label, "Dijkstra") == 0) {
        dijkstra(this->model);
    }
    if (strcmp(label, "A-star") == 0) {
        astar(this->model);
    }
    (void)*this;
}

void TController_On_PaletteChange(TController *this, const char *label)
{
    if (!this || !label) return;

    printf("[Controller] Palette item selected: %s\n", label);
    if (this->hex_choice) free(this->hex_choice);
    this->hex_choice = strdup(label);
}

void TController_On_LeftClick(TController *this, int x, int y)
{
    char *choice = this->hex_choice;

    if (strcmp(choice, "Start") == 0) {
        this->model->Change_Start(this->model, x, y);
    } else if (strcmp(choice, "Goal") == 0) {
        this->model->Change_Goal(this->model, x, y);
    } else {
        if (strcmp(choice, "Black") == 0) {
            this->model->hexs[x][y]->Change_Color(this->model->hexs[x][y], BLACK, 1);
        }
        if (strcmp(choice, "White") == 0) {
            this->model->hexs[x][y]->Change_Color(this->model->hexs[x][y], WHITE, 1);
        }
        if (strcmp(choice, "Blue") == 0) {
            this->model->hexs[x][y]->Change_Color(this->model->hexs[x][y], BLUE, 1);
        }
        if (strcmp(choice, "Green") == 0) {
            this->model->hexs[x][y]->Change_Color(this->model->hexs[x][y], GREEN, 1);
        }
        if (strcmp(choice, "Yellow") == 0) {
            this->model->hexs[x][y]->Change_Color(this->model->hexs[x][y], YELLOW, 1);
        }
    }
}

void TController_Update_Hex(TController *this, THex *hex)
{
    (void)colors;
    this->view->map->Update_Hex(this->view->map, hex);
}

void TController_New_Free(TController *this)
{
    if (this) {
        if (this->model)
            this->model->Free(this->model);
        free(this->hex_choice);
    }
    free(this);
    singleton_instance = NULL;
}
