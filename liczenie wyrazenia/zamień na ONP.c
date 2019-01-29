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
      //  printf("znak: %c jego ASCII: %d\n", value1, value1);
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
//int f=0;
void pushback(vector *wekt, char znak)
{
   // printf("\n(%d: %c ASCII: %d)", f, znak, znak);
   // f++;
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
   // printf("#%d#\n", a);
    for(i=0; i<a; i++)
    {
      //  print_stack(stos_operatorow);
     //   printf("%d\n", i);
        while(i<a && ((expression[i]>='0' && expression[i]<='9')
                      || expression[i]==',')){
      //  while((expression[i]>='0' && expression[i]<='9') || expression[i]==',' )

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
                // z=popback(stos_operatorow);
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
  /*  printf("%c\n", top_stack(stos_operatorow));
    int k;
    pushback(wyrazenie_w_ONP, popback_stack(stos_operatorow));
    for(k=0; k<wyrazenie_w_ONP->length; k++)
        printf("%c ", wyrazenie_w_ONP->data[k]);
    printf("\n");
    print_stack(stos_operatorow);
    char z; */
    while(top_stack(stos_operatorow)!='#')
    {
        //if(top_stack(stos_operatorow)!=0)
            pushback(wyrazenie_w_ONP, popback_stack(stos_operatorow));
    }
    return 1;
}
int nawias_po_funkcji(char *expression, int i)
{
    if(expression[i]=='l')
    {
        if(expression[i+2]!='(')
            return 1;
        else
            return 0;
    }
    else
    {
        if(expression[i+3]!='(')
            return 2;
        else
            return 0;
    }
}
bool czy_bledne(char *expression)
{
    bool bledne=false;
    int nawiasy=0, przecinek, i, a=strlen(expression)
    for(i=0; i<a; i++)
    {
        if(bledne)
            break;
        przecinek=0;
        while(i<a && ((expression[i]>='0' && expression[i]<='9')
        || expression[i]==',')){
            if(expression[i]==',' && przecinek==1)
            {
                bledne=true;
                break;
            }
            if(expression[i]==',')
                przecinek=1;
            i++;
        }
        if(expression[i-1]==',')
            bledne=true;
        else{
            if(expression[i]=='(' && expression[i+1]==')')
                bledne=true;
            else{
                if(expression[i]=='(')
                {
                    nawiasy++;
                    if((expression[i+1]>='*' && expression[i+1]<='/')
                    || expression[i+1]=='^')
                        bledne=true;
                }
                else{
                    if(expression[i]==')')  nawiasy--;
                    else{
                        if(expression[i]>='a' && expression[i]<='z')
                        {
                            int p=nawias_po_funkcji(expression, i);
                            if(p==0)
                                bledne=true;
                            else
                                i+=p;
                        }
                        else{
                            if((expression[i+1]>=')' && expression[i+1]<='/')
                            || expression[i+1]=='^')
                                bledne=true;
                        }
                    }
                }
            }
        }

    }
    if(nawiasy!=0)
        bledne==true;
    if(bledne)
        return true; //tak, b³êdne
    else
        return false;
}

int main()
{
    double wynik;
    int i;
    //char *wyrazenie="1+sin(3+4*2/(1-5)^2^3)";
    char *wyrazenie="0,9999+1";
   /* printf("#%d#\n", strlen(wyrazenie));
    for(i=0; i<strlen(wyrazenie); i++)
        printf("%c*%d ", wyrazenie[i], wyrazenie[i]);
    printf("\n"); */
    vector *ONP=initvect();
    if(zamien_na_ONP(ONP, wyrazenie))
    {
        int j;
        for(j=0; j<ONP->length; j++)
            printf("%c", ONP->data[j], ONP->data[j]);
        //printf("dlugosc wyrazenia: %d\n", ONP->length);
    }
   // printf("%d", ONP->length);
   //  c[3]='e';
    //printf("%c", c[0]);
}
