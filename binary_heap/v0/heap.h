#ifndef __HEAP__
#define __HEAP__

typedef struct Heap
{
    int size;
    int *A;
} Heap;

Heap *heap_init(int *, int);
void heap_destr(Heap **);
void build_heap(Heap *);

#endif