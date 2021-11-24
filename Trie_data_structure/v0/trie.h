#ifndef __TRIE__
#define __TRIE__

typedef struct List_node
{
    struct List_node *next;
    char symbol;
    char *word;
    struct Trie_node *tr_next;
} List_node;

typedef struct List
{
    List_node *first;
} List;

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

List *list_init();
List_node *list_insert(List *, char);
List_node *list_add(List *, char *);
List_node *list_search(List *, char);
void list_node_delete(List *, char);
void list_destr(List **);
void list_print(List *);
void list_print_word(List *);

Trie *trie_init();
void trie_search(Trie *, char *, List *);
void trie_add_word(Trie *, char *);
void trie_print(Trie *);
void trie_destr(Trie**);
#endif