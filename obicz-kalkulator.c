#include<stdio.h>
#include <math.h>
#include<string.h>
#include<stdlib.h>
typedef struct wekto {
    char* data;
    unsigned int length;
    unsigned int capacity;
    //char znak;
} vector;

typedef struct element {
    char value;
    struct element *next;
} el_listy;

el_listy *stos_operatorow;

void initstack()
{
    stos_operatorow=NULL;
    stos_operatorow=malloc(sizeof(el_listy));
    stos_operatorow->value='a';
    stos_operatorow->next=NULL;
}

int precedence(char op)
{
    if(op=='^')
        return 4;
    if(op=='*' || op=='/')
        return 3;
    if(op=='a')
        return 1;
    return 2;
}

char popback_stack(el_listy *head)
{
    if(head->next==NULL)
        printf("head->NULL");
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
   // printf("last element:%d ", p);
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
    //wekt->znak=NULL;
    return wekt;
}
int zamien_na_ONP(vector *wyrazenie_w_ONP, char *expression)
{
    initstack();
    int i, a=strlen(expression);
    for(i=0; i<a; i++)
    {
    if(expression[i]!=' '){
      //  printf("%d ", i);
        while(i<a && ((expression[i]>='0' && expression[i]<='9')
                      || expression[i]==',')){
      //  while((expression[i]>='0' && expression[i]<='9') || expression[i]==',' )

            pushback(wyrazenie_w_ONP, expression[i]);
            i++;
        }
        if(wyrazenie_w_ONP->data[wyrazenie_w_ONP->length-1]>='0'
        && wyrazenie_w_ONP->data[wyrazenie_w_ONP->length-1]<='9')
            pushback(wyrazenie_w_ONP, '_');
        if(expression[i]!=' ')
        {
            if(stos_operatorow->next==NULL || expression[i]=='(')
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
                        if(z=='a')
                        {
                            printf("zle wpisane wyrazenie");
                            return 0;
                        }
                        pushback(wyrazenie_w_ONP, z);
                    }
                   // z=popback(stos_operatorow);
                }
                else
                {
                    char z;
                    while(precedence(expression[i])<=precedence(top_stack(stos_operatorow))
                          && !(expression[i]=='^' && top_stack(stos_operatorow)=='^')
                          && top_stack(stos_operatorow)!='(')
                    {
                        z=popback_stack(stos_operatorow);
                        pushback(wyrazenie_w_ONP, z);
                    }
                    pushback_stack(stos_operatorow, expression[i]);
                }
            }
        }
    }}
  /*  printf("%c\n", top_stack(stos_operatorow));
    int k;
    pushback(wyrazenie_w_ONP, popback_stack(stos_operatorow));
    for(k=0; k<wyrazenie_w_ONP->length; k++)
        printf("%c ", wyrazenie_w_ONP->data[k]);
    printf("\n");
    print_stack(stos_operatorow);
    char z; */
    while(top_stack(stos_operatorow)!='a')
        pushback(wyrazenie_w_ONP, popback_stack(stos_operatorow));
    return 1;
}
int main()
{
    double wynik;
    char *wyrazenie="3,25+4*2/(1-5)^2^3";
    vector *ONP=initvect();
    if(zamien_na_ONP(ONP, wyrazenie)){
    int j;
    //printf("\n%d ", ONP->length);
    for(j=0; j<ONP->length; j++)
        printf("%c ", ONP->data[j]);}
   //  c[3]='e';
    //printf("%c", c[0]);
}
