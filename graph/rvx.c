/* По графу вывести отдельные компоненты - количество графов, 
и количество вершинв графе  */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int cmp_data(void *, void *);
void print_data(void *);

int main()
{
    Graph *graph = graph_init(print_data, cmp_data);
    int arr[13] = {0};
    int opres;
    int arg = 0;
    int ind = 1;
    graph_add(graph, ind++, &arr[arg++]);
    graph_add(graph, ind++, &arr[arg++]);
    graph_add(graph, ind++, &arr[arg++]);
    graph_add(graph, ind++, &arr[arg++]);
    graph_add(graph, ind++, &arr[arg++]);
    graph_add(graph, ind++, &arr[arg++]);
    graph_add(graph, ind++, &arr[arg++]);
    graph_add(graph, ind++, &arr[arg++]);
    graph_add(graph, ind++, &arr[arg++]);
    graph_add(graph, ind++, &arr[arg++]);
    graph_add(graph, ind++, &arr[arg++]);
    graph_add(graph, ind++, &arr[arg++]);

    graph_connect(graph, 2, 1, &opres);
    graph_connect(graph, 2, 3, &opres);
    graph_connect(graph, 2, 4, &opres);
    graph_connect(graph, 1, 7, &opres);
    graph_connect(graph, 3, 6, &opres);
    graph_connect(graph, 3, 4, &opres);
    graph_connect(graph, 5, 6, &opres);
    graph_connect(graph, 5, 4, &opres);
    graph_connect(graph, 5, 8, &opres);
    graph_connect(graph, 11, 10, &opres);
    graph_connect(graph, 9, 10, &opres);
    graph_print(graph);

    List *result = list_init(cmp_data, print_data);
    graph_get_component(graph, result);
    list_print(result);
    LNode *node = result->first;
    while (node != NULL)
    {
        list_print(((GNode *)node->data)->list_nodes);
        node = node->next;
    }

    return 0;
}

void print_data(void *data)
{
    GNode *node = data;
    printf("%d ", node->index);
}

int cmp_data(void *data_1, void *data_2)
{
    GNode *node_1 = data_1, *node_2 = data_2;
    int res;
    if (node_1->index < node_2->index)
        res = -1;
    else if (node_1->index > node_2->index)
        res = 1;
    else
        res = 0;
    return res;
}