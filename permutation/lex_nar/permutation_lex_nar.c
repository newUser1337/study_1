#include "permutation_lex_nar.h"
#include <stdlib.h>
#include "../../util/array.h"

perm_generator_lex_nar init_perm_lex_nar_generator(int n)
{
    perm_generator_lex_nar pgln;
    pgln.n = n;                                     //Размер массива
    pgln.count = 0;                                 //счетчик
    pgln.perm_arr = (int *)malloc(sizeof(int) * n); //Перестановки
    for (int i = 0; i < n; i++)
    {
        pgln.perm_arr[i] = i;
    }

    return pgln;
}

void destruct_perm_lex_nar_generator(perm_generator_lex_nar *pgln)
{
    free(pgln->perm_arr);
    pgln = NULL;
}

char perm_lex_nar_next(perm_generator_lex_nar *pgln)
{
    if (pgln->count == 0)
        return ++pgln->count;

    int i, j, idi = -1, idj;

    for (i = 0; i < pgln->n - 1; i++)
        if (pgln->perm_arr[i] < pgln->perm_arr[i + 1])
            idi = i;

    if (idi == -1)
        return 0;

    for (j = idi + 1; j < pgln->n; j++)
        if (pgln->perm_arr[idi] < pgln->perm_arr[j])
            idj = j;

    swap(&pgln->perm_arr[idi], &pgln->perm_arr[idj]);
    reverse_arr(pgln->perm_arr, idi + 1, pgln->n - 1);
    pgln->count++;

    return 1;
}

void perm_lex_nar_reset(perm_generator_lex_nar *pgln)
{
    pgln->count = 0;
    for (int i = 0; i < pgln->n; i++)
    {
        pgln->perm_arr[i] = i;
    }
}