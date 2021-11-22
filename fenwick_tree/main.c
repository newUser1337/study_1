#include <stdio.h>
#include <stdlib.h>
#include "fenw.h"

void print_arr(int *, size_t);

#define SIZE 8

int main()
{

    int array[SIZE];
    for (size_t i = 0; i < SIZE; i++)
        array[i] = i + 1;
    fenw *fw = fenw_init(array, SIZE);
    print_arr(array, SIZE);
    fenw_print(fw);
    
    fenw_destr(&fw);

    return 0;
}

void print_arr(int *array, size_t size)
{
    printf("Printing initial array \n");
    for (size_t i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}