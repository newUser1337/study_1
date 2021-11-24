#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"

void _heap_set_element(Heap *, int, int);
void swap(Heap_node *, Heap_node *);
void _heap_realloc_cpy_mem(Heap *, int);
void _heap_add_new(Heap *, int, int);

Heap *heap_init(int size)
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->size = 0;
    heap->bufsize = size * 2;
    heap->Array = (Heap_node *)malloc(sizeof(Heap_node) * heap->bufsize);

    return heap;
}

void heap_build(Heap *heap, int size)
{
    for (int i = size / 2; i > 0; i--)
        _heap_set_element(heap, i, size);
}

void _heap_set_element(Heap *heap, int pos, int size)
{
    int left = heap_get_left(pos);
    int right = heap_get_right(pos);
    int most = pos;
    if (left < size && heap->Array[left].index > heap->Array[most].index)
        most = left;
    if (right < size && heap->Array[right].index > heap->Array[most].index)
        most = right;
    if (most != pos)
    {
        swap(&heap->Array[pos], &heap->Array[most]);
        _heap_set_element(heap, most, size);
    }
}

void swap(Heap_node *a, Heap_node *b)
{
    Heap_node temp = *a;
    *a = *b;
    *b = temp;
}

void heap_destr(Heap **heap)
{
    free((*heap)->Array);
    free(*heap);
}

int heap_get_left(int pos)
{
    return pos * 2 + 1;
}

int heap_get_right(int pos)
{
    return pos * 2 + 2;
}

int heap_get_parent(int pos)
{
    return (pos - 1) / 2;
}

int _heap_alloc_memory(Heap *heap, int req_size)
{
    if (req_size < heap->bufsize)
        return 0;

    heap->bufsize *= 2;

    _heap_realloc_cpy_mem(heap, heap->bufsize);

    return 1;
}

int _heap_free_memory(Heap *heap, int req_size)
{
    if (!(req_size < heap->bufsize / 2))
        return 0;
    heap->bufsize /= 2;

    _heap_realloc_cpy_mem(heap, heap->bufsize);

    return 1;
}

void _heap_realloc_cpy_mem(Heap *heap, int size)
{
    Heap_node *temp_pointer = heap->Array;
    heap->Array = (Heap_node *)malloc(sizeof(Heap_node) * size);
    memcpy(heap->Array, temp_pointer, sizeof(Heap_node) * heap->size);
    free(temp_pointer);
}

Heap_node heap_add_element(Heap *heap, void *data, int index)
{
    _heap_alloc_memory(heap, heap->size + 1);
    heap->Array[heap->size].data = data;
    heap->Array[heap->size].index = index;
    _heap_add_new(heap, heap->size, index);

    return heap->Array[heap->size++];
}

void _heap_add_new(Heap *heap, int pos, int index)
{
    while (pos > 0 && heap->Array[(pos - 1) / 2].index < heap->Array[pos].index)
    {
        swap(&heap->Array[(pos - 1) / 2], &heap->Array[pos]);
        pos = (pos - 1) / 2;
    }
}

Heap_node heap_pop(Heap *heap)
{
    Heap_node r_node = heap->Array[0];

    heap->Array[0] = heap->Array[--heap->size];
    _heap_set_element(heap, 0, heap->size);

    return r_node;
}

void heap_print_index(Heap *heap)
{
    for (int i = 0; i < heap->size; i++)
        printf("%d ", heap->Array[i].index);
    printf("\n");
}