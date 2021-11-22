#include "compl.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    printf("size %zu \n", sizeof(Compl));

    Compl x;
    x.type = ALG;
    x.val.alg.x = 3;
    x.val.alg.y = 4;
    compl_print(&x);

    Compl y;
    y.type = TRIG;
    y.val.trig.r = 2;
    y.val.trig.fi = 45;
    compl_print(&y);

    Compl z;
    z.type = EXP;
    z.val.exp.r = 5;
    z.val.exp.fi = 6;
    compl_print(&z);

    return 0;
}