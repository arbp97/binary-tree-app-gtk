/* util.c

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

#include "util.h"

void console_log(const gchar *text, GtkWidget *buffer, bool newline)
{
    char tmp[strlen(text) + 1];
    GtkTextIter end;

    gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(buffer), &end);

    if (newline)
        sprintf(tmp, "\n%s", text);
    else
        sprintf(tmp, "%s", text);

    gtk_text_buffer_insert(
        GTK_TEXT_BUFFER(buffer),
        &end, tmp, strlen(tmp));
}

void clear_viewport(GtkWidget *viewport)
{
    GList *children, *iter;

    children = gtk_container_get_children(GTK_CONTAINER(viewport));

    for (iter = children; iter != NULL; iter = g_list_next(iter))
        gtk_container_remove(GTK_CONTAINER(viewport), g_object_ref(iter->data));

    g_list_free(children);

    gtk_widget_show_all(viewport);
}

void show_tree_arrangement_on_buffer(GtkListBoxRow *selected_row, Arrangement arrangement, GtkWidget *buffer)
{
    /*
        Shows the current nodes of the tree in the text area used for that arrangement.
        NOTICE: the buffer argument actually doesn't assure that
        the data will be written in it. The *_order functions in
        tree have fixed buffers to write to... #FIXME
    */

    // get child out of the selected row, a label
    GtkWidget *selected_row_label =
        gtk_bin_get_child(GTK_BIN(selected_row));

    // get the tree root out of the label
    int selected_row_tree_root =
        atoi(gtk_label_get_text(GTK_LABEL(selected_row_label)));

    // finally, find the tree with that root
    Tree *selected_tree = find_tree_list(TREE_LIST, selected_row_tree_root);

    // iterators to clear the text buffer
    GtkTextIter start, end;

    // get start and end points of said buffer
    gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(buffer), &start);
    gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(buffer), &end);

    // clears buffer
    gtk_text_buffer_delete(GTK_TEXT_BUFFER(buffer), &start, &end);

    // prints the tree in specified arrangement
    switch (arrangement)
    {
    case PRE_ORDER:
        pre_order(selected_tree->root);
        break;
    case IN_ORDER:
        in_order(selected_tree->root);
        break;
    case POST_ORDER:
        post_order(selected_tree->root);
        break;
    default:
        break;
    }
}

gint get_screen_width()
{
    GdkRectangle workarea = {0};
    gdk_monitor_get_workarea(
        gdk_display_get_primary_monitor(gdk_display_get_default()),
        &workarea);

    return workarea.width;
}

gint get_screen_height()
{
    GdkRectangle workarea = {0};
    gdk_monitor_get_workarea(
        gdk_display_get_primary_monitor(gdk_display_get_default()),
        &workarea);

    return workarea.height;
}

void render_tree(NodeTree *root, GtkWidget *viewport)
{
	adjust_tree_position(&root);

	gtk_fixed_put(GTK_FIXED(viewport),
				  root->widget, root->x_pos, root->y_pos);

	if (root->left)
		render_tree(root->left, viewport);

	if (root->right)
		render_tree(root->right, viewport);
}

void adjust_tree_position(NodeTree **root)
{
	if ((*root)->x_pos == ROOT_WIDGET_POS_X &&
		(*root)->y_pos == ROOT_WIDGET_POS_Y)
	{
		/*
		special one time setting adding more space
		between the original node's sub trees, to
		partially overcome overlapping widgets.
		*/
		if ((*root)->left)
		{
			(*root)->left->x_pos = (*root)->x_pos - 150;
			(*root)->left->y_pos = (*root)->y_pos + 50;

			adjust_tree_position(&(*root)->left);
		}
		if ((*root)->right)
		{
			(*root)->right->x_pos = (*root)->x_pos + 150;
			(*root)->right->y_pos = (*root)->y_pos + 50;

			adjust_tree_position(&(*root)->right);
		}
	}
	else
	{
		if ((*root)->left)
		{
			(*root)->left->x_pos = (*root)->x_pos - 50;
			(*root)->left->y_pos = (*root)->y_pos + 50;

			adjust_tree_position(&(*root)->left);
		}

		if ((*root)->right)
		{
			(*root)->right->x_pos = (*root)->x_pos + 50;
			(*root)->right->y_pos = (*root)->y_pos + 50;

			adjust_tree_position(&(*root)->right);
		}
	}
}
