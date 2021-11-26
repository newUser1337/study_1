#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int cmp_data(void *, void *);
void print_data(void *);

int main()
{
    Graph *graph = graph_init(print_data, cmp_data);
    int arr[8] = {0};
    graph_add(graph, 1, &arr[0]);
    graph_add(graph, 2, &arr[1]);
    graph_add(graph, 3, &arr[2]);
    graph_add(graph, 4, &arr[3]);
    graph_add(graph, 5, &arr[4]);
    graph_add(graph, 6, &arr[5]);
    graph_add(graph, 7, &arr[6]);
    graph_add(graph, 8, &arr[7]);
    int opres;

    graph_connect(graph, 2, 1, &opres);
    graph_connect(graph, 2, 3, &opres);
    graph_connect(graph, 2, 4, &opres);
    graph_connect(graph, 1, 7, &opres);
    graph_connect(graph, 3, 6, &opres);
    graph_connect(graph, 3, 4, &opres);
    graph_connect(graph, 5, 6, &opres);
    graph_connect(graph, 5, 4, &opres);
    graph_connect(graph, 5, 8, &opres);
    graph_print(graph);

    printf("dfs\n");
    graph_dfs(graph, 2);
    printf("dfs_rec\n");
    graph_dfs_rec(graph, 2);
    printf("bfs\n");
    graph_bfs(graph, 2);
    printf("cycle: \n");
    graph_cycle(graph, 8);

    graph_destr(&graph);

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