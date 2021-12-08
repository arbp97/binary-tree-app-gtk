/* main.c

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

GtkWidget *MAIN_WINDOW;
GtkWidget *TREE_WINDOW;
GtkWidget *ABOUT_WINDOW;
GtkWidget *MAIN_CONTAINER;
GtkWidget *CONTAINER_TOP_LEFT;
GtkWidget *CONTAINER_TOP_RIGHT;
GtkWidget *CONTAINER_BOTTOM_LEFT;
GtkWidget *CONTAINER_BOTTOM_RIGHT;
GtkWidget *SCROLL_WINDOW_TOP_LEFT;
GtkWidget *SCROLL_WINDOW_TOP_RIGHT;
GtkWidget *VIEWPORT_TOP_LEFT;
GtkWidget *VIEWPORT_TOP_RIGHT;
GtkWidget *FIXED_TOP_RIGHT;
GtkWidget *FIXED_TREE_VIEW;
GtkWidget *GRID_TOP_LEFT;
GtkWidget *BUTTON_1;
GtkWidget *BUTTON_2;
GtkWidget *BUTTON_3;
GtkWidget *BUTTON_4;
GtkWidget *BUTTON_5;
GtkWidget *BUTTON_6;
GtkWidget *BUTTON_7;
GtkWidget *BUTTON_TREE_VIEW;
GtkWidget *SPIN_BUTTON_1;
GtkWidget *SPIN_BUTTON_2;
GtkWidget *SCROLL_WINDOW_BOTTON_LEFT;
GtkWidget *SCROLL_WINDOW_BOTTON_RIGHT;
GtkWidget *VIEWPORT_BOTTOM_RIGHT;
GtkWidget *LIST_BOTTOM_RIGHT;
GtkWidget *TEXT_VIEW_BOTTOM_LEFT;
GtkWidget *TEXT_BUFFER_BOTTOM_LEFT;
GtkWidget *TEXT_BUFFER_BUTTON_3;
GtkWidget *TEXT_BUFFER_BUTTON_4;
GtkWidget *TEXT_BUFFER_BUTTON_5;
GtkBuilder *BUILDER;

List *TREE_LIST;

int ROOT_WIDGET_POS_X = INTERNAL_VIEWPORT_POS_X;
int ROOT_WIDGET_POS_Y = 0;

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv); // init Gtk

	//---------------------------------------------------------------------
	// establish contact with xml code used to adjust widget settings
	//---------------------------------------------------------------------

	BUILDER = gtk_builder_new_from_resource("/resources/res/app-layout.glade");

	MAIN_WINDOW = GTK_WIDGET(gtk_builder_get_object(BUILDER, "main-window"));
	TREE_WINDOW = GTK_WIDGET(gtk_builder_get_object(BUILDER, "tree-window"));
	ABOUT_WINDOW = GTK_WIDGET(gtk_builder_get_object(BUILDER, "about-window"));

	g_signal_connect(MAIN_WINDOW, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(TREE_WINDOW, "delete-event", G_CALLBACK(on_widget_deleted), NULL);
	g_signal_connect(ABOUT_WINDOW, "delete-event", G_CALLBACK(on_widget_deleted), NULL);

	gtk_builder_connect_signals(BUILDER, NULL);

	/* Getting widgets directly from the layout file w/ the builder */

	MAIN_CONTAINER =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "main-container"));
	CONTAINER_TOP_LEFT =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "container-top-left"));
	CONTAINER_TOP_RIGHT =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "container-top-right"));
	CONTAINER_BOTTOM_LEFT =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "container-bottom-left"));
	CONTAINER_BOTTOM_RIGHT =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "container-bottom-right"));

	SCROLL_WINDOW_TOP_LEFT =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "scrolled-top-left"));
	SCROLL_WINDOW_TOP_RIGHT =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "scrolled-top-right"));
	VIEWPORT_TOP_LEFT =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "view-top-left"));
	VIEWPORT_TOP_RIGHT =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "view-top-right"));
	FIXED_TOP_RIGHT =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "fixed-top-right"));
	FIXED_TREE_VIEW =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "fixed-tree-view"));
	GRID_TOP_LEFT =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "grid-top-left"));

	BUTTON_1 = GTK_WIDGET(gtk_builder_get_object(BUILDER, "button-1"));
	BUTTON_2 = GTK_WIDGET(gtk_builder_get_object(BUILDER, "button-2"));
	BUTTON_3 = GTK_WIDGET(gtk_builder_get_object(BUILDER, "button-3"));
	BUTTON_4 = GTK_WIDGET(gtk_builder_get_object(BUILDER, "button-4"));
	BUTTON_5 = GTK_WIDGET(gtk_builder_get_object(BUILDER, "button-5"));
	BUTTON_6 = GTK_WIDGET(gtk_builder_get_object(BUILDER, "button-6"));
	BUTTON_7 = GTK_WIDGET(gtk_builder_get_object(BUILDER, "button-7"));

	BUTTON_TREE_VIEW = GTK_WIDGET(gtk_builder_get_object(BUILDER, "button-tree-view"));

	SPIN_BUTTON_1 = GTK_WIDGET(gtk_builder_get_object(BUILDER, "spin-button-1"));
	SPIN_BUTTON_2 = GTK_WIDGET(gtk_builder_get_object(BUILDER, "spin-button-2"));

	SCROLL_WINDOW_BOTTON_LEFT =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "scrolled-bottom-left"));
	SCROLL_WINDOW_BOTTON_RIGHT =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "scrolled-bottom-right"));
	VIEWPORT_BOTTOM_RIGHT =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "view-bottom-right"));
	LIST_BOTTOM_RIGHT =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "list-bottom-right"));
	TEXT_VIEW_BOTTOM_LEFT =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "text-bottom-left"));
	TEXT_BUFFER_BOTTOM_LEFT =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "console-text-buffer"));
	TEXT_BUFFER_BUTTON_3 =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "button-3-buffer"));
	TEXT_BUFFER_BUTTON_4 =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "button-4-buffer"));
	TEXT_BUFFER_BUTTON_5 =
		GTK_WIDGET(gtk_builder_get_object(BUILDER, "button-5-buffer"));

	// creating b tree list
	TREE_LIST = create_list();

	gtk_widget_show(MAIN_WINDOW);

	// main loop
	gtk_main();

	delete_list(TREE_LIST);

	return EXIT_SUCCESS;
}
