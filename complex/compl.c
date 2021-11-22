#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "compl.h"

void compl_print(Compl *c)
{

    switch (c->type)
    {
    case ALG:
        printf("%f + %fi \n", c->val.alg.x, c->val.alg.y);
        break;
    case TRIG:
        printf("|%f|(cos(%f) + sin(%f)) \n", c->val.trig.r, c->val.trig.fi, c->val.trig.fi);
        break;
    case EXP:
        printf("|%f|e^i%f\n", c->val.exp.r, c->val.exp.fi);
        break;
    default:
        errno = ERANGE;
        perror("Wrong complex number type\n");
        exit(1);
        break;
    }
}