#include "subset.h"
#include <stdio.h>
#include <stdlib.h>
#include "../util/array.h"

void printsubs(char *a, char *mask, int n)
{
    printf("subs ");
    for (int i = 0; i < n; i++)
    {
        if (mask[i])
            printf("%d ", a[i]);
    }
    printf("\n");
}

int main()
{
    int size = 3;
    int *data = (int *)malloc(sizeof(int) * size);
    char *bit_mask_gray = (char *)malloc(sizeof(char) * size);
    for (int i = 1; i <= size; i++)
    {
        data[i - 1] = i;
    }

    subset_generator subs;
    int opstat = 1;

    subs = init_subset_generator(size);

    while (opstat)
    {
        //print_char_arr(subs.subset_mask, subs.n);
        //get_gray_code( subs.subset_mask, bit_mask_gray, size);
        // get_gray_code( subs.subset_mask, bit_mask_gray, size);
        // printsubs(subs.subset_mask, data, size);
        // printsubs(data, subs.subset_mask, size);

        //print_char_arr(subs.subset_mask, subs.n);
        //print_char_arr(subs.subset_mask, subs.n);
        get_gray_code(subs.subset_mask, bit_mask_gray, size);
        print_char_arr(bit_mask_gray, subs.n);
        subset_next(&subs, &opstat);
        
    }
}