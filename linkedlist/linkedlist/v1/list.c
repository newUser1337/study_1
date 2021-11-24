#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Node *_list_create_node(void *);
void _list_free_node(Node **);

List *list_init(int (*cmpdata)(void *, void *), void (*printdata)(void *))
{
    List *list = (List *)malloc(sizeof(List));
    list->first = NULL;
    list->last = NULL;
    list->cmpdata = cmpdata;
    list->printdata = printdata;

    return list;
}

Node *_list_create_node(void *data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void _list_free_node(Node **node)
{
    free((*node));
    *node = NULL;
}

Node *list_append(List *list, void *data)
{
    Node *node = _list_create_node(data);
    if (list->last == NULL)

        list->first = node;
    else
        list->last->next = node;
    list->last = node;

    return node;
}

Node *list_search(List *list, void *data)
{
    Node *node = list->first;
    while (node != NULL && list->cmpdata(node->data, data))
        node = node->next;

    return node;
}

Node *list_insert(List *list, void *data)
{
    Node *node = list_search(list, data);
    if (node == NULL)
    {
        node = _list_create_node(data);
        Node *prev_node = list_search_prev(list, data);
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

Node *list_search_prev(List *list, void *data)
{
    Node *node = list->first, *rnode = NULL;
    while (node != NULL && (list->cmpdata(data, node->data) != -1))
    {
        rnode = node;
        node = node->next;
    };

    return rnode;
}

void list_print(List *list)
{
    Node *node = list->first;
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
    Node *node = (*list)->first, *temp_node;
    while (node != NULL)
    {
        temp_node = node->next;
        _list_free_node(&node);
        node = temp_node;
    }

    free((*list));
    *list = NULL;

}