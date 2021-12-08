/* globals.h

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "includes.h"
#include "list.h"
#pragma once

// Widgets used all around the program

extern GtkWidget *MAIN_WINDOW;
extern GtkWidget *TREE_WINDOW;
extern GtkWidget *ABOUT_WINDOW;
extern GtkWidget *MAIN_CONTAINER;
extern GtkWidget *CONTAINER_TOP_LEFT;
extern GtkWidget *CONTAINER_TOP_RIGHT;
extern GtkWidget *CONTAINER_BOTTOM_LEFT;
extern GtkWidget *CONTAINER_BOTTOM_RIGHT;
extern GtkWidget *SCROLL_WINDOW_TOP_LEFT;
extern GtkWidget *SCROLL_WINDOW_TOP_RIGHT;
extern GtkWidget *VIEWPORT_TOP_LEFT;
extern GtkWidget *VIEWPORT_TOP_RIGHT;
extern GtkWidget *FIXED_TOP_RIGHT;
extern GtkWidget *FIXED_TREE_VIEW;
extern GtkWidget *GRID_TOP_LEFT;
extern GtkWidget *BUTTON_1;
extern GtkWidget *BUTTON_2;
extern GtkWidget *BUTTON_3;
extern GtkWidget *BUTTON_4;
extern GtkWidget *BUTTON_5;
extern GtkWidget *BUTTON_6;
extern GtkWidget *BUTTON_7;
extern GtkWidget *BUTTON_TREE_VIEW;
extern GtkWidget *SPIN_BUTTON_1;
extern GtkWidget *SPIN_BUTTON_2;
extern GtkWidget *SCROLL_WINDOW_BOTTON_LEFT;
extern GtkWidget *SCROLL_WINDOW_BOTTON_RIGHT;
extern GtkWidget *VIEWPORT_BOTTOM_RIGHT;
extern GtkWidget *LIST_BOTTOM_RIGHT;
extern GtkWidget *TEXT_VIEW_BOTTOM_LEFT;
extern GtkWidget *TEXT_BUFFER_BOTTOM_LEFT;
extern GtkWidget *TEXT_BUFFER_BUTTON_3;
extern GtkWidget *TEXT_BUFFER_BUTTON_4;
extern GtkWidget *TEXT_BUFFER_BUTTON_5;
extern GtkBuilder *BUILDER;

extern struct List *TREE_LIST;

typedef enum Arrangement
{
    PRE_ORDER = 0,
    IN_ORDER = 1,
    POST_ORDER = 2
} Arrangement;

/*
    mid x position of the container to show trees
    inside the app.
*/
static const int INTERNAL_VIEWPORT_POS_X = 225;

// variable x position of the root widget of a tree.
// it changes when the viewport changes
extern int ROOT_WIDGET_POS_X;
// variable y position of the root widget of a tree.
extern int ROOT_WIDGET_POS_Y;

// balance tolerance of an AVL tree
static const int AVL_THRESHOLD = 1;

#endif // !_GLOBALS_H_