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
    printf("%s", gtk_button_get_label(b));

    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(
                        TEXT_BUFFER_BOTTOM_LEFT),
                        gtk_button_get_label(b),
                        strlen(gtk_button_get_label(b)));
}
