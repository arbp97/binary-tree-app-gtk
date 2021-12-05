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

void on_button_1_clicked(GtkButton *b, GtkSpinButton *s)
{
    // new tree root value
    int spin_value = gtk_spin_button_get_value(s);

    /*
    we check whether a tree with this root
    exists or not
    */
    if (find_tree_list(TREE_LIST, spin_value))
    {
        console_log("ERROR: Tree already exists with that root", TEXT_BUFFER_BOTTOM_LEFT, true);
    }
    else
    {
        /*
        creating a new tree instance with the specified root value,
        adding it to a new node, and adding this node to the
        tree list
        */
        Tree *new_tree = create_tree(spin_value);

        NodeList *new_node = create_node_list(new_tree);

        add_node_list(TREE_LIST, new_node);

        /***************************************************/

        /*
        creating a new label and row to contain it
        */
        char tmp[100];

        sprintf(tmp, "%i", (int)spin_value);

        console_log("New tree created", TEXT_BUFFER_BOTTOM_LEFT, true);

        GtkWidget *new_label = gtk_label_new("label");

        gtk_label_set_text(GTK_LABEL(new_label), tmp);

        GtkWidget *new_row = gtk_list_box_row_new();

        /****************************************************/

        /*
        adding the new row to the list and showing it
        */
        gtk_container_add(GTK_CONTAINER(new_row), new_label);

        // inserts new row at the end of the list
        gtk_list_box_insert(GTK_LIST_BOX(LIST_BOTTOM_RIGHT), new_row, -1);

        // shows the changes in the list
        gtk_widget_show_all(new_row);
    }
}

void on_button_2_clicked(GtkButton *b, GtkSpinButton *s)
{
    int spin_value = gtk_spin_button_get_value(s);
    // get selected tree
    GtkListBoxRow *selected_row =
        gtk_list_box_get_selected_row(GTK_LIST_BOX(LIST_BOTTOM_RIGHT));

    /* checking if the row is actually selected,
        or if it even exists */
    if (!selected_row)
    {
        console_log("ERROR: no tree selected", TEXT_BUFFER_BOTTOM_LEFT, true);
    }
    else
    {
        // get child out of the selected row, a label
        GtkWidget *selected_row_label =
            gtk_bin_get_child(GTK_BIN(selected_row));

        // get the tree root out of the label
        int selected_row_tree_root =
            atoi(gtk_label_get_text(GTK_LABEL(selected_row_label)));

        // finally, find the tree with that root
        Tree *selected_tree = find_tree_list(TREE_LIST, selected_row_tree_root);

        /* Adding the new node to the selected tree */
        if (add_node_tree(selected_tree, spin_value))
        {
            if (selected_tree->root->data != selected_row_tree_root)
            {
                /*
                if the root changed (because of balancing), then
                it's label in the list needs to be changed also.
                */
                char tmp[10];
                sprintf(tmp, "%i", selected_tree->root->data);
                gtk_label_set_text(GTK_LABEL(selected_row_label), tmp);
            }

            console_log("Added node successfully", TEXT_BUFFER_BOTTOM_LEFT, true);
        }
        else
            console_log("ERROR: node was not created: node already exists", TEXT_BUFFER_BOTTOM_LEFT, true);
    }
}

void on_button_3_clicked(GtkButton *b)
{
    GtkListBoxRow *selected_row =
        gtk_list_box_get_selected_row(GTK_LIST_BOX(LIST_BOTTOM_RIGHT));

    /* checking if the row is actually selected,
        or if it even exists */
    if (!selected_row)
        console_log("ERROR: no tree selected", TEXT_BUFFER_BOTTOM_LEFT, true);
    else
        show_tree_arrangement_on_buffer(selected_row, PRE_ORDER, TEXT_BUFFER_BUTTON_3);
}

void on_button_4_clicked(GtkButton *b)
{
    GtkListBoxRow *selected_row =
        gtk_list_box_get_selected_row(GTK_LIST_BOX(LIST_BOTTOM_RIGHT));

    /* checking if the row is actually selected,
        or if it even exists */
    if (!selected_row)
        console_log("ERROR: no tree selected", TEXT_BUFFER_BOTTOM_LEFT, true);
    else
        show_tree_arrangement_on_buffer(selected_row, IN_ORDER, TEXT_BUFFER_BUTTON_4);
}

void on_button_5_clicked(GtkButton *b)
{
    GtkListBoxRow *selected_row =
        gtk_list_box_get_selected_row(GTK_LIST_BOX(LIST_BOTTOM_RIGHT));

    /* checking if the row is actually selected,
        or if it even exists */
    if (!selected_row)
        console_log("ERROR: no tree selected", TEXT_BUFFER_BOTTOM_LEFT, true);
    else
        show_tree_arrangement_on_buffer(selected_row, POST_ORDER, TEXT_BUFFER_BUTTON_5);
}

void on_button_6_clicked(GtkButton *b)
{
    /*
        Using the coordinates stored in every treenode, shows the tree
        in the viewport.
    */

    GtkListBoxRow *selected_row =
        gtk_list_box_get_selected_row(GTK_LIST_BOX(LIST_BOTTOM_RIGHT));

    /* checking if the row is actually selected,
        or if it even exists */
    if (!selected_row)
        console_log("ERROR: no tree selected", TEXT_BUFFER_BOTTOM_LEFT, true);
    else
    {
        clear_viewport(FIXED_TREE_VIEW);
        clear_viewport(FIXED_TOP_RIGHT);

        GtkWidget *label = gtk_bin_get_child(GTK_BIN(selected_row));
        char tmp[32];
        int selected_tree_root = atoi(gtk_label_get_text(GTK_LABEL(label)));

        sprintf(tmp, "%i", selected_tree_root);

        Tree *selected_tree = find_tree_list(TREE_LIST, selected_tree_root);

        selected_tree->root->x_pos = ROOT_WIDGET_POS_X;

        render_tree(selected_tree->root, FIXED_TOP_RIGHT);

        gtk_widget_show_all(FIXED_TOP_RIGHT);
    }
}

void on_button_7_clicked(GtkButton *b)
{
    GtkListBoxRow *selected_row =
        gtk_list_box_get_selected_row(GTK_LIST_BOX(LIST_BOTTOM_RIGHT));

    if (!selected_row)
        console_log("ERROR: no tree selected", TEXT_BUFFER_BOTTOM_LEFT, true);
    else
    {
        GtkWidget *label = gtk_bin_get_child(GTK_BIN(selected_row));
        char tmp[32];
        int selected_tree_root = atoi(gtk_label_get_text(GTK_LABEL(label)));

        sprintf(tmp, "%i", selected_tree_root);

        /* finding and deleting the tree and its node in the list*/

        Tree *selected_tree = find_tree_list(TREE_LIST, selected_tree_root);
        NodeList *cursor = TREE_LIST->head;
        bool found = false;

        while (cursor && !found)
            if (((Tree *)cursor->data_ptr) == selected_tree)
                found = true;

        delete_node_list(TREE_LIST, cursor);

        delete_tree(selected_tree);

        /*deleting the row in the bottom right list*/
        gtk_list_box_unselect_all(GTK_LIST_BOX(LIST_BOTTOM_RIGHT));

        gtk_container_remove(GTK_CONTAINER(LIST_BOTTOM_RIGHT), GTK_WIDGET(selected_row));

        gtk_widget_show_all(LIST_BOTTOM_RIGHT);

        clear_viewport(FIXED_TOP_RIGHT);
    }
}

void on_button_tree_view_clicked(GtkButton *b)
{
    GtkListBoxRow *selected_row =
        gtk_list_box_get_selected_row(GTK_LIST_BOX(LIST_BOTTOM_RIGHT));

    if (!selected_row)
        console_log("ERROR: no tree selected", TEXT_BUFFER_BOTTOM_LEFT, true);
    else
    {
        clear_viewport(FIXED_TREE_VIEW);
        clear_viewport(FIXED_TOP_RIGHT);

        GtkWidget *label = gtk_bin_get_child(GTK_BIN(selected_row));
        char tmp[32];
        int selected_tree_root = atoi(gtk_label_get_text(GTK_LABEL(label)));

        sprintf(tmp, "%i", selected_tree_root);

        Tree *selected_tree = find_tree_list(TREE_LIST, selected_tree_root);

        ROOT_WIDGET_POS_X = get_screen_width() / 2;

        selected_tree->root->x_pos = ROOT_WIDGET_POS_X;

        render_tree(selected_tree->root, FIXED_TREE_VIEW);

        gtk_widget_show_all(TREE_WINDOW);
        gtk_window_set_resizable(GTK_WINDOW(TREE_WINDOW), true);
        gtk_window_maximize(GTK_WINDOW(TREE_WINDOW));
        gtk_window_set_resizable(GTK_WINDOW(TREE_WINDOW), false);
    }
}

void on_list_selected_rows_changed(GtkListBox *l, GtkListBoxRow *r)
{

    /*
        Shows the current selected tree and cleans the viewport when
        a new tree is selected from the list.
    */
    char tmp[32];
    GtkListBoxRow *row =
        gtk_list_box_get_selected_row(GTK_LIST_BOX(LIST_BOTTOM_RIGHT));

    if (row)
    {
        /*
        this if statement exists because when you delete
        a tree, it updates the list and sends a signal to
        this handler. In that case the row would not exist.
        */
        GtkWidget *label = gtk_bin_get_child(GTK_BIN(row));
        int selected_tree_root = atoi(gtk_label_get_text(GTK_LABEL(label)));

        sprintf(tmp, "Tree selected: %i", selected_tree_root);

        Tree *selected_tree = find_tree_list(TREE_LIST, selected_tree_root);

        console_log(tmp, TEXT_BUFFER_BOTTOM_LEFT, true);
    }

    clear_viewport(FIXED_TOP_RIGHT);
    clear_viewport(FIXED_TREE_VIEW);
}

gboolean on_widget_deleted(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    gtk_widget_hide(widget);
    ROOT_WIDGET_POS_X = INTERNAL_VIEWPORT_POS_X;
    return TRUE;
}
