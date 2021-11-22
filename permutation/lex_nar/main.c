#include <stdio.h>
#include "permutation_lex_nar.h"
#include "../../util/array.h"

int main()
{
    perm_generator_lex_nar pgnl = init_perm_lex_nar_generator(5);
    

    while(perm_lex_nar_next(&pgnl)){
        printf("count --> %-5d    ", pgnl.count);
        print_int_arr(pgnl.perm_arr, pgnl.n);
    }
    
    // printf("Reset\n");
    // perm_lex_nar_reset(&pgnl);
    
    // while(perm_lex_nar_next(&pgnl)){
    //     printf("count --> %-5d    ", pgnl.count);
    //     print_int_arr(pgnl.perm_arr, pgnl.n);
    // }
    destruct_perm_lex_nar_generator(&pgnl);
}