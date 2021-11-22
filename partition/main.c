#include <stdio.h>
#include "partition.h"
#include "../util/array.h"

#define N 7

int main()
{
    partition_generator pg = init_partition_generator(N);

    while (partition_next(&pg))
    {
        print_int_short(pg.sp, pg.ep);
    }
    printf("count %d \n", pg.count);
}

// void print_int_short(int *sp, int *ep)
// {
//     int *cp = sp;

//     do
//     {
//         printf("%d ", *cp);
//     } while(cp++ != ep);
//     printf("\n");
// }