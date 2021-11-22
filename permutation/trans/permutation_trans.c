#include "permutation_trans.h"
#include <stdlib.h>
#include "../../util/array.h"

int direction(perm_generator_trans *, int);
void swapc(char *, char *);

perm_generator_trans init_perm_trans_generator(int n)
{
    perm_generator_trans pgt;
    pgt.n = n;                                     //Размер массива
    pgt.count = 0;                                 //счетчик
    pgt.perm_arr = (int *)malloc(sizeof(int) * n); //Перестановки
    pgt._dir = (char *)malloc(sizeof(char) * n);   //Вспомогательный массив
    for (int i = 0; i < n; i++)
    {
        pgt.perm_arr[i] = i;
        pgt._dir[i] = 1;
    }

    return pgt;
}

void destruct_perm_trans_generator(perm_generator_trans *pgt)
{
    free(pgt->perm_arr);
    free(pgt->_dir);
    pgt = NULL;
}

char perm_trans_next(perm_generator_trans *pgt)
{
    int i;
    int id;
    if(pgt->count == 0)
        return ++pgt->count;
    
    pgt->count++;
    id = -1;

    for (i = 0; i < pgt->n; i++)
        if ((direction(pgt, i)) && ((id == -1) || (pgt->perm_arr[i] > pgt->perm_arr[id])))
            id = i;

    if (id == -1)
        return 0;

    for (i = 0; i < pgt->n; i++)
        if (pgt->perm_arr[i] > pgt->perm_arr[id])
            pgt->_dir[i] = (pgt->_dir[i] == 1 ? 0 : 1);

    if (pgt->_dir[id])
    {
        swap(&pgt->perm_arr[id], &pgt->perm_arr[id - 1]);
        swapc(&pgt->_dir[id], &pgt->_dir[id - 1]);
    }
    else
    {
        swap(&pgt->perm_arr[id], &pgt->perm_arr[id + 1]);
        swapc(&pgt->_dir[id], &pgt->_dir[id + 1]);
    }

    return 1;
}

int direction(perm_generator_trans *pgt, int i)
{
    if (pgt->_dir[i])
    {
        if (!i)
            return 0;
        return ((pgt->perm_arr[i] > pgt->perm_arr[i - 1]) ? 1 : 0);
    }
    else
    {
        if (i == pgt->n - 1)
            return 0;
        return ((pgt->perm_arr[i] > pgt->perm_arr[i + 1]) ? 1 : 0);
    }
}

void swapc(char *a1, char *a2)
{
    char temp;

    temp = *a1;
    *a1 = *a2;
    *a2 = temp;
}

void perm_trans_reset(perm_generator_trans *pgt)
{
    pgt->count = 0;
    for (int i = 0; i < pgt->n; i++)
    {
        pgt->perm_arr[i] = i;
        pgt->_dir[i] = 1;
    }
}