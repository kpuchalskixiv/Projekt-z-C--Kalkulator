#include <gtk/gtk.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

static void
print_hello (GtkWidget *widget, gpointer data, char nap)
{
   // int i;
   // for(i=0; i<strlen(nap); i++)
       // g_print ("%c", nap);
//        gtk_entry_set_text(entry, nap);
}

static void
activate (GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *grid;
    GtkWidget *button_box;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 400, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 60);


    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *entry=gtk_entry_new();
    char *str="abcd";
//GtkWidget *entry=gtk_label_new (str);
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 2, 1);
    gtk_entry_set_text(entry, "2");
//    const gchar *napis=gtk_entry_get_text(GtkEntry *entry);
    g_print("%s", str);
    button = gtk_button_new_with_label ("Hello World");
    g_signal_connect_swapped (button, "clicked", (GCallback)gtk_entry_set_text, (entry, "1"));
   // g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
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
