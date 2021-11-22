#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include "../permutation/trans/permutation_trans.h"
#include "../util/array.h"

matrix *matrix_init(unsigned int n, unsigned int m)
{
    matrix *mat = (matrix *)malloc(sizeof(matrix));

    mat->n = n;
    mat->m = m;
    mat->data = (double *)malloc(sizeof(double) * n * m);

    return mat;
}

void matrix_free(matrix **mat)
{
    free((*mat)->data);
    free(*mat);
    mat = NULL;
}

double matrix_get_element(matrix *mat, unsigned int i, unsigned int j, unsigned int *opres)
{
    *opres = MATRIX_OPERATION_SUCCESS;

    if (i > mat->m || j > mat->n)
        *opres = MATRIX_INDEXES_OUT_OF_BOUND;

    return *(mat->data + i * mat->m + j);
}

void matrix_set_element(matrix *mat, unsigned int i, unsigned int j, double d, unsigned int *opres)
{
    *opres = MATRIX_OPERATION_SUCCESS;

    if (i > mat->m || j > mat->n)
        *opres = MATRIX_INDEXES_OUT_OF_BOUND;

    *(mat->data + i * mat->m + j) = d;
}

matrix *matrix_sum(matrix *mat1, matrix *mat2, unsigned int *opres)
{
    *opres = MATRIX_OPERATION_SUCCESS;

    if (mat1->n != mat2->n || mat1->m != mat2->m)
    {
        *opres = MATRIX_INCOMPATIBLE_SIZE;
        return NULL;
    }

    matrix *matr = matrix_init(mat1->n, mat1->m);
    for (int i = 0; i < mat1->n; i++)
    {
        for (int j = 0; j < mat1->m; j++)
        {
            double sum = matrix_get_element(mat1, i, j, opres) + matrix_get_element(mat2, i, j, opres);
            matrix_set_element(matr, i, j, sum, opres);
        }
    }

    return matr;
}

void matrix_print(matrix *mat)
{
    int opres;
    for (int i = 0; i < mat->n; i++)
    {
        for (int j = 0; j < mat->m; j++)
        {
            printf("%-6g ", matrix_get_element(mat, i, j, &opres));
        }
        printf("\n");
    }
}

void matrix_row_mul_elemetns(matrix *mat, unsigned int row, double mul, unsigned int *opres)
{

    for (int i = 0; i < mat->m; i++)
        matrix_set_element(mat, row, i, mul * matrix_get_element(mat, row, i, opres), opres);
}

double matrix_get_element_for_triangle(matrix *mat, unsigned int row, unsigned int *opres)
{
    double aii = matrix_get_element(mat, row, row, opres);
    double aij;

    if (aii != 0)
        return aii;

    for (int i = row + 1; i < mat->n; i++)
    {
        if ((matrix_get_element(mat, i, row, opres)) != 0)
        {
            row_add(mat, row, i, 1.0, opres);
            return matrix_get_element(mat, row, row, opres);
        }
    }

    // for (int i = row + 1; i < mat->m; i++)
    // {
    //     if ((matrix_get_element(mat, row, i, opres)) != 0)
    //     {
    //         col_add(mat, row, i, 1.0, opres);
    //         return matrix_get_element(mat, row, row, opres);
    //     }
    // }

    return 0.0;
}

void matrix_col_to_zero_down(matrix *mat, unsigned int row, unsigned int col, unsigned int *opres)
{
    double aii = matrix_get_element(mat, row, col, opres);
    if (aii == 0)
        return;

    for (int i = row + 1; i < mat->n; i++)
    {
        row_add(mat, i, row, -1.0 * matrix_get_element(mat, i, col, opres) / aii , opres);
    }
}