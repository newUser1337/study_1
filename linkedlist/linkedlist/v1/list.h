#ifndef __LIST__
#define __LIST__

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

typedef struct List
{
    Node *first;
    Node *last;
    int (*cmpdata)(void *, void *);
    void (*printdata)(void *);
} List;

List *list_init(int (*)(void *, void *), void (*)(void *));
Node *list_append(List *, void *);
Node *list_search(List *, void *);
Node *list_insert(List *, void *);
Node *list_search_prev(List *, void *);
void list_print(List *);
void list_destr(List **);

#endif