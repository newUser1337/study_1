#ifndef __SUBSET_GRAY__
#define __SUBSET_GGRAY__

typedef struct subset_gray_generator
{
    int n;              //размер множества
    int count;          //порядковый номер подмножества
    char *subset_mask;  //массив bit mask
    int *subset;        //массив с подмножествами
} subset_gray_generator;

subset_gray_generator init_subset_gray_generator(int);
unsigned char subset_gray_next(subset_gray_generator *, int *);
void subset_gray_reset(subset_gray_generator *);
void destruct_subset_gray_generator(subset_gray_generator *);
void get_gray_code(int *, int*, int); 
#endif