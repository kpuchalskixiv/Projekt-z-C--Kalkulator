#include<stdio.h>
#include <math.h>
#include<string.h>
#include<stdlib.h>

typedef struct element {
    char value;
    struct element *next;
} el_listy;

el_listy *stos_operatorow;

void initstack(char a)
{
    stos_operatorow=NULL;
    stos_operatorow=malloc(sizeof(el_listy));
    stos_operatorow->value=a;
    stos_operatorow->next=NULL;
}

int precedence(char op)
{
    if(op=='^')
        return 4;
    if(op=='*' || op=='/')
        return 3;
    return 2;
}

char popback_stack(el_listy *head)
{
    if(head->next==NULL)
    {
        char z=head->value;
        head->value=NULL;
        return z;
    }
    else{
        el_listy *current=head->next;
        el_listy *pom;
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
    if(head->value==NULL)
        head->value==value1;
    else{
        el_listy *current=head;
        while(current->next!=NULL)
            current=current->next;
        current->next=malloc(sizeof(el_listy));
        current=current->next;
        current->value=value1;
        current->next=NULL;
    }
}

int main()
{
    double wynik;
    char *wyrazenie="1+2*3-(5-4)";
    initstack('a');
    int i;
    for(i=0; i<strlen(wyrazenie); i++)
        pushback_stack(stos_operatorow, wyrazenie[i]);
    printf("%c", top_stack(stos_operatorow));
    char z=popback_stack(stos_operatorow);
    printf("%c", top_stack(stos_operatorow));

}
