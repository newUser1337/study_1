#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"
#include "list.h"

void print_symbol(void *);
int cmp_symbol(void *, void *);
node_list *_trie_create_n_list(char);
Trie_node *_get_tr_node_by_key(List *, char, Trie_node *);
List *_trie_get_list_symbol(Trie_node *);
Trie_node *_trie_create_node();
void _trie_print_words(Trie_node *);
void _print_word(Trie_node *);
void _trie_destr_node(Trie_node *);
void _trie_search(Trie_node *, char *, size_t, size_t, size_t, List *);
void _trie_get_words(Trie_node *, size_t, List *);
int _trie_get_word(Trie_node *, List *, char *);

Trie *trie_init()
{
    Trie *tr = (Trie *)malloc(sizeof(Trie));
    tr->root = _trie_create_node();

    return tr;
}

Trie_node *_trie_create_node()
{
    Trie_node *tr_node = (Trie_node *)malloc(sizeof(Trie_node));
    tr_node->keys = NULL;
    tr_node->parent = NULL;
    tr_node->isFinish = 0;

    return tr_node;
}

void trie_add_word(Trie *tr, char *word)
{
    Trie_node *tr_node;
    size_t len;

    tr_node = tr->root;
    len = strlen(word);

    for (size_t i = 0; i < len; i++)
        tr_node = _get_tr_node_by_key(_trie_get_list_symbol(tr_node), word[i], tr_node);
    tr_node->isFinish = 1;
}

List *_trie_get_list_symbol(Trie_node *tr_node)
{
    if (tr_node->keys == NULL)
        tr_node->keys = list_init(cmp_symbol, print_symbol);

    return tr_node->keys;
}

Trie_node *_get_tr_node_by_key(List *list, char symbol, Trie_node *parent_tr_node)
{
    Trie_node *r_tr_node;
    node_list n_list;
    n_list.symbol = symbol;

    LNode *lnode = list_search(list, &n_list);
    if (lnode == NULL)
    {
        node_list *new_n_list = _trie_create_n_list(symbol);
        new_n_list->tr_next = _trie_create_node();
        new_n_list->tr_next->parent = parent_tr_node;
        lnode = list_insert(list, new_n_list);
    }
    r_tr_node = ((node_list *)lnode->data)->tr_next;

    return r_tr_node;
}

node_list *_trie_create_n_list(char symbol)
{
    node_list *n_list = (node_list *)malloc(sizeof(node_list));
    n_list->symbol = symbol;
    n_list->tr_next = NULL;

    return n_list;
}

void trie_print(Trie *tr)
{
    if (tr->root->keys == NULL || tr->root->keys->first == NULL)
        printf("Trie is empty\n");
    else
        _trie_print_words(tr->root);
}

void _trie_print_words(Trie_node *tr_node)
{
    if (tr_node->isFinish)
    {
        _print_word(tr_node);
        printf("\n");
    }
    if(tr_node->keys == NULL)
        return;
    LNode *lnode = tr_node->keys->first;
    while (lnode != NULL)
    {
        _trie_print_words(((node_list *)lnode->data)->tr_next);
        lnode = lnode->next;
    }
}

void _print_word(Trie_node *tr_node)
{
    if (tr_node->parent != NULL)
    {
        _print_word(tr_node->parent);
        LNode *lnode = tr_node->parent->keys->first;
        while (((node_list *)lnode->data)->tr_next != tr_node)
            lnode = lnode->next;
        printf("%c", ((node_list *)lnode->data)->symbol);
    }
}


void trie_search(Trie *tr, char *str, List *result)
{
    size_t len = strlen(str);
    _trie_search(tr->root, str, 0, len, 0, result);
}

void _trie_search(Trie_node *tr_node, char *str, size_t cur_pos, size_t len, size_t dep, List *result)
{
    if (tr_node->isFinish)
        return;

    size_t next_pos;
    LNode *l_node = tr_node->keys->first;
    while (l_node != NULL)
    {
        if (str[cur_pos] == ((node_list *)l_node->data)->symbol)
            next_pos = cur_pos + 1;
        else
            next_pos = 0;

        if (next_pos == len)
        {
            _trie_get_words(((node_list *)l_node->data)->tr_next, dep, result);
            next_pos = 0;
        }

        _trie_search(((node_list *)l_node->data)->tr_next, str, next_pos, len, dep + 1, result);

        l_node = l_node->next;
    }
}

void _trie_get_words(Trie_node *tr_node, size_t dep, List *result)
{
    if (tr_node->isFinish)
    {
        char *word = (char *)malloc(sizeof(char) * dep);
        int z = _trie_get_word(tr_node, result, word);
        word[z] = '\n';
        list_insert(result, word);
        return;
    }

    LNode *l_node = tr_node->keys->first;
    while (l_node != NULL)
    {
        _trie_get_words(((node_list *)l_node->data)->tr_next, dep + 1, result);
        l_node = l_node->next;
    }
}

int _trie_get_word(Trie_node *tr_node, List *result, char *word)
{
    int pos = 0;
    if (tr_node->parent != NULL)
    {
        pos = _trie_get_word(tr_node->parent, result, word);
        LNode *l_node = tr_node->parent->keys->first;
        while (((node_list *)l_node->data)->tr_next != tr_node)
            l_node = l_node->next;

        word[pos++] = ((node_list *)l_node->data)->symbol;
    }
    return pos;
}

void trie_destr(Trie **tr)
{
    _trie_destr_node((*tr)->root);
    free(*tr);
    *tr = NULL;
}

void _trie_destr_node(Trie_node *tr_next)
{
    if (!tr_next->isFinish)
    {
        LNode *l_node = tr_next->keys->first;
        while (l_node != NULL)
        {
            _trie_destr_node(((node_list *)l_node->data)->tr_next);
            free(l_node->data);
            l_node = l_node->next;
        }
        list_destr(&tr_next->keys);
    }
    free(tr_next);
}

void print_symbol(void *data)
{
    printf("%c", ((node_list *)data)->symbol);
}
int cmp_symbol(void *data_1, void *data_2)
{
    int result;
    if (((node_list *)data_1)->symbol < ((node_list *)data_2)->symbol)
        result = -1;
    else if (((node_list *)data_1)->symbol > ((node_list *)data_2)->symbol)
        result = 1;
    else
        result = 0;

    return result;
}