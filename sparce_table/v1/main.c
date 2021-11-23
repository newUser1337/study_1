#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sparce.h"

#define SIZE 17

int get_pow_2(int);
int get_pow_2_gcc(int);
int min(int, int);
void get_ST(int *, int **, int, int);
int set_elemet(int *, int **, int, int);
void print_arr(int **, int, int);
int rmq(int **, int, int);

int main()
{
    int array[SIZE] = {2, 6, -3, 5, -7, 2, -8, 3, -5, -2, 11, -20, 4, -4, -6, -4, -21};
    sparce *sp = sparce_init(array, SIZE);
    sparce_print(sp);

    int r = 16;
    int l = 1;
    int res = sparce_rmq(sp, r, l);

    printf("res  %d\n", res);

    return 0;
}
