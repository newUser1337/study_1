#include "permutation_lex_rec.h"
#include <stdlib.h>

void perm_rec(perm_generator_lex_rec *, int);

perm_generator_lex_rec init_perm_lex_rec_generator(int n, void *supdata, void (*func)(perm_generator_lex_rec *, void *))
{
    perm_generator_lex_rec pg;
    pg.n = n;                                        //Размер массива
    pg.callback = func;                              //Обратный вызов
    pg.count = 0;                                    //счетчик
    pg.supdata = supdata;                            //Внешние данные
    pg.perm_arr = (int *)malloc(sizeof(int) * n);    //Перестановки
    pg._used_arr = (char *)malloc(sizeof(char) * n); //Вспомогательный массив

    return pg;
}

void destruct_perm_lex_rec_generator(perm_generator_lex_rec *pg)
{
    free(pg->perm_arr);
    free(pg->_used_arr);
    pg = NULL;
}

void perm_lex_rec_run(perm_generator_lex_rec *pg)
{
    perm_rec(pg, 0);
}

void perm_rec(perm_generator_lex_rec *pg, int index)
{
    if (index == pg->n)
    {
        pg->count++;
        pg->callback(pg, pg->supdata);
        return;
    }
    for (int i = 0; i < pg->n; i++)
    {
        if (pg->_used_arr[i])
            continue;
        pg->perm_arr[index] = i;
        pg->_used_arr[i] = 1;
        perm_rec(pg, index + 1);
        pg->_used_arr[i] = 0;
    }
}