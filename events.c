/* events.c

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

#include "events.h"

void on_button_1_clicked(GtkButton *b)
{
    char tmp[100];

    sprintf(tmp, "\n%s", gtk_button_get_label(b));

    gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(
                        TEXT_BUFFER_BOTTOM_LEFT),
                        tmp,
                        strlen(tmp));

    GtkWidget* newLabel = gtk_label_new(tmp);

    gtk_label_set_text(GTK_LABEL(newLabel),"test row");

    // inserts new row at the end of the list
    gtk_list_box_insert(GTK_LIST_BOX(LIST_BOTTOM_RIGHT), newLabel, -1);

    // shows the changes in the list
    gtk_widget_show_all(LIST_BOTTOM_RIGHT);
}
