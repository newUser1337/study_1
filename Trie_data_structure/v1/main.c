#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trie.h"

void print_ch(void *);
int cmp_ch(void *, void *);

int main()
{
    Trie *tr = trie_init();
    trie_add_word(tr, "newword");
    trie_add_word(tr, "ward");
    trie_add_word(tr, "warhammer");
    trie_add_word(tr, "warmap");
    trie_add_word(tr, "warma");
    trie_add_word(tr, "z_prog");
    trie_print(tr);

    List *result = list_init(cmp_ch, print_ch);
    trie_search(tr, "w", result);
    list_print(result);

    list_destr(&result);
    trie_destr(&tr);
    return 0;
}

void print_ch(void *data)
{
    printf("%s", (char *)data);
}
int cmp_ch(void *data_1, void *data_2)
{
    return strcmp((char *)data_1, (char *)data_2);
}