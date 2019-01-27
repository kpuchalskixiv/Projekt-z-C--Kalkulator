#include <gtk/gtk.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
int i=0;
char wyr[100];
char znak='7';
static void addtostring(GtkWidget *widget, gpointer data, char a)
{
    //wyr[i]=a;
    i++;
}
static void print_string(GtkWidget *widget, gpointer data)
{
    int j;
    for(j=0; j<i; j++)
        g_print("%c", wyr[j]);
}
static void
print_hello (GtkWidget *widget, gpointer data)
{
  g_print ("Hello World\n");
}

static void
print_hello2 (GtkWidget *widget, gpointer data)
{
  g_print ("Hello World no. 02\n");
}

static void
activate (GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_container_set_border_width(GTK_CONTAINER(window), 50);
    /* Here we construct the container that is going pack our buttons */
    grid = gtk_grid_new ();
    gtk_container_add(GTK_CONTAINER(window), grid);
    button=gtk_button_new_with_label("1");
    g_signal_connect(button, "clicked", G_CALLBACK(addtostring), '1');
    /* Place the first button in the grid cell (0, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

    button=gtk_button_new_with_label("2");
    g_signal_connect(button, "clicked", G_CALLBACK(addtostring), '2');
    gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

    /*button=gtk_button_new_with_label("3");
    g_signal_connect(button, "clicked", G_CALLBACK(addtostring), '3');
    gtk_grid_attach(GTK_GRID(grid), button, 2, 0, 1, 1);

    button=gtk_button_new_with_label("4");
    g_signal_connect(button, "clicked", G_CALLBACK(addtostring), '4');
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 1, 1);

    button=gtk_button_new_with_label("5");
    g_signal_connect(button, "clicked", G_CALLBACK(addtostring), '5');
    gtk_grid_attach(GTK_GRID(grid), button, 1, 1, 1, 1);

    button=gtk_button_new_with_label("6");
    g_signal_connect(button, "clicked", G_CALLBACK(addtostring), '6');
    gtk_grid_attach(GTK_GRID(grid), button, 2, 1, 1, 1);

    button=gtk_button_new_with_label("7");
    g_signal_connect(button, "clicked", G_CALLBACK(addtostring), '7');
    gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 1, 1);

    button=gtk_button_new_with_label("8");
    g_signal_connect(button, "clicked", G_CALLBACK(addtostring), '8');
    gtk_grid_attach(GTK_GRID(grid), button, 1, 2, 1, 1);

    button=gtk_button_new_with_label("9");
    g_signal_connect(button, "clicked", G_CALLBACK(addtostring), '9');
    gtk_grid_attach(GTK_GRID(grid), button, 2, 2, 1, 1);

    button=gtk_button_new_with_label("0");
    g_signal_connect(button, "clicked", G_CALLBACK(addtostring), '0');
    gtk_grid_attach(GTK_GRID(grid), button, 1, 3, 1, 1);

    button=gtk_button_new_with_label(".");
    g_signal_connect(button, "clicked", G_CALLBACK(addtostring), '.');
    gtk_grid_attach(GTK_GRID(grid), button, 2, 3, 1, 1);

    button=gtk_button_new_with_label("+");
    g_signal_connect(button, "clicked", G_CALLBACK(addtostring), '+');
    gtk_grid_attach(GTK_GRID(grid), button, 3, 0, 1, 1);

    button=gtk_button_new_with_label("-");
    g_signal_connect(button, "clicked", G_CALLBACK(addtostring), '-');
    gtk_grid_attach(GTK_GRID(grid), button, 3, 1, 1, 1);

    button=gtk_button_new_with_label("*");
    g_signal_connect(button, "clicked", G_CALLBACK(addtostring), '*');
    gtk_grid_attach(GTK_GRID(grid), button, 3, 2, 1, 1);

    button=gtk_button_new_with_label("/");
    g_signal_connect(button, "clicked", G_CALLBACK(addtostring), '/');
    gtk_grid_attach(GTK_GRID(grid), button, 3, 3, 1, 1);

    button=gtk_button_new_with_label("=");
    g_signal_connect(button, "clicked", G_CALLBACK(print_string), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 4, 0, 1, 3); */

    button = gtk_button_new_with_label ("Quit");
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_grid_attach (GTK_GRID (grid), button, 0, 3, 1, 1);
    gtk_widget_show_all(window);
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
