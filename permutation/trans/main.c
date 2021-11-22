#include <stdio.h>
#include "permutation_trans.h"
#include "../../util/array.h"

int main()
{
    perm_generator_trans pgt = init_perm_trans_generator(4);

    while(perm_trans_next(&pgt)){
        printf("count --> %-5d    ", pgt.count);
        print_int_arr(pgt.perm_arr, pgt.n);
    }
    
    printf("Reset\n");
    perm_trans_reset(&pgt);
    
    while(perm_trans_next(&pgt)){
        printf("count --> %-5d    ", pgt.count);
        print_int_arr(pgt.perm_arr, pgt.n);
    }
    destruct_perm_trans_generator(&pgt);
}