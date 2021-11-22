#include <stdio.h>
#include "array.h"

void print_int_arr(int *a, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void print_char_arr(char *a, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void reverse_arr(int *arr, int spos, int epos)
{
    while (spos < epos)
    {
        swap(arr+spos, arr+epos);
        spos++;
        epos--;
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_int_short(int *sp, int *ep)
{
    int *cp = sp;

    do
    {
        printf("%d ", *cp);
    } while(cp++ != ep);
    printf("\n");
}