#include <gtk/gtk.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

typedef struct wekto {
    char* data;
    unsigned int length;
    unsigned int capacity;
    char znak;
} vector;
int i=0;
char* napis;
static void
dodaj_do_napisu(char a)
{
    napis=a;
    i++;
}
static void
pushback(GtkWidget *widget, gpointer data, vector *wekt)
{
    if(wekt->length==0)
    {
        wekt->data=malloc(sizeof(char));
        wekt->capacity+=1;
        wekt->length+=1;
        wekt->data[0]=wekt->znak;
    }
    else{
    if(wekt->capacity<=wekt->length){
        wekt->capacity*=2;
        wekt->data=realloc(wekt->data, (wekt->capacity)*sizeof(char));
        wekt->data[wekt->length]=wekt->znak;
        wekt->length+=1;
        }
        else{
            wekt->data[wekt->length]=wekt->znak;
            wekt->length+=1;
        }

    }
}

vector *initvect()
{
    vector *wekt=malloc(sizeof(vector));
    wekt->length=0;
    wekt->capacity=0;
    wekt->data=NULL;
    wekt->znak=NULL;
    return wekt;
}
static void print_string(GtkWidget *widget, gpointer data)
{
    int j;
    g_print("", napis);
  //  for(j=0; j<i; j++)
   //     g_print("%c", napis[j]);
}
static void
print_hello (GtkWidget *widget, gpointer data)
{
  g_print ("hello");
}


static void
activate (GtkApplication* app, gpointer user_data)
{
    vector *wektor=initvect();
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Kalkulator");
    gtk_container_set_border_width(GTK_CONTAINER(window), 50);
    /* Here we construct the container that is going pack our buttons */
    grid = gtk_grid_new ();
    gtk_container_add(GTK_CONTAINER(window), grid);

   // GtkWidget *entry=gtk_entry_new();
    const gchar *str="abcd";
    GtkWidget *entry=gtk_label_new (str);
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);

    button=gtk_button_new_with_label("1");
    wektor->znak="a";
    g_signal_connect(button, "clicked", G_CALLBACK(dodaj_do_napisu), "1");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 1, 1);
/*
    button=gtk_button_new_with_label("2");
    wektor_ichar->znak='2';
    g_signal_connect(button, "clicked", G_CALLBACK(pushback), wektor_ichar);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

    button=gtk_button_new_with_label("3");
    wektor_ichar->znak='3';
    g_signal_connect(button, "clicked", G_CALLBACK(pushback),  wektor_ichar);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 0, 1, 1);

    button=gtk_button_new_with_label("4");
    wektor_ichar->znak='4';
    g_signal_connect(button, "clicked", G_CALLBACK(pushback),  wektor_ichar);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 1, 1);

    button=gtk_button_new_with_label("5");
    wektor_ichar->znak='5';
    g_signal_connect(button, "clicked", G_CALLBACK(pushback),  wektor_ichar);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 1, 1, 1);

    button=gtk_button_new_with_label("6");
    wektor_ichar->znak='6';
    g_signal_connect(button, "clicked", G_CALLBACK(pushback),  wektor_ichar);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 1, 1, 1);

    button=gtk_button_new_with_label("7");
    wektor_ichar->znak='7';
    g_signal_connect(button, "clicked", G_CALLBACK(pushback), wektor_ichar);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 1, 1);

    button=gtk_button_new_with_label("8");
    wektor_ichar->znak='8';
    g_signal_connect(button, "clicked", G_CALLBACK(pushback),  wektor_ichar);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 2, 1, 1);

    button=gtk_button_new_with_label("9");
    wektor_ichar->znak='9';
    g_signal_connect(button, "clicked", G_CALLBACK(pushback), wektor_ichar);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 2, 1, 1);

    button=gtk_button_new_with_label("0");
    wektor_ichar->znak='0';
    g_signal_connect(button, "clicked", G_CALLBACK(pushback),  wektor_ichar);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 3, 1, 1);

    button=gtk_button_new_with_label(".");
    wektor_ichar->znak='.';
    g_signal_connect(button, "clicked", G_CALLBACK(pushback), wektor_ichar);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 3, 1, 1);

    button=gtk_button_new_with_label("+");
    wektor_ichar->znak='+';
    g_signal_connect(button, "clicked", G_CALLBACK(pushback), wektor_ichar);
    gtk_grid_attach(GTK_GRID(grid), button, 3, 0, 1, 1);

    button=gtk_button_new_with_label("-");
    wektor_ichar->znak='-';
    g_signal_connect(button, "clicked", G_CALLBACK(pushback), wektor_ichar);
    gtk_grid_attach(GTK_GRID(grid), button, 3, 1, 1, 1);

    button=gtk_button_new_with_label("*");
    wektor_ichar->znak='*';
    g_signal_connect(button, "clicked", G_CALLBACK(pushback), wektor_ichar);
    gtk_grid_attach(GTK_GRID(grid), button, 3, 2, 1, 1);

    button=gtk_button_new_with_label("/");
    wektor_ichar->znak='/';
    g_signal_connect(button, "clicked", G_CALLBACK(pushback), wektor_ichar);
    gtk_grid_attach(GTK_GRID(grid), button, 3, 3, 1, 1);
*/
    button=gtk_button_new_with_label("=");
    g_signal_connect(button, "clicked", G_CALLBACK(print_string), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 1, 1, 1);

    button = gtk_button_new_with_label ("Quit");
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_grid_attach (GTK_GRID (grid), button, 3, 1, 1, 1);
    gtk_widget_show_all(window);
}
int main(int argc, char **argv)
{
   // int cap, len, n, i;
    //char a;
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}

