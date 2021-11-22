#ifndef __MATRIX__
#define __MATRIX__

#define MATRIX_OPERATION_SUCCESS 0
#define MATRIX_INCOMPATIBLE_SIZE 1
#define MATRIX_INDEXES_OUT_OF_BOUND 2

typedef struct matrix
{
    unsigned int n;
    unsigned int m;
    double *data;
} matrix;

matrix *matrix_init(unsigned int, unsigned int);
void matrix_free(matrix **);

double matrix_det_perm(matrix *, unsigned int *);
double matrix_det_tri(matrix *, unsigned int *);

matrix *matrix_sum(matrix *, matrix *, unsigned int *);

matrix *matrix_multi(matrix *, matrix *, unsigned int *);
double _mul_elements(matrix *, matrix *, int, int, unsigned int *);

double matrix_get_element(matrix *, unsigned int, unsigned int, unsigned int *);
void matrix_set_element(matrix *, unsigned int, unsigned int, double, unsigned int *);
void matrix_print(matrix *);
void matrix_row_mul_elemetns(matrix *, unsigned int, double, unsigned int *);

double matrix_det_tri(matrix *, unsigned int *);
void bring_to_triangle(matrix *, unsigned int *);
void row_add(matrix *, int , int , double , unsigned int *);
void col_add(matrix *, int , int , double , unsigned int *);
double matrix_get_element_for_triangle(matrix *, unsigned int , unsigned int *);
void matrix_col_to_zero_down(matrix *, unsigned int, unsigned int, unsigned int *);
void matrix_to_triangle(matrix *, unsigned int *);
#endif