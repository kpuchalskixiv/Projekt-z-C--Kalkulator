#include<stdio.h>
#include <math.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    char *expression="3.45+12";
    int j, z=0, i=0;
    char l[10];
    double t[10];
    for(i=0; i<strlen(expression); i++){
        j=0;
        while((expression[i]>='0' && expression[i]<='9')
            || expression[i]=='.')
        {
            l[j]=expression[i];
            j++;
            i++;
        }
        t[z]=atof(l);
        z++;
    }
   // double x=atof(s);
   for(i=0; i<z; i++)
        printf("%f ", t[i]);
}
