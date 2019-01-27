#include<stdio.h>
#include <math.h>
#include<string.h>
#include<stdlib.h>
#define Q 1.11111111111
typedef struct wekto {
    char* data;
    unsigned int length;
    unsigned int capacity;
} vector;

typedef struct element {
    char value;
    struct element *next;
} el_listy;

el_listy *stos_operatorow;

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

void initstack()
{
    stos_operatorow=NULL;
    stos_operatorow=malloc(sizeof(el_listy));
    stos_operatorow->value='#';
    stos_operatorow->next=NULL;
}

int precedence(char op)
{
    if(op>='a' && op<='z')
        return 5;
    else
        if(op=='^')
            return 4;
        else
            if(op=='*' || op=='/')
                return 3;
            else
                if(op=='#')
                    return 1;
                else
                    return 2;
}

char popback_stack(el_listy *head)
{
    if(head->next==NULL)
        printf("dupa");
    else{
        el_listy *current=head->next;
        el_listy *pom=head;
        while(current->next!=NULL)
        {
            pom=current;
            current=current->next;
        }
        pom->next=NULL;
        char z=current->value;
        free(current);
        return z;
    }
}

char top_stack(el_listy *head)
{
    if(head->next==NULL)
    {
        char z=head->value;
        return z;
    }
    else{
        el_listy *current=head->next;
        while(current->next!=NULL)
            current=current->next;
        char z=current->value;
        return z;
    }
}

void pushback_stack(el_listy *head, char value1)
{

        el_listy *current=head;
        while(current->next!=NULL)
            current=current->next;
        current->next=malloc(sizeof(el_listy));
        current=current->next;
        current->value=value1;
        current->next=NULL;

}

void print_stack( el_listy * first)
{
    el_listy *current=first;
    while(current!=NULL)
    {
        printf("%c ", current->value);
        current=current ->next;
    }
}

void pushback(vector *wekt, char znak)
{
    if(wekt->length==0)
    {
        wekt->data=malloc(sizeof(char));
        wekt->capacity+=1;
        wekt->length+=1;
        wekt->data[0]=znak;
    }
    else{
    if(wekt->capacity<=wekt->length){
        wekt->capacity*=2;
        wekt->data=realloc(wekt->data, (wekt->capacity)*sizeof(char));
        wekt->data[wekt->length]=znak;
        wekt->length+=1;
        }
        else{
            wekt->data[wekt->length]=znak;
            wekt->length+=1;
        }

    }
}

char popback(vector *wekt)
{
    char p;
    p=wekt->data[wekt->length-1];
    free(wekt->data[wekt->length-1]);
    wekt->length-=1;
    return p;
}

vector *initvect()
{
    vector *wekt=malloc(sizeof(vector));
    wekt->length=0;
    wekt->capacity=0;
    wekt->data=NULL;
    return wekt;
}
int zamien_na_ONP(vector *wyrazenie_w_ONP, char *expression)
{
    initstack();
    int i, a=strlen(expression);
    for(i=0; i<a; i++)
    {
        while(i<a && ((expression[i]>='0' && expression[i]<='9')
                      || expression[i]=='.')){

            pushback(wyrazenie_w_ONP, expression[i]);
            i++;
        }

        if(i==a)
            break;

        if(wyrazenie_w_ONP->length>0){
        if(wyrazenie_w_ONP->data[wyrazenie_w_ONP->length-1]>='0'
        && wyrazenie_w_ONP->data[wyrazenie_w_ONP->length-1]<='9')
            pushback(wyrazenie_w_ONP, '_'); }

        if(expression[i]>='a' && expression[i]<='z')
        {
            pushback_stack(stos_operatorow, expression[i]);
            while(i<a && expression[i]>='a' && expression[i]<='z')
                i++;
        }
        if(expression[i]=='(')
            pushback_stack(stos_operatorow, expression[i]);
        else
        {
            if(expression[i]==')')
            {
                char z;
                while(1)
                {
                    z=popback_stack(stos_operatorow);
                    if(z=='(')
                        break;
                    if(z=='#')
                    {
                        printf("zle wpisane wyrazenie");
                        return 0;
                    }
                    pushback(wyrazenie_w_ONP, z);
                }
            }
            else
            {
                char z;
                while((precedence(top_stack(stos_operatorow))==5
                    || precedence(expression[i])<precedence(top_stack(stos_operatorow))
                    || (precedence(expression[i])==precedence(top_stack(stos_operatorow))
                        && expression[i]!='^'))
                    && top_stack(stos_operatorow)!='(')
                {
                    z=popback_stack(stos_operatorow);
                    pushback(wyrazenie_w_ONP, z);
                }
                pushback_stack(stos_operatorow, expression[i]);
            }
        }
    }
    while(top_stack(stos_operatorow)!='#')
        pushback(wyrazenie_w_ONP, popback_stack(stos_operatorow));
    return 1;
}

void print_stack_calculate( stackss * first)
{
    stackss *current=first;
    while(current!=NULL)
    {
        printf("%f ", current->value);
        current=current ->next;
    }
}

double popback_stack_calculate(stackss *head)
{
    if(head->next==NULL){
        //printf("wielkosc stosu po popie: %d i spopowany element: %f\n", stack_size_calculate(head), head->value);
        return head->value;
    }
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
       // printf("wielkosc stosu po popie: %d i spopowany element: %f\n", stack_size_calculate(head), z);
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
   // printf("\n%c\n", z);
    double a, b;
    if(z=='_')
        return Q;
    else{
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
        if(z=='+') return b+a;
        if(z=='-') return b-a;
        if(z=='*') return b*a;
        if(z=='/') return b/a;
        if(z=='^') return pow(b, a);
    }
    }
}

double oblicz_onp(vector *wyrazenie_w_ONP)
{
    int j=0, w, i=0;
    char l[30];
    double x;
    initstack_calculate();
    char *expression=wyrazenie_w_ONP->data;
    for(i=0; i<wyrazenie_w_ONP->length; i++){
       // printf("%c", expression[i]);
        while(i<wyrazenie_w_ONP->length &&
            ((expression[i]>='0' && expression[i]<='9')
            || expression[i]=='.'))
        {
            l[j]=expression[i];
            j++;
            i++;
        }
        if(j>0)
        {
            l[j]='\0';
            for(w=0; w<j; w++)
                printf("%c", l[j]);
            x=atof(l);
            printf("#%d  %f#", j, x);
          //  printf("%f %d\n", x, i);
            pushback_stack_calculate(stos_obliczen, x);
            j=0;
        }
        if(!j && expression[i]!='_')
        {
            double y=licz(expression[i]);
            if(y!=Q)
                pushback_stack_calculate(stos_obliczen, y);
        }
    }
    return popback_stack_calculate(stos_obliczen);
}

int main()
{
    double wynik;
    int j;
   // char *wyrazenie="sin(3+4*2/(1-5)^2^3)";
    char *wyrazenie="1.2+3";
    vector *ONP=initvect();
    if(zamien_na_ONP(ONP, wyrazenie))
    {
       /* int j;
        for(j=0; j<ONP->length; j++)
            printf("%c", ONP->data[j]);
        printf(" dlugosc wyrazenia: %d\n", ONP->length); */
        wynik=oblicz_onp(ONP);
        printf("wynik: %f ", wynik);
        printf("%d\n", sizeof(wynik));
        char s[sizeof(wynik)];
        snprintf(s, sizeof(wynik), "%f", wynik);
        printf("wynik: %s", s);

    }
    return 0;
}
