#include "matrix.h"
#include "../permutation/trans/permutation_trans.h"
#include "../util/array.h"

double matrix_det_tri(matrix *mat, unsigned int *opres)
{
    *opres = MATRIX_OPERATION_SUCCESS;

    if (mat->m != mat->n)
    {
        *opres = MATRIX_INCOMPATIBLE_SIZE;
        return 0;
    }

    bring_to_triangle(mat, opres);
    double det = 1;
    for (int i = 0; i < mat->n; i++)
    {
        det *= matrix_get_element(mat, i, i, opres);
    }
}

void bring_to_triangle(matrix *mat, unsigned int *opres)
{
    double ai, aj;

    for (int i = 0; i < mat->n; i++)
    {
        ai = matrix_get_element(mat, i, i, opres);
        for (int j = i + 1; j < mat->n; j++)
        {
            aj = matrix_get_element(mat, j, i, opres);
            row_add(mat, j, i, -1.0 * aj / ai, opres);
        }
    }
}

void row_add(matrix *mat, int rowi, int rowj, double mul, unsigned int *opres)
{
    for (int i = 0; i < mat->n; i++)
        matrix_set_element(mat, rowi, i, matrix_get_element(mat, rowi, i, opres) + mul * matrix_get_element(mat, rowj, i, opres), opres);
}

void col_add(matrix *mat, int coli, int colj, double mul, unsigned int *opres)
{
    for (int i = 0; i < mat->m; i++)
        matrix_set_element(mat, i, coli, matrix_get_element(mat, i, coli, opres) + mul * matrix_get_element(mat, i, colj, opres), opres);
}

void matrix_to_triangle(matrix *mat, unsigned int *opres)
{
    unsigned int min = (mat->m > mat->n) ? mat->n : mat->m;
    double aii;
    int i = 0;

    while (i != min)
    {
        aii = matrix_get_element_for_triangle(mat,i,opres);
        if(aii != 0)
            matrix_col_to_zero_down(mat, i, i, opres);
        i++;
    }
}