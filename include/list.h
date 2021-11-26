#ifndef __LIST__
#define __LIST__

typedef struct LNode
{
    void *data;
    struct LNode *next;
} LNode;

typedef struct List
{
    LNode *first;
    LNode *last;
    int (*cmpdata)(void *, void *);
    void (*printdata)(void *);
} List;

List *list_init(int (*)(void *, void *), void (*)(void *));
LNode *list_append(List *, void *);
LNode *list_search(List *, void *);
LNode *list_insert(List *, void *);
LNode *list_search_prev(List *, void *);
void list_print(List *);
void list_destr(List **);
void list_remove(List* , LNode **);

#endif