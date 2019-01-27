
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
/********* kalkulator.c: kalkulator dla wyrazen rzeczywistych **********
* Modu³ udost ²epnia funkcj ²e double oblicz(char *tekst_wyrazenia), która
* czyta z tekst_wyrazenia zapisane z uzyciem nawiasow i czterech
* podstawowych dzialan wyrazenie (zakonczone znakiem =) i oblicza je ´
* rekurencyjnie. Wartos´c wyra ´ zenia zwracana jest jako wynik obliczenia. ÿ
***************************************************************************/
#define LICZBA ’0’
/***************** PROTOTYPY FUNKCJI ********************/
static int czytaj_znak(char **inp); // czyta kolejny widoczny znak z wejscia ´
static void zwroc_znak(int z, char **inp); // oddaje znak na wejscie ´
static double czytaj_liczbe(char **inp); // czyta kolejn ²a liczbe z wejscia ´
static double wyrazenie(char **inp); // analizuje sk³adnie wyrazenia i wylicza jego warto ÿ s´c´
static double skladnik(char **inp); // analizuje sk³adnie sk³adnika i wylicza jego wartos´c´
static double czynnik(char **inp); // analizuje sk³adnie czynnika i wylicza jego wartos´c´
extern void pokazBlad(char *blad);
 // funkcja z zewn ²etrznego modu³u do sygnalizacji b³ ²edu
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

