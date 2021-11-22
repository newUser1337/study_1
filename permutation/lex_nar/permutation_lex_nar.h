#ifndef __PERMUTATION_LEX_NAR__
#define __PERMUTATION_LEX_NAR__

typedef struct perm_generator_lex_nar
{
    int n;         //размер вектора
    int count;     //порядковый номер перестановки
    int *perm_arr; //массив с перестановкой
} perm_generator_lex_nar;

perm_generator_lex_nar init_perm_lex_nar_generator(int);
char perm_lex_nar_next(perm_generator_lex_nar *);
void perm_lex_nar_reset(perm_generator_lex_nar *);
void destruct_perm_lex_nar_generator(perm_generator_lex_nar *);
#endif