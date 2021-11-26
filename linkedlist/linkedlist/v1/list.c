#include <stdio.h>
#include <stdlib.h>
#include "list.h"

LNode *_list_create_node(void *);
void _list_free_node(LNode **);

List *list_init(int (*cmpdata)(void *, void *), void (*printdata)(void *))
{
    List *list = (List *)malloc(sizeof(List));
    list->first = NULL;
    list->last = NULL;
    list->cmpdata = cmpdata;
    list->printdata = printdata;

    return list;
}

LNode *_list_create_node(void *data)
{
    LNode *node = (LNode *)malloc(sizeof(LNode));
    node->data = data;
    node->next = NULL;
    return node;
}

void _list_free_node(LNode **node)
{
    free((*node));
    *node = NULL;
}

LNode *list_append(List *list, void *data)
{
    LNode *node = _list_create_node(data);
    if (list->last == NULL)

        list->first = node;
    else
        list->last->next = node;
    list->last = node;

    return node;
}

LNode *list_search(List *list, void *data)
{
    LNode *node = list->first;
    while (node != NULL && list->cmpdata(node->data, data))
        node = node->next;

    return node;
}

LNode *list_insert(List *list, void *data)
{
    LNode *node = list_search(list, data);
    if (node == NULL)
    {
        node = _list_create_node(data);
        LNode *prev_node = list_search_prev(list, data);
        if (prev_node != NULL)
        {
            node->next = prev_node->next;
            prev_node->next = node;
        }
        else
        {
            node->next = list->first;
            list->first = node;
        }
        if (node->next == NULL)
            list->last = node;
    }

    return node;
}

LNode *list_search_prev(List *list, void *data)
{
    LNode *node = list->first, *rnode = NULL;
    while (node != NULL && (list->cmpdata(data, node->data) != -1))
    {
        rnode = node;
        node = node->next;
    };

    return rnode;
}

void list_print(List *list)
{
    if (list == NULL)
        return;
    LNode *node = list->first;
    printf("Printing list\n");
    while (node != NULL)
    {
        list->printdata(node->data);
        node = node->next;
    }
    printf("\nEnd of list\n");
}

void list_destr(List **list)
{
    LNode *node = (*list)->first, *temp_node;
    while (node != NULL)
    {
        temp_node = node->next;
        _list_free_node(&node);
        node = temp_node;
    }

    free((*list));
    *list = NULL;
}

void list_remove(List* list, LNode **lnode)
{
    LNode *lnode_prev;

    if (list->first == *lnode)
    {
        list->first = (*lnode)->next;
        if (list->last == *lnode)
        {
            list->last = (*lnode)->next;
        }
    }
    else
    {
        lnode_prev = list->first;
        while (lnode_prev != NULL && lnode_prev->next != *lnode)
            lnode_prev = lnode_prev->next;
        if(lnode_prev == NULL)
            return;
        if ((*lnode)->next == NULL)
        {
            list->last = lnode_prev;
            lnode_prev->next = NULL;

        }
        else
        {
            lnode_prev->next = (*lnode)->next;
        }
    }
    _list_free_node(lnode);
}