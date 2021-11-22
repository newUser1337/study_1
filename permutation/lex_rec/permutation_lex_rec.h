#ifndef __PERMUTATION_LEX_REC__
#define __PERMUTATION_LEX_REC__

typedef struct perm_generator_lex_rec
{
    int n;            //размер вектора
    int count;        //порядковый номер перестановки
    int *perm_arr;    //массив с перестановкой
    char *_used_arr;  //внутренняя структура
    void *supdata;    // внешние данные
    void (*callback)(struct perm_generator_lex_rec *, void *); //функция обратного вызова
} perm_generator_lex_rec;

perm_generator_lex_rec init_perm_lex_rec_generator(int, void*, void (*)(perm_generator_lex_rec *, void *));
void perm_lex_rec_run(perm_generator_lex_rec *);
void destruct_perm_lex_rec_generator(perm_generator_lex_rec *);

#endif