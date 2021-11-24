#ifndef __HEAP__
#define __HEAP__

typedef struct Heap_node
{
    int index;
    void *data;
} Heap_node;

typedef struct Heap
{
    int size;
    int bufsize;
    Heap_node *Array;
} Heap;

Heap *heap_init(int);
void heap_destr(Heap **);
int heap_get_left(int);
int heap_get_right(int);
int heap_get_parent(int);
void heap_build(Heap *, int);
Heap_node heap_add_element(Heap*, void*,int);
Heap_node heap_pop(Heap*);
void heap_print_index(Heap*);


#endif