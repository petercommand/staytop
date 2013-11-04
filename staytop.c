#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include "menu.h"
#include "send_message.h"
#include "staytop.h"
GtkWidget *window;
int main (int argc,
	  char *argv[])
{
  GtkWidget *vbox, *button_set, *button_unset;
  extern GtkWidget *menubar;

  gtk_init (&argc, &argv);
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  button_set = gtk_button_new_with_label ("set");
  button_unset = gtk_button_new_with_label ("unset");
  gtk_drag_source_set(GTK_WIDGET(button_set), GDK_BUTTON1_MASK, NULL, 0, GDK_ACTION_COPY);
  gtk_drag_source_set(GTK_WIDGET(button_unset), GDK_BUTTON1_MASK, NULL, 0, GDK_ACTION_COPY);
  gtk_window_set_default_size(GTK_WINDOW(window), 100, 100);
  vbox = gtk_vbox_new (FALSE, 0);
  create_menu();
  gtk_box_pack_start (GTK_BOX (vbox), menubar, FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), button_set, FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), button_unset, FALSE, FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show_all (window);
  g_signal_connect (G_OBJECT (window), "destroy",
		    G_CALLBACK (destroy), NULL);
  g_signal_connect (G_OBJECT (button_set), "drag_begin",
		    G_CALLBACK (drag_begin), NULL);
  g_signal_connect (G_OBJECT (button_set), "drag_end",
		    G_CALLBACK(drag_end), NULL);
  g_signal_connect (G_OBJECT (button_unset), "drag_begin",
		    G_CALLBACK (drag_begin), NULL);
  g_signal_connect (G_OBJECT (button_unset), "drag_end",
		    G_CALLBACK(drag_end), NULL);
  gtk_main();
  return 0;
}
static void destroy (GtkWidget *window, gpointer data)
{
  gtk_main_quit ();
}
static void drag_begin (GtkWidget *widget, GdkDragContext *dc, gpointer data)
{
  g_print ("hello\n");
}
static void drag_end (GtkWidget *widget, GdkDragContext *dc, gint x, gint y, guint t, gpointer data)
{
  const char *label = gtk_button_get_label(GTK_BUTTON(widget));
  char set[] = "set";
  g_print("%s dropped\n",label);
  label==set?set_state():unset_state();


}
