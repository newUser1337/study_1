#include <stdio.h>
#include "permutation_lex_rec.h"
#include "../../util/array.h"

void perm_callback(perm_generator_lex_rec *, void *);

int main()
{
    int supdata = 7;
    perm_generator_lex_rec pglr = init_perm_lex_rec_generator(4, &supdata, perm_callback);
    perm_lex_rec_run(&pglr);
    destruct_perm_lex_rec_generator(&pglr);

}

void perm_callback(perm_generator_lex_rec *pglr, void *supdata)
{
    printf("%-6d   supdata = %-6d --> ", pglr->count, *((int*)pglr->supdata));
    print_int_arr(pglr->perm_arr, pglr->n);
}