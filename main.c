#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>

// Widgets

GtkWidget *main_window;
GtkWidget *main_container;
GtkWidget *container_top_left;
GtkWidget *container_top_right;
GtkWidget *container_bottom_left;
GtkWidget *container_bottom_right;
GtkWidget *scroll_window_top_left;
GtkWidget *viewport_top_left;
GtkWidget *grid_top_left;
GtkWidget *button_1;
GtkWidget *button_2;
GtkWidget *button_3;
GtkWidget *button_4;
GtkWidget *button_5;
GtkWidget *spin_button_1;
GtkWidget *spin_button_2;
GtkWidget *scroll_window_bottom_left;
GtkWidget *scroll_window_bottom_right;
GtkWidget *viewport_bottom_right;
GtkWidget *list_bottom_right;
GtkWidget *text_view_bottom_left;
GtkBuilder *builder;

int main(int argc, char *argv[])
{

	gtk_init(&argc, &argv); // init Gtk

	//---------------------------------------------------------------------
	// establish contact with xml code used to adjust widget settings
	//---------------------------------------------------------------------

	builder = gtk_builder_new_from_file("app-layout.glade");

	main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main-window"));

	g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_builder_connect_signals(builder, NULL);

	/* Getting widgets directly from the layout file w/ the builder */

	main_container =
			GTK_WIDGET(gtk_builder_get_object(builder, "main-container"));
	container_top_left =
			GTK_WIDGET(gtk_builder_get_object(builder, "container-top-left"));
	container_top_right =
			GTK_WIDGET(gtk_builder_get_object(builder, "container-top-right"));
	container_bottom_left =
			GTK_WIDGET(gtk_builder_get_object(builder, "container-bottom-left"));
	container_bottom_right =
			GTK_WIDGET(gtk_builder_get_object(builder, "container-bottom-right"));

	scroll_window_top_left =
			GTK_WIDGET(gtk_builder_get_object(builder, "scrolled-top-left"));
	viewport_top_left =
			GTK_WIDGET(gtk_builder_get_object(builder, "view-top-left"));
	grid_top_left =
			GTK_WIDGET(gtk_builder_get_object(builder, "grid-top-left"));

	button_1 = GTK_WIDGET(gtk_builder_get_object(builder, "button-1"));
	button_2 = GTK_WIDGET(gtk_builder_get_object(builder, "button-2"));
	button_3 = GTK_WIDGET(gtk_builder_get_object(builder, "button-3"));
	button_4 = GTK_WIDGET(gtk_builder_get_object(builder, "button-4"));
	button_5 = GTK_WIDGET(gtk_builder_get_object(builder, "button-5"));

	spin_button_1 = GTK_WIDGET(gtk_builder_get_object(builder, "spin-button-1"));
	spin_button_2 = GTK_WIDGET(gtk_builder_get_object(builder, "spin-button-2"));

	scroll_window_bottom_left =
			GTK_WIDGET(gtk_builder_get_object(builder, "scrolled-bottom-left"));
	scroll_window_bottom_right =
			GTK_WIDGET(gtk_builder_get_object(builder, "scrolled-bottom-right"));
	viewport_bottom_right =
			GTK_WIDGET(gtk_builder_get_object(builder, "view-bottom-right"));
	list_bottom_right =
			GTK_WIDGET(gtk_builder_get_object(builder, "list-bottom-right"));
	text_view_bottom_left =
			GTK_WIDGET(gtk_builder_get_object(builder, "text-bottom-left"));

	gtk_widget_show(main_window);

	// main loop
	gtk_main();

	return EXIT_SUCCESS;
}
