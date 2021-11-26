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

void console_log(const gchar *text)
{
    char tmp[strlen(text)+1];

    sprintf(tmp, "\n%s", text);

    gtk_text_buffer_insert_at_cursor(
                    GTK_TEXT_BUFFER(TEXT_BUFFER_BOTTOM_LEFT),
                    tmp,
                    strlen(tmp));
}

void on_button_1_clicked(GtkButton* b, GtkSpinButton* s)
{
    int spin_value = gtk_spin_button_get_value(s);

    if (find_tree_list(&TREE_LIST, spin_value))
    {
        console_log("ERROR: Tree already exists with that root");
    }
    else
    {
        Tree* new_tree = create_tree(spin_value);

        NodeList* new_node = create_node_list(new_tree);

        add_node_list(&TREE_LIST, &new_node);

        char tmp[100];

        sprintf(tmp, "%i",(int) spin_value);

        console_log("New tree created");

        GtkWidget* new_label = gtk_label_new("label");

        gtk_label_set_text(GTK_LABEL(new_label),tmp);

        GtkWidget* new_row = gtk_list_box_row_new();

        gtk_container_add(GTK_CONTAINER(new_row), new_label);

        // inserts new row at the end of the list
        gtk_list_box_insert(GTK_LIST_BOX(LIST_BOTTOM_RIGHT), new_row, -1);

        // shows the changes in the list
        gtk_widget_show_all(new_row);

    }
}

void on_button_2_clicked(GtkButton* b, GtkSpinButton* s)
{
    GtkListBoxRow* selected_row = gtk_list_box_get_selected_row(GTK_LIST_BOX(LIST_BOTTOM_RIGHT));
    GtkWidget* selected_row_label = gtk_bin_get_child(GTK_BIN(selected_row));
    int selected_row_tree_root = atoi(gtk_label_get_text(GTK_LABEL(selected_row_label)));
    Tree* selected_tree = find_tree_list(&TREE_LIST, selected_row_tree_root);

    NodeList* new_node = create_node_list(add_node_tree(
                &selected_tree, gtk_spin_button_get_value(s)));

    add_node_list(&TREE_LIST, &new_node);

    in_order(&selected_tree->root);

}

void on_list_selected_rows_changed(GtkListBox* l, GtkListBoxRow* r)
{
    console_log("HELO");

    char tmp[10];

    GtkListBoxRow* row = gtk_list_box_get_selected_row(GTK_LIST_BOX(LIST_BOTTOM_RIGHT));
    GtkWidget* label = gtk_bin_get_child(GTK_BIN(row));
    if(row) console_log("yes");

    console_log(gtk_label_get_text(GTK_LABEL(label)));
}
