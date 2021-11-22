#include <stdio.h>
#include "array.h"

#define size 1

int main (){

    int a[size];

    for(int i = 0; i < size;i++)
        a[i] = i;

    for(int i = 0; i < size;i++)
        printf("%d ", a[i]);
    printf("\n");
    printf("\n");

    reverse_arr(a, 0, 0);

    for(int i = 0; i < size;i++)
        printf("%d ", a[i]);
    printf("\n");
}