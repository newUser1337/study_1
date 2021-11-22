#ifndef __PERMUTATION_TRANS__
#define __PERMUTATION_TRANS__

typedef struct perm_generator_trans
{
    int n;         //размер вектора
    int count;     //порядковый номер перестановки
    int *perm_arr; //массив с перестановкой
    char *_dir;    //внутренняя структура
} perm_generator_trans;

perm_generator_trans init_perm_trans_generator(int);
char perm_trans_next(perm_generator_trans *);
void perm_trans_reset(perm_generator_trans *);
void destruct_perm_trans_generator(perm_generator_trans *);
#endif