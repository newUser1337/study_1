#include "bigint.h"
#include <stdio.h>
#include <time.h>

void fact(unsigned int, bigint *res);

int main()
{
    /*bigint a = bigint_init_val(30, 0, 123456789);
    bigint_print(&a);
    bigint_free(&a);*/

    // bigint a = bigint_init(300, 0);
    // bigint b = bigint_init(300, 0);
    // bigint c = bigint_init(60002, 0);

    // for (int i = 0; i < 300; i++)
    // {
    //     bigint_setdigit(&a, i, 5);
    //     bigint_setdigit(&b, i, 4);
    // }

    // bigint_mult(&a, &b, &c);

    // bigint_print(&a);
    // bigint_print(&b);
    // bigint_print(&c);

    // bigint_free(&a);
    // bigint_free(&b);
    // bigint_free(&c);
    
    clock_t start = clock();

    bigint res = bigint_init(100000, 0);
    fact(6, &res);
    bigint_print(&res);

    clock_t end = clock();

    printf("time %g\n", (double)(end-start)*1000/CLOCKS_PER_SEC);

    // bigint d = bigint_init(30, 0);
    // bigint c = bigint_init(30, 0);
    //bigint m = bigint_init(0, 0);

    // bigint_setdigit(&d, 0, 5);
    // bigint_setdigit(&d, 1, 4);
    // bigint_setdigit(&d, 2, 3);
    // bigint_setdigit(&d, 3, 2);
    // bigint_setdigit(&d, 4, 1);

    // bigint_setdigit(&c, 0, 3);
    // bigint_setdigit(&c, 1, 2);
    // bigint_setdigit(&c, 2, 1);
    // bigint_setdigit(&c, 3, 1);
    // bigint_setdigit(&c, 4, 1);
    // bigint_setdigit(&c, 5, 1);
    // bigint_setdigit(&c, 6, 1);
    // bigint_setdigit(&c, 7, 1);
    // bigint_setdigit(&c, 8, 2);

    // bigint_mult(&d, &c, &m);

    // c.size=15;
    // c.sign=1;
    //bigint_setdigit(&d, 1, 2);
    //bigint_setdigit(&d, 2, 2);
    // __mult_digit(&d, &c, 3);

    // bigint_print(&d);
    // bigint_print(&c);
    //     bigint_print(&m);
    // bigint_free(&d);
    // bigint_free(&c);
    // bigint_free(&m);
}
