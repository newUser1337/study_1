#include <stdlib.h>
#include "matrix.h"
#include "../permutation/trans/permutation_trans.h"
#include "../util/array.h"

matrix *matrix_multi(matrix *mata, matrix *matb, unsigned int *opres)
{
    *opres = MATRIX_OPERATION_SUCCESS;

    if (mata->m != matb->n)
    {
        *opres = MATRIX_INCOMPATIBLE_SIZE;
        return NULL;
    }

    matrix *matr = matrix_init(mata->n, matb->m);
    for (int i = 0; i < mata->n; i++)
    {
        for (int j = 0; j < matb->m; j++)
        {
            //matrix_set_element(matr, i, j, 1.0, opres);
            matrix_set_element(matr, i, j, _mul_elements(mata, matb, i, j, opres), opres);
        }
    }

    return matr;
}

double _mul_elements(matrix *mata, matrix *matb, int row, int col, unsigned int *opres)
{
    double val = 0.0;
    for(int i = 0; i < mata->m; i++)
    {
        val = val + (matrix_get_element(mata, row, i, opres) * matrix_get_element(matb, i, col, opres));
    }

}