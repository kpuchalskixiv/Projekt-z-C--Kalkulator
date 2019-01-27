#include <gtk/gtk.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
GtkWidget *entry;

void edit_entry(GtkWidget *widget, gchar c[])
{
    gint position;
    char *text=gtk_entry_get_text(GTK_ENTRY(entry));
    position=gtk_entry_get_text_length(GTK_ENTRY(entry));
    gtk_editable_insert_text(GTK_EDITABLE(entry), c, -1, &position);
}

void clear()
{
    gtk_entry_set_text(GTK_ENTRY(entry), "");
}

void calculate()
{

}

void
activate (GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *grid;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Kalkulator");
    gtk_window_set_default_size (GTK_WINDOW (window), 400, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 60);

    grid = gtk_grid_new ();
    gtk_container_add(GTK_CONTAINER(window), grid);

    entry=gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 5, 1);

    button = gtk_button_new_with_label ("1");
    g_signal_connect( button, "clicked", G_CALLBACK(edit_entry), (gpointer) "1");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 1, 1);

    button=gtk_button_new_with_label("2");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "2");
    gtk_grid_attach(GTK_GRID(grid), button, 1, 1, 1, 1);

    button=gtk_button_new_with_label("3");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "3");
    gtk_grid_attach(GTK_GRID(grid), button, 2, 1, 1, 1);

    button=gtk_button_new_with_label("4");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "4");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 1, 1);

    button=gtk_button_new_with_label("5");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "5");
    gtk_grid_attach(GTK_GRID(grid), button, 1, 2, 1, 1);

    button=gtk_button_new_with_label("6");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "6");
    gtk_grid_attach(GTK_GRID(grid), button, 2, 2, 1, 1);

    button=gtk_button_new_with_label("7");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "7");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 3, 1, 1);

    button=gtk_button_new_with_label("8");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "8");
    gtk_grid_attach(GTK_GRID(grid), button, 1, 3, 1, 1);

    button=gtk_button_new_with_label("9");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "9");
    gtk_grid_attach(GTK_GRID(grid), button, 2, 3, 1, 1);

    button=gtk_button_new_with_label(".");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), ".");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 4, 1, 1);

    button=gtk_button_new_with_label("0");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "0");
    gtk_grid_attach(GTK_GRID(grid), button, 1, 4, 1, 1);

    button=gtk_button_new_with_label("+");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "+");
    gtk_grid_attach(GTK_GRID(grid), button, 3, 1, 1, 1);

    button=gtk_button_new_with_label("-");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "-");
    gtk_grid_attach(GTK_GRID(grid), button, 3, 2, 1, 1);

    button=gtk_button_new_with_label("*");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "*");
    gtk_grid_attach(GTK_GRID(grid), button, 3, 3, 1, 1);

    button=gtk_button_new_with_label("/");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "/");
    gtk_grid_attach(GTK_GRID(grid), button, 3, 4, 1, 1);

    button=gtk_button_new_with_label("^");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "^");
    gtk_grid_attach(GTK_GRID(grid), button, 2, 4, 1, 1);

    button=gtk_button_new_with_label("sin");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "sin");
    gtk_grid_attach(GTK_GRID(grid), button, 4, 1, 1, 1);

    button=gtk_button_new_with_label("cos");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "cos");
    gtk_grid_attach(GTK_GRID(grid), button, 4, 2, 1, 1);

    button=gtk_button_new_with_label("tan");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "tan");
    gtk_grid_attach(GTK_GRID(grid), button, 4, 3, 1, 1);

    button=gtk_button_new_with_label("ln");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "ln");
    gtk_grid_attach(GTK_GRID(grid), button, 4, 4, 1, 1);

    button=gtk_button_new_with_label(")");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), ")");
    gtk_grid_attach(GTK_GRID(grid), button, 4, 5, 1, 1);

    button=gtk_button_new_with_label("(");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "(");
    gtk_grid_attach(GTK_GRID(grid), button, 3, 5, 1, 1);

    button=gtk_button_new_with_label("=");
    g_signal_connect(button, "clicked", G_CALLBACK(calculate), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 5, 1, 1);

    button = gtk_button_new_with_label ("Clear");
    g_signal_connect_swapped( button, "clicked", G_CALLBACK(clear), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 5, 1, 1);

    button = gtk_button_new_with_label ("Quit");
    g_signal_connect_swapped( button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 5, 1, 1);

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
