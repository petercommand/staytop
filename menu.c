#include <gtk/gtk.h>
#include "menu.h"
GtkWidget *menubar, *help, *helpmenu;
GtkWidget *about;


void create_menu ()
{
  menubar = gtk_menu_bar_new();
  help = gtk_menu_item_new_with_mnemonic("_Help");
  helpmenu = gtk_menu_new();
  about = gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT, NULL);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), helpmenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu), about);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help);
  /*g_signal_connect(G_OBJECT(about), "activate",
    G_CALLBACK(NULL), NULL);*/
}
