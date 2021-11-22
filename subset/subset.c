#include "subset.h"
#include <stdlib.h>

void binary_add_one(int, char *);

subset_generator init_subset_generator(int size)
{
    subset_generator subs;
    subs.n = size;
    subs.count = 0;
    subs.subset_mask = (char *)calloc(size + 1, sizeof(char));

    return subs;
}

unsigned char subset_next(subset_generator *subs, int *opstat)
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

    // if(subs->count == 0)
    //     return ++subs->count;

    binary_add_one(subs->n, subs->subset_mask);

    return ++subs->count;
}
void subset_reset(subset_generator *subs)
{
}
void destruct_subset_generator(subset_generator *subs)
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

void get_gray_code(char *subset_mask, char *gray, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        gray[i] = subset_mask[i] ^ subset_mask[i + 1];

    }
    gray[n - 1] = subset_mask[n - 1];

}