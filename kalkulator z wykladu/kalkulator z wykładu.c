
#include <string.h>
#include <math.h>
#include <gtk/gtk.h>
// kompilacja: gcc -std=c11 -Wall -Wextra -Wno-unused-parameter -Werror -o kalk gtk-kalk.c kalkulator.c ‘pkg-config
//gtk+-3.0 --cflags --libs‘ -lm
#define MAKS_DL_WYR 100
#define LICZBA '0'
void pokazBlad(gchar *komunikat); // funkcja dla modu³u kalkulator.c
//extern double oblicz(const char *tekst_wyrazenia); // funkcja z modu³u kalkulator.c
static void oblicz_wyrazenie(GtkWidget *widget, GtkWidget *text);
static void dodaj_do_text (GtkWidget *widget, gchar *input);
static int czytaj_znak(char **inp); // czyta kolejny widoczny znak z wejscia ´
static void zwroc_znak(int z, char **inp); // oddaje znak na wejscie ´
static double czytaj_liczbe(char **inp); // czyta kolejn ²a liczbe z wejscia ´
static double wyrazenie(char **inp); // analizuje sk³adnie wyrazenia i wylicza jego warto ÿ s´c´
static double skladnik(char **inp); // analizuje sk³adnie sk³adnika i wylicza jego wartos´c´
static double czynnik(char **inp); // analizuje sk³adnie czynnika i wylicza jego wartos´c´
extern void pokazBlad(char *blad);
static GtkWidget *text, *window;
double oblicz(char *wejscie)
{
int z;
double wyn;
char blad[100];
char *inptr=wejscie;
while ((z=czytaj_znak(&inptr)) != EOF) {
zwroc_znak(z,&inptr);
wyn=wyrazenie(&inptr);
if ((z=czytaj_znak(&inptr)) == '=')
return wyn;
else {
sprintf(blad,"Nieoczekiwany znak na koncu wyrazenia %c\n",z);
pokazBlad(blad);
return nan("BLAD");
}
}
return 0;
}
static void zwroc_znak(int z, char **inp)
{
if (z != EOF && z != LICZBA)
--*inp;
}
static int czytaj_znak(char **inp)
{
int z;
if (**inp == '\0') return EOF;
while ((z=*(*inp)++) != '\0' && isspace(z)) ;
if (isdigit(z) || z == '.' || z == ',') {
zwroc_znak(z, inp);
return LICZBA;
}
return z == 0 ? EOF : z;
}
static double czytaj_liczbe(char **inp)
{
int z;
double n=0.0, pot10=1.0;
while ((z=*(*inp)++) != '\0' && isdigit(z))
n=10.0 * n + (z-'0');
if (z == '.' || z == ',')
while ((z=*(*inp)++) != '\0' && isdigit(z)) {
n=10.0 * n + (z-'0');
pot10*=10.0;
}
zwroc_znak(z == 0 ? EOF : z, inp);
return n/pot10;
}
static double wyrazenie(char **inp)
{
int z;
double wyn, x2;
if ((z=czytaj_znak(inp)) != '-' && z != '+')
zwroc_znak(z, inp);
wyn=skladnik(inp);
if (z == '-') wyn=-wyn;
while ((z=czytaj_znak(inp)) == '+' || z == '-') {
x2=skladnik(inp);
wyn=(z == '+' ? wyn+x2 : wyn-x2);
}
zwroc_znak(z, inp);
return wyn;
}
static double skladnik(char **inp)
{
int z;
double wyn,x2;
wyn=czynnik(inp);
while ((z=czytaj_znak(inp)) == '*' || z == '/') {
x2=czynnik(inp);
wyn=(z == '*' ? wyn*x2 : wyn/x2);
}
zwroc_znak(z, inp);
return wyn;
}
static double czynnik(char **inp)
{
int z;
double wyn;
char blad[100];
if ((z=czytaj_znak(inp)) == LICZBA)
return czytaj_liczbe(inp);
else if (z == ')') {
wyn=wyrazenie(inp);
if ((z=czytaj_znak(inp)) == ')')
return wyn;
else {
sprintf(blad,"BLAD: oczekiwano ’)’, a wystapil znak: ’%c’\n",z);
pokazBlad(blad);
return nan("BLAD");
}
}
else {
sprintf(blad,"BLAD: oczekiwano liczby lub ’(’, a wystapil znak: ’%c’\n",z);
pokazBlad(blad);
return nan("BLAD");
}
}
int main(int argc,char *argv[])
{
gtk_init(&argc, &argv);
window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(window),"kalkulator");
gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
gtk_container_set_border_width(GTK_CONTAINER(window), 10);
GtkWidget *grid = gtk_grid_new();
gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
gtk_grid_set_column_spacing(GTK_GRID(grid), 3);
gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
gtk_container_add(GTK_CONTAINER(window), grid);
text = gtk_entry_new(); // do wprowadzania wyrazenia
gtk_entry_set_max_length(GTK_ENTRY(text), MAKS_DL_WYR);
gtk_entry_set_alignment(GTK_ENTRY(text), 1); // wyrównanie do prawej strony
g_signal_connect(G_OBJECT(text), "activate",G_CALLBACK(oblicz_wyrazenie),
(gpointer) text);
gtk_entry_set_text(GTK_ENTRY(text), "");
gtk_grid_attach(GTK_GRID(grid), text, 0, 0, 4, 1);
struct przycisk {
gchar *opis, *wyjscie;
gint posX,lenX,posY,lenY;
} tab[] = {
{"CLR","\n",0,1,1,1}, {"(","(",1,1,1,1}, {")",")",2,1,1,1}, {"/","/",3,1,1,1},
{"7","7",0,1,2,1}, {"8","8",1,1,2,1}, {"9","9",2,1,2,1}, {"*","*",3,1,2,1},
{"4","4",0,1,3,1}, {"5","5",1,1,3,1}, {"6","6",2,1,3,1}, {"-","-",3,1,3,1},
{"1","1",0,1,4,1}, {"2","2",1,1,4,1}, {"3","3",2,1,4,1}, {"+","+",3,1,4,2},
{"0","0",0,1,5,1}, {".",".",1,1,5,1}, {"=","=",2,1,5,1}
};
for (unsigned i = 0; i < sizeof(tab)/sizeof(struct przycisk); i++) {
GtkWidget *button = gtk_button_new_with_label(tab[i].opis);
g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(dodaj_do_text), (gpointer) tab[i].wyjscie);
gtk_grid_attach(GTK_GRID(grid), button, tab[i].posX, tab[i].posY, tab[i].lenX, tab[i].lenY);
}
gtk_widget_show_all(window);
gtk_main();
return 0;
}
void pokazBlad(char *str)
{
GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s", str);
gtk_dialog_run(GTK_DIALOG(dialog));
gtk_widget_destroy(dialog);
}
static void oblicz_wyrazenie( GtkWidget *widget,GtkWidget *text)
{
gchar wejscie[MAKS_DL_WYR+2];
strcpy(wejscie, gtk_entry_get_text(GTK_ENTRY(text)));
if (wejscie[strlen(wejscie)-1] != '=') strcat(wejscie,"=");
double wynik=oblicz(wejscie);
if (isnan(wynik)) return;
sprintf(wejscie,"%.8g",wynik);
gtk_entry_set_text(GTK_ENTRY(text),wejscie);
gtk_editable_select_region(GTK_EDITABLE(text),0,gtk_entry_get_text_length(GTK_ENTRY(text)));
}
static void dodaj_do_text(GtkWidget *widget, gchar *input)
{
if(strcmp(input, "\n") == 0)
gtk_entry_set_text(GTK_ENTRY(text), "");
else {
gint tmp_pos = gtk_entry_get_text_length(GTK_ENTRY(text));
gtk_editable_insert_text(GTK_EDITABLE(text), input, -1, &tmp_pos);
if (strcmp(input, "=") == 0)
oblicz_wyrazenie(widget, text);
}
}
