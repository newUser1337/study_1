#include <stdio.h>
#include <stdlib.h>
#include "fenw.h"

void print_arr(int *, size_t);

#define SIZE 9

int main()
{

    int array[SIZE];
    for (size_t i = 0; i < SIZE; i++)
        array[i] = i + 1;
    fenw *fw = fenw_init(array, SIZE);
    print_arr(array, SIZE);
    fenw_print(fw);
    // fenw_add(fw, 1, 2);
    fenw_print(fw);

    printf("new\n\n");
    array[1] += 2;
    print_arr(array, SIZE);
    fenw *gw = fenw_init(array, SIZE);
    fenw_print(gw);

    int result = fenw_get_sum(fw, 3, 5);
    printf("summ\n");
    printf("%d \n", result);

    fenw_destr(&fw);
    fenw_destr(&gw);

    return 0;
}

void print_arr(int *array, size_t size)
{
    printf("Printing initial array \n");
    for (size_t i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}