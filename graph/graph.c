#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "tree.h"
#include "graph.h"
#include "queue.h"
#include "stack.h"

typedef struct Path
{
    int from;
    int to;
} Path;

GNode *_graph_create_node(Graph *, int, void *);
void _graph_add(Graph *, GNode *);
Tree *_graph_get_tree(Graph *);
List *_graph_get_list_node(Graph *, GNode *);
void _graph_print_node_rec(Graph *, TNode *);
void _graph_print_node(Graph *, GNode *);
void _graph_print_node_index(Graph *, GNode *);
void _graph_dfs(Graph *, GNode *, Stack *, int *);
void _graph_dfs_rec(Graph *, GNode *, int *);
void _graph_bfs(Graph *, GNode *, Queue *, int *);
void _graph_cycle(Graph *, GNode *, int *, GNode *, Stack *, int *);
void _graph_tree_destr(Tree **);
void _graph_tree_node_destr_rec(TNode *);
void _graph_tree_node_destr(TNode **);
void _graph_init_isvisit_array(int *, int);
void _graph_print_stack_cycle(Stack *, int);
int _graph_stack_search(Stack *, int);
void _graph_get_component_rec(Graph *, TNode *, int *, List *);
void _graph_get_component_rec_ver(Graph *, LNode *, LNode *, int *);
int cmp_index(void *, void *);
int print_index(void *);
void _graph_direct_cycle(Graph *, LNode *, List *, List *, List *, List *, int *);
void _graph_fill_list_rec(Graph *, List *, TNode *);
void _graph_fill_list(Graph *, List *);
void print_path(void *);

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
    GNode *node = _graph_create_node(graph, index, data);
    graph->size++;
    _graph_add(graph, node);

    return node;
}

GNode *_graph_create_node(Graph *graph, int index, void *data)
{
    GNode *node = (GNode *)malloc(sizeof(GNode));
    node->data = data;
    node->index = index;
    node->list_nodes = list_init(graph->cmpdata, graph->printdata);

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

    _graph_init_isvisit_array(isvisited, graph->size);
    st = stack_init(graph->size);
    _graph_dfs(graph, node, st, isvisited);
    stack_free(&st);
    printf("\n");
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
    _graph_init_isvisit_array(isvisited, graph->size);
    _graph_dfs_rec(graph, node, isvisited);
    printf("\n");
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

    _graph_init_isvisit_array(isvisited, graph->size);
    queue = queue_init(graph->size);
    _graph_bfs(graph, node, queue, isvisited);
    queue_free(&queue);
    printf("\n");
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

void graph_get_component(Graph *graph, List *result)
{
    int isvisited[graph->size];
    _graph_init_isvisit_array(isvisited, graph->size);

    _graph_get_component_rec(graph, graph->tree->first, isvisited, result);
}

void _graph_get_component_rec(Graph *graph, TNode *root, int *isvisited, List *result)
{
    if (root == NULL)
        return;
    if (!isvisited[((GNode *)root->data)->index - 1])
    {
        isvisited[((GNode *)root->data)->index - 1] = 1;

        List *list_nodes = ((GNode *)root->data)->list_nodes;
        GNode *source = _graph_create_node(graph, ((GNode *)root->data)->index, ((GNode *)root->data)->data);
        _graph_get_list_node(graph, source);
        LNode *cur_node = list_append(result, source);
        list_insert(((GNode *)cur_node->data)->list_nodes, source);
        LNode *node;
        if (list_nodes != NULL)
        {
            node = list_nodes->first;
            _graph_get_component_rec_ver(graph, cur_node, node, isvisited);

            while (node != NULL)
            {
                if (!isvisited[((GNode *)node->data)->index - 1])
                {
                    isvisited[((GNode *)node->data)->index - 1] = 1;
                    list_insert(((GNode *)cur_node->data)->list_nodes, node->data);
                }
                node = node->next;
            }
        }
    }
    _graph_get_component_rec(graph, root->left, isvisited, result);
    _graph_get_component_rec(graph, root->right, isvisited, result);
}

void _graph_get_component_rec_ver(Graph *graph, LNode *root, LNode *node, int *isvisited)
{
    while (node != NULL)
    {
        if (!isvisited[((GNode *)node->data)->index - 1])
        {
            isvisited[((GNode *)node->data)->index - 1] = 1;
            list_insert(((GNode *)root->data)->list_nodes, node->data);
            _graph_get_component_rec_ver(graph, root, ((GNode *)node->data)->list_nodes->first, isvisited);
        }
        node = node->next;
    }
}

int graph_cycle(Graph *graph, int start_index)
{
    GNode *node;
    Stack *stack;
    int isvisited[graph->size];
    int result = 0;

    node = graph_find_ind(graph, start_index);
    if (node == NULL)
    {
        printf("Error: node not found\n");
        return result;
    }

    _graph_init_isvisit_array(isvisited, graph->size);
    stack = stack_init(graph->size);
    _graph_cycle(graph, node, isvisited, node, stack, &result);
    stack_free(&stack);
}

void _graph_cycle(Graph *graph, GNode *node, int *isvisited, GNode *from, Stack *stack, int *res)
{
    if (isvisited[node->index - 1])
        return;
    LNode *lnode = (_graph_get_list_node(graph, node))->first;
    isvisited[node->index - 1] = 1;
    stack_push(stack, node);
    while (lnode != NULL)
    {
        if (isvisited[((GNode *)lnode->data)->index - 1] && ((GNode *)lnode->data)->index != from->index)
        {
            if (_graph_stack_search(stack, ((GNode *)lnode->data)->index))
            {
                _graph_print_stack_cycle(stack, ((GNode *)lnode->data)->index);
                isvisited[node->index - 1] = 0;
                stack_pop(stack);
                *res = 1;
                return;
            }
        }
        if (!isvisited[((GNode *)lnode->data)->index - 1])
            _graph_cycle(graph, lnode->data, isvisited, node, stack, res);
        lnode = lnode->next;
    }
    stack_pop(stack);
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

void _graph_init_isvisit_array(int *array, int size)
{
    for (int i = 0; i < size; i++)
        array[i] = 0;
}

int _graph_stack_search(Stack *stack, int index)
{
    int res = 0;
    for (int i = 0; i < stack->top; i++)
    {
        if (((GNode *)stack->buf[i])->index == index)
        {
            res = 1;
            break;
        }
    }
    return res;
}

void _graph_print_stack_cycle(Stack *stack, int start_index)
{
    int j;
    for (j = 0; j < stack->top; j++)
        if (((GNode *)stack->buf[j])->index == start_index)
            break;

    for (int i = j; i < stack->top; i++)
        printf("%d ", ((GNode *)stack->buf[i])->index);
    printf("\n");
}

void graph_connect_direct(Graph *graph, int index_1, int index_2, int *opres)
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
    if (list_search(list2, node_1) != NULL)
    {
        printf("Nodes already connected\n");
        *opres = 2;
        return;
    }
    list_insert(list1, node_2);
    *opres = 0;
}

int graph_direct_cycle(Graph *graph, List **out_path)
{
    int result = 0;
    List *l_nprocess = list_init(graph->cmpdata, graph->printdata);
    List *l_inprocess = list_init(graph->cmpdata, graph->printdata);
    List *l_processed = list_init(graph->cmpdata, graph->printdata);
    *out_path = list_init(cmp_index, print_path);
    _graph_fill_list(graph, l_nprocess);
    while (l_nprocess->first != NULL)
        _graph_direct_cycle(graph, l_nprocess->first, l_nprocess, l_inprocess, l_processed, *out_path, &result);
    
    list_destr(&l_nprocess);
    list_destr(&l_inprocess);
    list_destr(&l_processed);
    
    return result;
}

void _graph_direct_cycle(Graph *graph, LNode *root, List *l_nprocess, List *l_inprocess, List *l_processed, List *path, int *res)
{
    if (root == NULL)
        return;
    if (list_search(l_processed, root->data) != NULL)
        return;
    if (list_search(l_inprocess, root->data) != NULL)
    {
        *res = 1;
        return;
    }

    LNode *ltemp = list_insert(l_inprocess, root->data);
    LNode *l_del = list_search(l_nprocess, root->data);
    list_remove(l_nprocess, &l_del);
    List *list_child = ((GNode *)ltemp->data)->list_nodes;
    LNode *lnode = list_child->first;
    while (lnode != NULL)
    {
        Path *path_data = (Path *)malloc(sizeof(Path));
        path_data->from = ((GNode *)ltemp->data)->index;
        path_data->to = ((GNode *)lnode->data)->index;
        list_append(path, path_data);

        _graph_direct_cycle(graph, lnode, l_nprocess, l_inprocess, l_processed, path, res);

        lnode = (lnode == NULL) ? list_child->first : lnode->next;
    }
    list_insert(l_processed, ltemp->data);
    list_remove(l_inprocess, &ltemp);
}

void _graph_fill_list(Graph *graph, List *l_nprocess)
{
    _graph_fill_list_rec(graph, l_nprocess, graph->tree->first);
}
void _graph_fill_list_rec(Graph *graph, List *l_nprocess, TNode *root)
{
    if (root == NULL)
        return;

    list_append(l_nprocess, root->data);

    _graph_fill_list_rec(graph, l_nprocess, root->left);
    _graph_fill_list_rec(graph, l_nprocess, root->right);
}

int print_index(void *data)
{
    printf("%d ", *((int *)data));
}

void print_path(void *data)
{
    Path *z = data;
    printf("(%d->%d) \n", z->from, z->to);
}

int cmp_index(void *data_1, void *data_2)
{
    int *a1, *a2;
    a1 = data_1;
    a2 = data_2;
    if (*a1 > *a2)
        return 1;
    else if (*a1 < *a2)
        return -1;
    else
        return 0;
}