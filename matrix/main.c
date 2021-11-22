#include <stdio.h>
#include "matrix.h"

matrix *build();

int main()
{
    // matrix* mata = matrix_init(5,5);
    // int opres;

    // matrix_set_element(mata, 0, 0, 1, &opres);
    // matrix_set_element(mata, 0, 1, 2, &opres);
    // matrix_set_element(mata, 0, 2, 3, &opres);
    // matrix_set_element(mata, 0, 3, 4, &opres);
    // matrix_set_element(mata, 0, 4, 6, &opres);

    // matrix_set_element(mata, 1, 0, 4, &opres);
    // matrix_set_element(mata, 1, 1, 5, &opres);
    // matrix_set_element(mata, 1, 2, 6, &opres);
    // matrix_set_element(mata, 1, 3, 13, &opres);
    // matrix_set_element(mata, 1, 4, 19, &opres);

    // matrix_set_element(mata, 2, 0, 7, &opres);
    // matrix_set_element(mata, 2, 1, 8, &opres);
    // matrix_set_element(mata, 2, 2, 7, &opres);
    // matrix_set_element(mata, 2, 3, 21, &opres);
    // matrix_set_element(mata, 2, 4, 23, &opres);

    // matrix_set_element(mata, 3, 0, 7, &opres);
    // matrix_set_element(mata, 3, 1, 8, &opres);
    // matrix_set_element(mata, 3, 2, 7, &opres);
    // matrix_set_element(mata, 3, 3, 1, &opres);
    // matrix_set_element(mata, 3, 4, 2, &opres);

    // matrix_set_element(mata, 4, 0, 11, &opres);
    // matrix_set_element(mata, 4, 1, 23, &opres);
    // matrix_set_element(mata, 4, 2, 5, &opres);
    // matrix_set_element(mata, 4, 3, 1, &opres);
    // matrix_set_element(mata, 4, 4, 2, &opres);

    // matrix* matb = matrix_init(1,1);
    // matrix_set_element(matb, 0, 0, 11, &opres);

    // matrix* matc = matrix_init(2,2);
    // matrix_set_element(matc, 0, 0, 6, &opres);
    // matrix_set_element(matc, 0, 1, 5, &opres);
    // matrix_set_element(matc, 1, 0, 1, &opres);
    // matrix_set_element(matc, 1, 1, 2, &opres);

    // matrix_print(mata);
    // matrix_print(matb);
    // matrix_print(matc);
    // printf("\n");

    // double det1 = matrix_det_perm(mata, &opres);
    // double det2 = matrix_det_perm(matb, &opres);
    // double det3 = matrix_det_perm(matc, &opres);

    // printf("matrix det %g\n", det1);
    // printf("matrix det %g\n", det2);
    // printf("matrix det %g\n", det3);

    // det1 = matrix_det_tri(mata, &opres);
    // matrix_print(mata);
    // printf("matrix det %g\n", det1);

    // matrix_free(&mata);
    // matrix_free(&matb);
    // matrix_free(&matc);

    // matrix* mat1 = matrix_init(3,4);
    // matrix* mat2 = matrix_init(4,5);

    // matrix_set_element(mat1, 0, 0, 4, &opres);
    // matrix_set_element(mat1, 0, 1, 5, &opres);
    // matrix_set_element(mat1, 0, 2, 2, &opres);
    // matrix_set_element(mat1, 0, 3, 9, &opres);

    // matrix_set_element(mat1, 1, 0, 4, &opres);
    // matrix_set_element(mat1, 1, 1, 2, &opres);
    // matrix_set_element(mat1, 1, 2, 1, &opres);
    // matrix_set_element(mat1, 1, 3, 6, &opres);

    // matrix_set_element(mat1, 2, 0, 4, &opres);
    // matrix_set_element(mat1, 2, 1, 8, &opres);
    // matrix_set_element(mat1, 2, 2, 5, &opres);
    // matrix_set_element(mat1, 2, 3, 2, &opres);

    // matrix_set_element(mat2, 0, 0, 11, &opres);
    // matrix_set_element(mat2, 0, 1, 2, &opres);
    // matrix_set_element(mat2, 0, 2, 0, &opres);
    // matrix_set_element(mat2, 0, 3, 7, &opres);
    // matrix_set_element(mat2, 0, 4, 7, &opres);

    // matrix_set_element(mat2, 1, 0, 5, &opres);
    // matrix_set_element(mat2, 1, 1, 2, &opres);
    // matrix_set_element(mat2, 1, 2, 8, &opres);
    // matrix_set_element(mat2, 1, 3, 5, &opres);
    // matrix_set_element(mat2, 1, 4, 1, &opres);

    // matrix_set_element(mat2, 2, 0, 4, &opres);
    // matrix_set_element(mat2, 2, 1, 5, &opres);
    // matrix_set_element(mat2, 2, 2, 6, &opres);
    // matrix_set_element(mat2, 2, 3, 2, &opres);
    // matrix_set_element(mat2, 2, 4, 9, &opres);

    // matrix_set_element(mat2, 3, 0, 0, &opres);
    // matrix_set_element(mat2, 3, 1, 1, &opres);
    // matrix_set_element(mat2, 3, 2, 2, &opres);
    // matrix_set_element(mat2, 3, 3, 7, &opres);
    // matrix_set_element(mat2, 3, 4, 8, &opres);

    // matrix_print(mat1);
    // printf("\n");
    // matrix_print(mat2);

    // matrix *mat3 = matrix_multi(mat1, mat2, &opres);
    // printf("\n");
    // printf("\n");
    // matrix_print(mat3);
    // printf("\n");
    // matrix_row_mul_elemetns(mat3, 0, 1.0/77.0, &opres);
    // matrix_print(mat3);

    matrix *mata = build();
    int opres;

    // matrix_print(mata);
    // printf("\n");
    // matrix_get_element_for_triangle(mata, 0, &opres);
    matrix_print(mata);
    printf("\n");
    
    matrix_to_triangle(mata, &opres);
    matrix_print(mata);

}

matrix *build()
{
    matrix *mata = matrix_init(2, 4);
    int opres;

    matrix_set_element(mata, 0, 0, 0, &opres);
    matrix_set_element(mata, 0, 1, 4, &opres);
    matrix_set_element(mata, 0, 2, 2, &opres);
    matrix_set_element(mata, 0, 3, 14, &opres);
    //matrix_set_element(mata, 0, 4, 15, &opres);

    matrix_set_element(mata, 1, 0, 0, &opres);
    matrix_set_element(mata, 1, 1, 5, &opres);
    matrix_set_element(mata, 1, 2, 6, &opres);
    matrix_set_element(mata, 1, 3, 13, &opres);
    //matrix_set_element(mata, 1, 4, 19, &opres);

//     matrix_set_element(mata, 2, 0, 1, &opres);
//     matrix_set_element(mata, 2, 1, 8, &opres);
//     matrix_set_element(mata, 2, 2, 6, &opres);
//     matrix_set_element(mata, 2, 3, 21, &opres);
//     //matrix_set_element(mata, 2, 4, 23, &opres);

//     matrix_set_element(mata, 3, 0, 4, &opres);
//     matrix_set_element(mata, 3, 1, 8, &opres);
//     matrix_set_element(mata, 3, 2, 6, &opres);
//     matrix_set_element(mata, 3, 3, 1, &opres);
//    // matrix_set_element(mata, 3, 4, 2, &opres);

//     matrix_set_element(mata, 4, 0, 3, &opres);
//     matrix_set_element(mata, 4, 1, 23, &opres);
//     matrix_set_element(mata, 4, 2, 6, &opres);
//     matrix_set_element(mata, 4, 3, 1, &opres);
    //matrix_set_element(mata, 4, 4, 2, &opres);

    return mata;
}