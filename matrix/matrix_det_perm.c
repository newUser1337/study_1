#include "matrix.h"
#include "../permutation/trans/permutation_trans.h"
#include "../util/array.h"

double matrix_det_perm(matrix *mat, unsigned int *opres)
{
    *opres = MATRIX_OPERATION_SUCCESS;

    if (mat->m != mat->n)
    {
        *opres = MATRIX_INCOMPATIBLE_SIZE;
        return 0;
    }

    perm_generator_trans pg = init_perm_trans_generator(mat->m);
    
    
    double res = 0;
    double sum_term;

    while (perm_trans_next(&pg))
    {
        sum_term = ((pg.count - 1) % 2) ? -1 : 1;

        int opres;
        for (int i = 0; i < pg.n; i++)
        {
            sum_term = sum_term * matrix_get_element(mat, pg.perm_arr[i], i, &opres);
        }
        res = res + sum_term;
//        printf("%-6d sumterm = %-6g  -> ", pg.count, sum_term);
//        print_int_arr(pg.perm_arr, pg.n);
    
    }
    
    destruct_perm_trans_generator(&pg);
    return res;
}
