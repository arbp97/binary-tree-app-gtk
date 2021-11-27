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
#include "list.h"
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>

// write to console in app
void console_log(const gchar *text);

/* Create new tree */
void on_button_1_clicked(GtkButton* b, GtkSpinButton* s);

/* Inserts new node in selected tree*/
void on_button_2_clicked(GtkButton* b, GtkSpinButton* s);

/* Logs when the selected tree changes */
void on_list_selected_rows_changed(GtkListBox* l, GtkListBoxRow* r);

#endif // !_EVENTS_H_