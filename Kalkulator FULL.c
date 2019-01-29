#include <gtk/gtk.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define Q 1.11111111111

GtkApplication *app;
GtkWidget *entry;

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
        return head->value;
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
                      || expression[i]==',')){

            pushback(wyrazenie_w_ONP, expression[i]);
            i++;
        }

        if(i==a)
        {

            break;
        }

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
                        zle_wyrazenie();
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
    if(head->next==NULL)
        return head->value;
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
    if(z=='_')
        return Q;
    else{
    a=popback_stack_calculate(stos_obliczen);
    if(a!=Q){
        if(z>='a' && z<='z')
        {
            if(z=='s') return sin(a);
            if(z=='c') return cos(a);
            if(z=='t') return tan(a);
            if(z=='l') return log(a);
        }
        else
        {
            b=popback_stack_calculate(stos_obliczen);
            if(b!=Q){
                if(z=='+') return b+a;
                if(z=='-') return b-a;
                if(z=='*') return b*a;
                if(z=='/') return b/a;
                if(z=='^') return pow(b, a);
            }
        }
    }
    else return Q;
    }
}

double oblicz_onp(vector *wyrazenie_w_ONP)
{
    int j=0, w, i=0;
    char number[90];
    double x;
    initstack_calculate();
    char *expression=wyrazenie_w_ONP->data;
    for(i=0; i<wyrazenie_w_ONP->length; i++){
        while(i<wyrazenie_w_ONP->length &&
            ((expression[i]>='0' && expression[i]<='9')
            || expression[i]==','))
        {
            number[j]=expression[i];
            j++;
            i++;
        }
        if(j>0)
        {
            number[j]='\0';
            x=atof(number);
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


void edit_entry(GtkWidget *widget, gchar *c)
{
    gint position;
    char *text=gtk_entry_get_text(GTK_ENTRY(entry));
    position=gtk_entry_get_text_length(GTK_ENTRY(entry));
    gtk_editable_insert_text(GTK_EDITABLE(entry), c, -1, &position);
}

void clear()
{
    gtk_entry_set_text(GTK_ENTRY(entry), "");
}
void zle_wyrazenie()
{
    GtkWidget *okno;
    GtkWidget *grid;
    GtkWidget *button;
    okno = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (okno), "BAD EXPRESSION");
    gtk_window_set_default_size (GTK_WINDOW (okno), 100, 50);
    gtk_container_set_border_width(GTK_CONTAINER(okno), 10);

    grid = gtk_grid_new ();
    gtk_container_add(GTK_CONTAINER(okno), grid);

    button = gtk_button_new_with_label ("You wrote incorrect expression, please enter new one");
    g_signal_connect(button, "clicked", G_CALLBACK(clear), NULL);
    g_signal_connect_swapped( button, "clicked", G_CALLBACK(gtk_widget_destroy), okno);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);
    gtk_widget_show_all (okno);
}

void calculate()
{
    double wynik;
    char *wyrazenie=gtk_entry_get_text(GTK_ENTRY(entry));
    if(czy_bledne(wyrazenie))
        zle_wyrazenie();
    else{
        vector *ONP=initvect();
        if(zamien_na_ONP(ONP, wyrazenie))
        {
            wynik=oblicz_onp(ONP);
            if(wynik==Q)
                zle_wyrazenie();
            else{
                int n=90;
                char s[n];
                snprintf(s, n, "%f", wynik);
                gtk_entry_set_text(GTK_ENTRY(entry), s);
            }
        }
    }
}

int nawias_po_funkcji(char *expression, int i)
{
    if(expression[i]=='l')
    {
        if(expression[i+2]=='(')
            return 1;
        else
            return 0;
    }
    else
    {
        if(expression[i+3]=='(')
            return 2;
        else
            return 0;
    }
}

int czy_bledne(char *expression)
{
    int bledne=0;
    int nawiasy=0, przecinek, i, a=strlen(expression);
    for(i=0; i<a; i++)
    {
        if(bledne)
            break;
        if(nawiasy<0)
        {
            bledne=1;
            break;
        }
        przecinek=0;
        while(i<a && ((expression[i]>='0' && expression[i]<='9')
        || expression[i]==',')){
            if(expression[i]==',' && przecinek==1)
            {
                bledne=1;
                break;
            }
            if(expression[i]==',')
                przecinek=1;
            i++;
        }
        if(expression[i-1]==',')
            bledne=1;
        else{
            if(expression[i]=='(' && expression[i+1]==')')
                bledne=1;
            else{
                if(expression[i]=='(')
                {
                    nawiasy++;
                    if((expression[i+1]>='*' && expression[i+1]<='/')
                    || expression[i+1]=='^')
                        bledne=1;
                }
                else{
                    if(expression[i]==')')  nawiasy--;
                    else{
                        if(expression[i]>='a' && expression[i]<='z')
                        {
                            int p=nawias_po_funkcji(expression, i);
                            if(p==0)
                                bledne=1;
                            else
                                i+=p;
                        }
                        else{
                            if((expression[i+1]>=')' && expression[i+1]<='/')
                            || expression[i+1]=='^')
                                bledne=1;
                        }
                    }
                }
            }
        }

    }
    if(nawiasy!=0)
        bledne==1;
    if(bledne)
        return 1; //tak, b³êdne
    else
        return 0;
}

void activate (gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *grid;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Kalkulator");
    gtk_window_set_default_size (GTK_WINDOW (window), 400, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 60);

    grid = gtk_grid_new ();
    gtk_container_add(GTK_CONTAINER(window), grid);

    entry=gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 5, 1);
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1);

    button = gtk_button_new_with_label ("1");
    g_signal_connect( button, "clicked", G_CALLBACK(edit_entry), (gpointer) "1");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 1, 1);

    button=gtk_button_new_with_label("2");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "2");
    gtk_grid_attach(GTK_GRID(grid), button, 1, 1, 1, 1);

    button=gtk_button_new_with_label("3");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "3");
    gtk_grid_attach(GTK_GRID(grid), button, 2, 1, 1, 1);

    button=gtk_button_new_with_label("4");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "4");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 1, 1);

    button=gtk_button_new_with_label("5");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "5");
    gtk_grid_attach(GTK_GRID(grid), button, 1, 2, 1, 1);

    button=gtk_button_new_with_label("6");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "6");
    gtk_grid_attach(GTK_GRID(grid), button, 2, 2, 1, 1);

    button=gtk_button_new_with_label("7");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "7");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 3, 1, 1);

    button=gtk_button_new_with_label("8");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "8");
    gtk_grid_attach(GTK_GRID(grid), button, 1, 3, 1, 1);

    button=gtk_button_new_with_label("9");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "9");
    gtk_grid_attach(GTK_GRID(grid), button, 2, 3, 1, 1);

    button=gtk_button_new_with_label(",");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), ",");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 4, 1, 1);

    button=gtk_button_new_with_label("0");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "0");
    gtk_grid_attach(GTK_GRID(grid), button, 1, 4, 1, 1);

    button=gtk_button_new_with_label("+");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "+");
    gtk_grid_attach(GTK_GRID(grid), button, 3, 1, 1, 1);

    button=gtk_button_new_with_label("-");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "-");
    gtk_grid_attach(GTK_GRID(grid), button, 3, 2, 1, 1);

    button=gtk_button_new_with_label("*");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "*");
    gtk_grid_attach(GTK_GRID(grid), button, 3, 3, 1, 1);

    button=gtk_button_new_with_label("/");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "/");
    gtk_grid_attach(GTK_GRID(grid), button, 3, 4, 1, 1);

    button=gtk_button_new_with_label("^");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "^");
    gtk_grid_attach(GTK_GRID(grid), button, 2, 4, 1, 1);

    button=gtk_button_new_with_label("sin");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "sin");
    gtk_grid_attach(GTK_GRID(grid), button, 4, 1, 1, 1);

    button=gtk_button_new_with_label("cos");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "cos");
    gtk_grid_attach(GTK_GRID(grid), button, 4, 2, 1, 1);

    button=gtk_button_new_with_label("tan");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "tan");
    gtk_grid_attach(GTK_GRID(grid), button, 4, 3, 1, 1);

    button=gtk_button_new_with_label("ln");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "ln");
    gtk_grid_attach(GTK_GRID(grid), button, 4, 4, 1, 1);

    button=gtk_button_new_with_label(")");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), ")");
    gtk_grid_attach(GTK_GRID(grid), button, 4, 5, 1, 1);

    button=gtk_button_new_with_label("(");
    g_signal_connect(button, "clicked", G_CALLBACK(edit_entry), "(");
    gtk_grid_attach(GTK_GRID(grid), button, 3, 5, 1, 1);

    button=gtk_button_new_with_label("=");
    g_signal_connect(button, "clicked", G_CALLBACK(calculate), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 2, 5, 1, 1);

    button = gtk_button_new_with_label ("Clear");
    g_signal_connect_swapped( button, "clicked", G_CALLBACK(clear), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 5, 1, 1);

    button = gtk_button_new_with_label ("Quit");
    g_signal_connect_swapped( button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 5, 1, 1);

    gtk_widget_show_all (window);
}


int main (int argc, char **argv)
{
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

