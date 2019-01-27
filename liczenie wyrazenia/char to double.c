#include<stdio.h>
#include <math.h>
#include<string.h>
#include<stdlib.h>
#define Q 1.11111111111
typedef struct wekto {
    char* data;
    unsigned int length;
    unsigned int capacity;
    //char znak;
} vector;

typedef struct stack {
    double value;
    struct stack *next;
}stackss;

stackss *stos_obliczen;

void initstack_calculate()
{
    stos_obliczen=NULL;
    stos_obliczen=malloc(sizeof(stackss));
    stos_obliczen->value=Q;
    stos_obliczen->next=NULL;
}

double popback_stack_calculate(stackss *head)
{
    if(head->next==NULL)
        printf("head->NULL");
    else{
        stackss *current=head->next;
        stackss *pom=head;
        while(current->next!=NULL)
        {
            pom=current;
            current=current->next;
        }
        pom->next=NULL;
        double z=current->value;
        free(current);
        return z;
    }
}

int stack_size_calculate(stackss *head)
{
    if(head->next==NULL)
        return 0;
    else{
        int k=0;
        stackss *current=head;
        while(current->next!=NULL)
        {
            current=current->next;
            k++;
        }
        return k;
    }
}

void pushback_stack_calculate(stackss *head, double value1)
{

        stackss *current=head;
        while(current->next!=NULL)
            current=current->next;
        current->next=malloc(sizeof(stackss));
        current=current->next;
        current->value=value1;
        current->next=NULL;

}
double licz(char z)
{
    double a, b;
    if(z>='a' && z<='z')
    {
        a=popback_stack_calculate(stos_obliczen);
        if(z=='s') return sin(a);
        else{
            if(z=='c') return cos(a);
            else{
                if(z=='t') return tan(a);
                else{
                    if(z=='l') return log(a);
                }

            }
        }
    }
    else
    {
        a=popback_stack_calculate(stos_obliczen);
        b=popback_stack_calculate(stos_obliczen);
        if(z=='+') return a+b;
        if(z=='-') return a-b;
        if(z=='*') return a*b;
        if(z=='/') return a/b;
        if(z=='^') return pow(a, b);
    }
}

void oblicz_onp(vector *wyrazenie_w_ONP)
{
    int j, z=0, w, i=0;
    char l[30];
    double x;
    initstack_calculate();
    char *expression=wyrazenie_w_ONP->data;
    for(i=0; i<wyrazenie_w_ONP->length; i++){
        j=0;
        while((expression[i]>='0' && expression[i]<='9')
            || expression[i]=='.')
        {
            l[j]=expression[i];
            j++;
            i++;
        }
        if(j>0)
        {
            l[j]='\0';
            x=atof(l);
            pushback_stack_calculate(stos_obliczen, x);
        }
        if(!j && expression[i]!='_')
        {
            double y=licz(expression[i]);
            pushback_stack_calculate(stos_obliczen, y);
    }
    if(stack_size_calculate(stos_obliczen)==1)
        printf("%f", popback_stack_calculate(stos_obliczen));
}

int main()
{
   /* char *expression="3.45+1";
    int j, w, z=0, i=0;
    char l[10];
    double y;
    y=atof(l);
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
        l[j]='\0';
        t[z]=atof(l);
        //l[0]='.';
      //  for(w=0; w<10; w++)
      //      l[i]='0';
     //   l[1]='.';
        y=atof(l);
        z++;
    } */
    char *s="-32.5";
    double x=atof(s);
    printf("%f ", x );
  // for(i=0; i<z; i++)
    //    printf("%f ", t[i]);
}
