#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//https://en.wikipedia.org/wiki/C_dynamic_memory_allocation#Differences_between_malloc()_and_calloc()
//https://en.wikipedia.org/wiki/Dynamic_array#Bounded-size_dynamic_arrays_and_capacity
// data-pierwszy length-sizeof, capacity-pamiêæ
// data jest tablic¹ dynamiczn¹???
typedef struct wekto {
    char* data;
    unsigned int length;
    unsigned int capacity;
    char znak;
} vector;
void pushback(vector *wekt)
{
    if(wekt->length==0)
    {
        wekt->data=realloc(wekt->data, sizeof(char));
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
int main()
{
    int cap, len, n, i;
    char a;
    vector *wektor=initvect();
    scanf("%d", &n);
    for(i=0; i<n; i++)
    {
        scanf("%c", &a);
        if(a==' ' || a=='\n')
            scanf("%c", &a);
        wektor->znak=a;
        pushback(wektor);
        printf("%c ", wektor->data[i]);}
    printf("length:%d ", wektor->length);

   // printf("length:%d ", wektor->length);
}
