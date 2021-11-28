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
    // new tree root value
    int spin_value = gtk_spin_button_get_value(s);

    /*
    we check whether a tree with this root
    exists or not
    */
    printf("llega 1");
    if (find_tree_list(&TREE_LIST, spin_value))
    {
        console_log("ERROR: Tree already exists with that root");
    }
    else
    {
        /*
        creating a new tree instance with the specified root value,
        adding it to a new node, and adding this node to the
        tree list
        */printf("llega 2");
        //getchar();
        Tree* new_tree = create_tree(spin_value);
        printf("llega 3");
        NodeList* new_node = create_node_list(new_tree);
        printf("llega 4");
        add_node_list(&TREE_LIST, &new_node);
        printf("llega 5");
        /***************************************************/

        /*
        creating a new label and row to contain it
        */
        char tmp[100];

        sprintf(tmp, "%i",(int) spin_value);

        console_log("New tree created");

        GtkWidget* new_label = gtk_label_new("label");

        gtk_label_set_text(GTK_LABEL(new_label),tmp);

        GtkWidget* new_row = gtk_list_box_row_new();

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

void on_button_2_clicked(GtkButton* b, GtkSpinButton* s)
{
    // get selected tree
    GtkListBoxRow* selected_row =
                    gtk_list_box_get_selected_row(GTK_LIST_BOX(LIST_BOTTOM_RIGHT));

    /* checking if the row is actually selected,
        or if it even exists */
    if(!selected_row)
    {
        console_log("ERROR: no tree selected");
    }
    else
    {
        // get child out of the selected row, a label
        GtkWidget* selected_row_label =
                    gtk_bin_get_child(GTK_BIN(selected_row));

        // get the tree root out of the label
        int selected_row_tree_root =
                    atoi(gtk_label_get_text(GTK_LABEL(selected_row_label)));

        // finally, find the tree with that root
        Tree* selected_tree = find_tree_list(&TREE_LIST, selected_row_tree_root);

        /* tries to a new node IN THE TREE, if the value is < than
            the root of the tree, then it does not add it */
        NodeTree* new_node_tree = add_node_tree(&selected_tree, gtk_spin_button_get_value(s));
        NodeList* new_node = NULL;

        /* if the node was in fact created, then it is put
            into a new list node and added to the b tree list */
        if (new_node_tree)
        {
            new_node = create_node_list(new_node_tree);
            //PROBABLE BUG HERE ADDING SECOND TREE TO LIST, IT CRASHES
            //LATER
            add_node_list(&TREE_LIST, &new_node);

            NodeList* cursor = create_node_list(NULL);
            Tree* aux = NULL;
            cursor = TREE_LIST->head;

            while (cursor != NULL)
            {
                aux = (Tree*) cursor->data_ptr;
                //printf("%i", ((NodeTree*)aux->root)->data);

                cursor = cursor->next;
            }
            free(cursor);
        }
        else console_log("ERROR: node was not created: node already exists");

        in_order(&selected_tree->root);
    }

}

void on_list_selected_rows_changed(GtkListBox* l, GtkListBoxRow* r)
{
    char tmp[32];

    GtkListBoxRow* row = gtk_list_box_get_selected_row(GTK_LIST_BOX(LIST_BOTTOM_RIGHT));
    GtkWidget* label = gtk_bin_get_child(GTK_BIN(row));

    sprintf(tmp, "Tree selected: %s", gtk_label_get_text(GTK_LABEL(label)));

    console_log(tmp);
    
    GtkWidget* new_button = gtk_button_new_with_label(gtk_label_get_text(GTK_LABEL(label)));
    gint wx=180, wy=0;

    gtk_fixed_put(GTK_FIXED(FIXED_TOP_RIGHT), new_button,wx,wy);

    GValue root_pos_x = G_VALUE_INIT;
    GValue root_pos_y = G_VALUE_INIT;

    g_value_init (&root_pos_x, G_TYPE_INT);
    g_value_init (&root_pos_y, G_TYPE_INT);
    g_value_set_int (&root_pos_x, wx);
    g_value_set_int (&root_pos_y, wy);

    gtk_container_child_set_property(GTK_CONTAINER(FIXED_TOP_RIGHT),new_button,"root_pos_x",&root_pos_x);
    gtk_container_child_set_property(GTK_CONTAINER(FIXED_TOP_RIGHT),new_button,"root_pos_y",&root_pos_y);

    wx = g_value_get_int(&root_pos_x);
    wy = g_value_get_int(&root_pos_y);
    g_value_unset(&root_pos_x);
    g_value_unset(&root_pos_y);

    GtkWidget* new_button2 = gtk_button_new_with_label("5");

    gtk_fixed_put(GTK_FIXED(FIXED_TOP_RIGHT), new_button2,wx-50,wy+50);
    sprintf(tmp, "x: %i y: %i",(int)wx,(int)wy);
    console_log(tmp);

    gtk_widget_show_all(FIXED_TOP_RIGHT);
}
