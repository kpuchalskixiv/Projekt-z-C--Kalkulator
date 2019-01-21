#include <gtk/gtk.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

static void
wejscie(GtkButton *button,  GtkWidget *enter, char *nap)
{
    g_print("%s", nap);
   // gtk_entry_set_text(GTK_ENTRY(enter), nap);
}

static void
activate (GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *grid;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 400, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 60);

    grid = gtk_grid_new ();
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *entry=gtk_entry_new();
    char *str="abcd";
    char *wyr="1";
    gint position;

    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 2, 1);
    gtk_entry_set_text(GTK_ENTRY(entry), str);
  //  const char *tekst=gtk_entry_get_text(GTK_ENTRY(entry));
   // position=strlen(tekst);
    position=gtk_entry_get_text_length(GTK_ENTRY(entry));
    gtk_editable_insert_text(GTK_EDITABLE(entry), str, -1, &position);

    button = gtk_button_new_with_label ("Hello World");
  //  g_signal_connect (button, "clicked", (GCallback)wejscie, (entry, wyr));
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_editable_insert_text), (GTK_IS_EDITABLE(entry), str, -1, &position));
  //  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);

    gtk_widget_show_all (window);
}


int main (int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
