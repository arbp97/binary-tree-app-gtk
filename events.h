/* events.h

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

#ifndef _EVENTS_H_
#define _EVENTS_H_
#pragma once

#include "globals.h"
#include "tree.h"
#include "util.h"

/* Create new tree */
void on_button_1_clicked(GtkButton *b, GtkSpinButton *s);

/* Inserts new node in selected tree*/
void on_button_2_clicked(GtkButton *b, GtkSpinButton *s);

/* Prints the selected tree in pre order */
void on_button_3_clicked(GtkButton *b);

/* Prints the selected tree in order */
void on_button_4_clicked(GtkButton *b);

/* Prints the selected tree in post order */
void on_button_5_clicked(GtkButton *b);

/* shows the selected tree in viewport */
void on_button_6_clicked(GtkButton *b);

/* deletes selected tree and clears the viewport */
void on_button_7_clicked(GtkButton *b);

/* Shows the dedicated tree view window*/
void on_button_tree_view_clicked(GtkButton *b);

/* Logs when the selected tree changes */
void on_list_selected_rows_changed(GtkListBox *l, GtkListBoxRow *r);

/* Used to hide the tree view window instead of destroying it*/
gboolean on_widget_deleted(GtkWidget *widget, GdkEvent *event, gpointer data);

#endif // !_EVENTS_H_