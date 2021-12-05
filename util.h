/* util.h

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

#ifndef _UTIL_H_
#define _UTIL_H_
#pragma once

#include "globals.h"
#include "tree.h"

// write to console in app
void console_log(const gchar *text, GtkWidget *buffer, bool newline);

/* removes all widgets from the the top right container*/
void clear_viewport(GtkWidget *viewport);

/* prints tree in specified buffer and arrangement*/
void show_tree_arrangement_on_buffer(GtkListBoxRow *selected_row, Arrangement arrangement, GtkWidget *buffer);

// Get usable height of the default monitor
gint get_screen_height();

// Get usable width of the default monitor
gint get_screen_width();

// "Draws" tree nodes into the viewport
void render_tree(NodeTree *root, GtkWidget *viewport);

/*
adjusts all nodes X,Y position relative to
the root position
*/
void adjust_tree_position(NodeTree **root);

#endif // !_UTIL_H_