#include "list.h" 

#ifndef __TRIE__
#define __TRIE__

typedef struct Trie_node
{
    struct Trie_node *parent;
    List *keys;
    int isFinish;
} Trie_node;

typedef struct Trie
{
    Trie_node *root;
} Trie;

typedef struct node_list
{
    char symbol;
    Trie_node *tr_next;
}node_list;

Trie *trie_init();
void trie_add_word(Trie *, char *);
void trie_print(Trie *);
void trie_search(Trie *, char *, List *);
void trie_destr(Trie **);
#endif