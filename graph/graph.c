#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "tree.h"
#include "graph.h"
#include "queue.h"
#include "stack.h"

GNode *_graph_create_node(int, void *);
void _graph_add(Graph *, GNode *);
Tree *_graph_get_tree(Graph *);
List *_graph_get_list_node(Graph *, GNode *);
void _graph_print_node_rec(Graph *, TNode *);
void _graph_print_node(Graph *, GNode *);
void _graph_print_node_index(Graph *, GNode *);
void _graph_dfs(Graph *, GNode *, Stack *, int *);
void _graph_dfs_rec(Graph *, GNode *, int *);
void _graph_bfs(Graph *, GNode *, Queue *, int *);
void _graph_tree_destr(Tree **);
void _graph_tree_node_destr_rec(TNode *);
void _graph_tree_node_destr(TNode **);
void _grap_init_isvisit_array(int *, int );

Graph *graph_init(void (*printdata)(void *),
                  int (*cmpdata)(void *, void *))
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->size = 0;
    graph->tree = NULL;
    graph->printdata = printdata;
    graph->cmpdata = cmpdata;

    return graph;
}

GNode *graph_add(Graph *graph, int index, void *data)
{
    GNode *node = _graph_create_node(index, data);
    graph->size++;
    _graph_add(graph, node);

    return node;
}

GNode *_graph_create_node(int index, void *data)
{
    GNode *node = (GNode *)malloc(sizeof(GNode));
    node->data = data;
    node->index = index;
    node->list_nodes = NULL;

    return node;
}

void _graph_add(Graph *graph, GNode *node)
{
    Tree *graph_tree = _graph_get_tree(graph);
    tree_add(graph_tree, node);
}

Tree *_graph_get_tree(Graph *graph)
{
    if (graph->tree == NULL)
        graph->tree = tree_init(graph->printdata, graph->cmpdata);

    return graph->tree;
}

void graph_connect(Graph *graph, int index_1, int index_2, int *opres)
{
    GNode *node_1, *node_2;
    node_1 = graph_find_ind(graph, index_1);
    node_2 = graph_find_ind(graph, index_2);
    if (node_1 == NULL || node_2 == NULL || index_1 == index_2)
    {
        printf("Error during connection\n");
        *opres = 1;
        return;
    }
    List *list1, *list2;
    list1 = _graph_get_list_node(graph, node_1);
    list2 = _graph_get_list_node(graph, node_2);
    if (list_search(list1, node_2) != NULL)
    {
        printf("Nodes already connected\n");
        *opres = 2;
        return;
    }
    list_insert(list1, node_2);
    list_insert(list2, node_1);
    *opres = 0;
}

List *_graph_get_list_node(Graph *graph, GNode *node)
{
    if (node->list_nodes == NULL)
    {
        node->list_nodes = list_init(graph->cmpdata, graph->printdata);
    }
    return node->list_nodes;
}

GNode *graph_find_ind(Graph *graph, int index)
{
    GNode temp_node;
    TNode *tree_node;
    Tree *graph_tree;
    temp_node.index = index;
    graph_tree = _graph_get_tree(graph);
    tree_node = tree_find(graph_tree, &temp_node);
    if (tree_node != NULL)
        return tree_node->data;
    else
        return NULL;

}

void graph_print(Graph *graph)
{
    _graph_print_node_rec(graph, graph->tree->first);
}

void _graph_print_node(Graph *graph, GNode *node)
{
    printf("Printing node, index: ");
    graph->printdata(node);
    printf("\n");
    printf("Printing connections: \n");
    list_print(node->list_nodes);
    printf("End of printing connections \n");
}

void _graph_print_node_index(Graph *graph, GNode *node)
{
    graph->printdata(node);
    printf("\n");
}

void _graph_print_node_rec(Graph *graph, TNode *root)
{
    if (root == NULL)
        return;
    _graph_print_node(graph, root->data);
    _graph_print_node_rec(graph, root->left);
    _graph_print_node_rec(graph, root->right);
}

void graph_dfs(Graph *graph, int start_index)
{
    GNode *node;
    Stack *st;
    int isvisited[graph->size];

    node = graph_find_ind(graph, start_index);
    if (node == NULL)
    {
        printf("Error: node not found\n");
        return;
    }

    _grap_init_isvisit_array(isvisited, graph->size);
    st = stack_init(graph->size);
    _graph_dfs(graph, node, st, isvisited);
    stack_free(&st);
}

void _graph_dfs(Graph *graph, GNode *node, Stack *st, int *isvisited)
{
    List *list_node;
    LNode *lnode;

    isvisited[node->index - 1] = 1;
    stack_push(st, node);
    while (stack_peek(st) != NULL)
    {
        node = stack_pop(st);
        _graph_print_node_index(graph, node);
        lnode = (_graph_get_list_node(graph, node))->first;
        while (lnode != NULL)
        {
            if (!isvisited[((GNode *)lnode->data)->index - 1])
            {
                stack_push(st, lnode->data);
                isvisited[((GNode *)lnode->data)->index - 1] = 1;
            }
            lnode = lnode->next;
        }
    }
}

void graph_dfs_rec(Graph *graph, int start_index)
{
    GNode *node;
    int isvisited[graph->size];

    node = graph_find_ind(graph, start_index);
    if (node == NULL)
    {
        printf("Error: node not found\n");
        return;
    }
    _grap_init_isvisit_array(isvisited, graph->size);
    _graph_dfs_rec(graph, node, isvisited);
}

void _graph_dfs_rec(Graph *graph, GNode *node, int *isvisited)
{
    if (isvisited[node->index - 1])
        return;

    LNode *lnode = (_graph_get_list_node(graph, node))->first;
    isvisited[node->index - 1] = 1;
    _graph_print_node_index(graph, node);
    while (lnode != NULL)
    {
        if (!isvisited[((GNode *)lnode->data)->index - 1])
            _graph_dfs_rec(graph, lnode->data, isvisited);
        lnode = lnode->next;
    }
}

void graph_bfs(Graph *graph, int start_index)
{
    GNode *node;
    Queue *queue;
    int isvisited[graph->size];

    node = graph_find_ind(graph, start_index);
    if (node == NULL)
    {
        printf("Error: node not found\n");
        return;
    }

    _grap_init_isvisit_array(isvisited, graph->size);
    queue = queue_init(graph->size);
    _graph_bfs(graph, node, queue, isvisited);
    queue_free(&queue);
}

void _graph_bfs(Graph *graph, GNode *node, Queue *queue, int *isvisited)
{
    LNode *lnode;
    isvisited[node->index - 1] = 1;
    queue_queue(queue, node);
    while (queue_dequeue_peek(queue) != NULL)
    {
        node = queue_dequeue(queue);
        _graph_print_node_index(graph, node);
        lnode = (_graph_get_list_node(graph, node))->first;
        while (lnode != NULL)
        {
            if (!isvisited[((GNode *)lnode->data)->index - 1])
            {
                queue_queue(queue, lnode->data);
                isvisited[((GNode *)lnode->data)->index - 1] = 1;
            }
            lnode = lnode->next;
        }
    }
}

void graph_destr(Graph **graph)
{
    Tree *graph_tree = _graph_get_tree(*graph);
    _graph_tree_destr(&graph_tree);

    free(*graph);
    *graph = NULL;
}

void _graph_tree_destr(Tree **tr)
{
    if ((*tr)->first != NULL)
        _graph_tree_node_destr_rec((*tr)->first);

    free(*tr);
    *tr = NULL;
}

void _graph_tree_node_destr_rec(TNode *node)
{
    if (node->left != NULL)
        _graph_tree_node_destr_rec(node->left);
    if (node->right != NULL)
        _graph_tree_node_destr_rec(node->right);

    _graph_tree_node_destr(&node);
}

void _graph_tree_node_destr(TNode **node)
{
    if (((GNode *)((*node)->data))->list_nodes != NULL)
        list_destr(&(((GNode *)((*node)->data))->list_nodes));
    free(*node);
    *node = NULL;
}

void _grap_init_isvisit_array(int *array, int size)
{
    for (int i = 0; i < size; i++)
        array[i] = 0;
}