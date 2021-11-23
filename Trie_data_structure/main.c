#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trie.h"

int main()
{
    Trie *tr = trie_init();
    char *ward = "ward";
    trie_add_word(tr, ward);
    char *second = "second";
    trie_add_word(tr, second);
    char *warmap = "warmap";
    trie_add_word(tr, warmap);
    char *warhammer = "warhammer";
    trie_add_word(tr, warhammer);
    char *z_prog = "z_prog";
    trie_add_word(tr, z_prog);
    // trie_print(tr);

    char *war = "wa";
    List *result = list_init();
    trie_search(tr, war, result);
    // list_print_word(result);


    List_node *list_node = result->first;
    while (list_node != NULL)
    {
        free(list_node->word);
        list_node = list_node->next;
    }

    trie_destr(&tr);
    list_destr(&result);

    return 0;
}