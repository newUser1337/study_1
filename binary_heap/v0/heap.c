#include <stdlib.h>
#include "heap.h"

void _heap_heapify(Heap *, int, int);

Heap *heap_init(int array, int size)
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->size = size;
    heap->A = (int *)malloc(sizeof(int) * size);

    return heap;
}

void heap_destr(Heap **heap)
{
    free((*heap)->A);
    free(*heap);
    *heap = NULL;
}

void build_heap(Heap *heap)
{
    for (int i = heap->size / 2 - 1; i > 0; i--)
    {
    }
}

void _heap_heapify(Heap *heap, int index, int size)
{
}