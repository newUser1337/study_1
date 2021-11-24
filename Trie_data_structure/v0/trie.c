#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"

List_node *_list_create_node(char);
List_node *_list_create_node_word(char *);
void _list_destr_node(List_node **);
List_node *_list_search_index(List *, char);

List *list_init()
{
    List *list = (List *)malloc(sizeof(List));
    printf("malloc list\n");
    list->first = NULL;

    return list;
}

List_node *list_search(List *list, char symbol)
{
    List_node *list_node = list->first;
    while (list_node != NULL && symbol != list_node->symbol)
        list_node = list_node->next;

    return list_node;
}

List_node *list_insert(List *list, char symbol)
{
    List_node *list_node = list_search(list, symbol), *list_index_node;
    if (list_node == NULL)
    {
        list_node = _list_create_node(symbol);
        list_index_node = _list_search_index(list, symbol);
        if (list_index_node != NULL)
        {
            list_node->next = list_index_node->next;
            list_index_node->next = list_node;
        }
        else
        {
            list_node->next = list->first;
            list->first = list_node;
        }
    }

    return list_node;
}

List_node *list_add(List *list, char *word)
{
    List_node *list_node = _list_create_node_word(word);
    List_node *cur_node = list->first;
    if (cur_node == NULL)
    {
        list->first = list_node;
    }
    else
    {
        while (cur_node->next != NULL)
            cur_node = cur_node->next;

        cur_node->next = list_node;
    }

    return list_node;
}

List_node *_list_search_index(List *list, char symbol)
{
    List_node *list_node = list->first;

    if (list_node != NULL && symbol > list_node->symbol)
    {
        List_node *list_node_next = list_node->next;
        while (list_node_next != NULL && symbol > list_node_next->symbol)
        {
            list_node = list_node_next;
            list_node_next = list_node_next->next;
        }
    }
    else
        list_node = NULL;

    return list_node;
}

List_node *_list_create_node(char symbol)
{
    List_node *list_node = (List_node *)malloc(sizeof(List_node));
    printf("malloc node\n");
    list_node->symbol = symbol;

    return list_node;
}

List_node *_list_create_node_word(char *word)
{
    List_node *list_node = (List_node *)malloc(sizeof(List_node));
    printf("malloc node\n");
    list_node->word = word;

    return list_node;
}

void list_destr(List **list)
{
    List_node *list_node = (*list)->first, *list_temp_node;
    while (list_node != NULL)
    {
        list_temp_node = list_node->next;
        _list_destr_node(&list_node);
        list_node = list_temp_node;
    }
    printf("free list \n");
    free(*list);
    *list = NULL;
}

void _list_destr_node(List_node **list_node)
{
    printf("free list node \n");
    free(*list_node);
    *list_node = NULL;
}

void list_node_delete(List *list, char symbol)
{
    List_node *list_node = list_search(list, symbol);
    if (list_node != NULL)
    {
        List_node *list_index_node = _list_search_index(list, symbol);
        if (list_index_node != NULL)
            list_index_node->next = list_node->next;
        else
            list->first = list_node->next;
        _list_destr_node(&list_node);
    }
}

void list_print(List *list)
{
    List_node *list_node = list->first;
    printf("printing_list\n");
    while (list_node != NULL)
    {
        printf("%c", list_node->symbol);
        list_node = list_node->next;
    }
    printf("\n");
}

void list_print_word(List *list)
{
    List_node *list_node = list->first;
    printf("printing_list\n");
    while (list_node != NULL)
    {
        printf("%s", list_node->word);
        list_node = list_node->next;
    }
    printf("\n");
}

Trie_node *_trie_create_node();
List *_trie_get_list();
Trie_node *_get_tr_node_by_key(List *, char, Trie_node *);
void _trie_print_words(List *);
void _print_word(Trie_node *);
void _trie_search(List *, char *, size_t, size_t, size_t, List *);
int _trie_get_word(Trie_node *, List *, char *);
void _trie_get_words(List *, size_t, List *);

Trie *trie_init()
{
    Trie *tr = (Trie *)malloc(sizeof(Trie));
    printf("malloc Trie\n");
    tr->root = _trie_create_node();

    return tr;
}

void trie_add_word(Trie *tr, char *word)
{
    Trie_node *tr_node;
    size_t len;

    tr_node = tr->root;
    len = strlen(word);

    for (size_t i = 0; i < len; i++)
        tr_node = _get_tr_node_by_key(_trie_get_list(tr_node), word[i], tr_node);
    tr_node->isFinish = 1;
}

Trie_node *_trie_create_node()
{
    Trie_node *tr_node = (Trie_node *)malloc(sizeof(Trie_node));
    printf("malloc node tr\n");
    tr_node->keys = NULL;
    tr_node->parent = NULL;
    tr_node->isFinish = 0;

    return tr_node;
}

List *_trie_get_list(Trie_node *tr_node)
{
    if (tr_node->keys == NULL)
        tr_node->keys = list_init();

    return tr_node->keys;
}

Trie_node *_get_tr_node_by_key(List *list, char symbol, Trie_node *intr_node)
{
    Trie_node *r_tr_node;
    List_node *lnode = list_search(list, symbol);
    if (lnode == NULL)
    {
        lnode = list_insert(list, symbol);
        lnode->tr_next = _trie_create_node();
        lnode->tr_next->parent = intr_node;
    }
    r_tr_node = lnode->tr_next;

    return r_tr_node;
}

void trie_print(Trie *tr)
{
    List *root_list = tr->root->keys;
    if (root_list == NULL || root_list->first == NULL)
        printf("Trie is empty\n");
    else
    {
        _trie_print_words(root_list);
    }
}

void _trie_print_words(List *list)
{
    if (list == NULL)
        return;

    List_node *list_node = list->first;
    while (list_node != NULL)
    {
        if (list_node->tr_next->isFinish)
        {
            _print_word(list_node->tr_next);
            printf("\n");
        }
        _trie_print_words(list_node->tr_next->keys);
        list_node = list_node->next;
    }
}

void _print_word(Trie_node *tr_node)
{
    if (tr_node->parent != NULL)
    {
        _print_word(tr_node->parent);
        List_node *list_node = tr_node->parent->keys->first;
        while (list_node->tr_next != tr_node)
            list_node = list_node->next;
        printf("%c", list_node->symbol);
    }
}

void _trie_search(List *list, char *str, size_t cur_pos, size_t len, size_t dep, List *result)
{
    List_node *list_node = list->first;
    size_t next_pos;
    while (list_node != NULL)
    {
        if (str[cur_pos] == list_node->symbol)
            next_pos = cur_pos + 1;
        else
            next_pos = 0;

        if (cur_pos == len)
        {
            _trie_get_words(list_node->tr_next->keys, dep, result);
            next_pos = 0;
        }

        if (list_node->tr_next->keys != NULL)
        {
            _trie_search(list_node->tr_next->keys, str, next_pos, len, dep + 1, result);
        };
        list_node = list_node->next;
    }
}

void _trie_get_words(List *list, size_t dep, List *result)
{
    if (list == NULL)
        return;

    List_node *list_node = list->first;
    while (list_node != NULL)
    {
        if (list_node->tr_next->isFinish)
        {
            char *word = (char *)malloc(sizeof(char) * dep);
            int z = _trie_get_word(list_node->tr_next, result, word);
            word[z] = '\n';
            list_add(result, word);
        }
        _trie_get_words(list_node->tr_next->keys, dep + 1, result);
        list_node = list_node->next;
    }
}

int _trie_get_word(Trie_node *tr_node, List *result, char *word)
{
    int pos = 0;
    if (tr_node->parent != NULL)
    {
        pos = _trie_get_word(tr_node->parent, result, word);
        List_node *list_node = tr_node->parent->keys->first;
        while (list_node->tr_next != tr_node)
            list_node = list_node->next;

        word[pos++] = list_node->symbol;
        // result[pos++] = list_node->symbol;
    }
    return pos;
}

void trie_search(Trie *tr, char *str, List *result)
{
    size_t len = strlen(str);

    _trie_search(tr->root->keys, str, 0, len, 0, result);
}

void _trie_destr_node(Trie_node *);

void trie_destr(Trie **tr)
{
    _trie_destr_node((*tr)->root);
    printf("free tr\n");
    free(*tr);
    *tr = NULL;
}

void _trie_destr_node(Trie_node *tr_next)
{
    if (tr_next->keys == NULL)
    {
        printf("free next\n");
        free(tr_next);
        return;
    }

    List_node *list_node = tr_next->keys->first;
    while (list_node != NULL)
    {
        _trie_destr_node(list_node->tr_next);
        list_node = list_node->next;
    }
    list_destr(&tr_next->keys);
    printf("free next\n");
    free(tr_next);
}