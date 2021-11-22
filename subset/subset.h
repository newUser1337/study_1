#ifndef __SUBSET__
#define __SUBSET__

typedef struct subset_generator
{
    int n;              //размер множества
    int count;          //порядковый номер подмножества
    char *subset_mask;  //массив bit mask
} subset_generator;

subset_generator init_subset_generator(int);
unsigned char subset_next(subset_generator *, int *);
void subset_reset(subset_generator *);
void destruct_subset_generator(subset_generator *);
void get_gray_code(char *, char *, int);
#endif