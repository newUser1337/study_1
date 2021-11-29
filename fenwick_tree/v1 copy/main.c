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
    int sum = fenw_get_sum_lr(fw, 0, 8);
    printf("sum : %d\n", sum);
    int elem = fenw_get_sum_element(fw, 8);
    printf("elem : %d\n", elem);

    return 0;
}

void print_arr(int *array, size_t size)
{
    printf("Printing initial array \n");
    for (size_t i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}