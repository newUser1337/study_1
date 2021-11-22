#include "subset_gray.h"
#include <stdlib.h>

void binary_add_one(int, char *);

subset_gray_generator init_subset_gray_generator(int size)
{
    subset_gray_generator subs;
    subs.n = size;
    subs.count = 0;
    subs.subset_mask = (char *)calloc(size + 1, sizeof(char));

    return subs;
}

unsigned char subset_gray_next(subset_gray_generator *subs, int *opstat)
{
    *opstat = 1;
    char finish = 1;

    for (int i = 0; i < subs->n; i++)
    {
        if (*(subs->subset_mask + i) == 0)
        {
            finish = 0;
        }
    }

    if (finish)
    {
        *opstat = 0;
        return subs->count;
    }

    binary_add_one(subs->n, subs->subset_mask);

    return ++subs->count;
}
void subset_gray_reset(subset_gray_generator *subs)
{
}
void destruct_subset_gray_generator(subset_gray_generator *subs)
{
}

void binary_add_one(int n, char *a)
{
    char *cp = a;
    char cf = 1;

    do
    {
        if (*cp + cf > 1)
        {
            *cp = 0;
        }
        else
        {
            *cp = 1;
            cf = 0;
        }
        cp++;
    } while (cf && cp != (a + n));
}