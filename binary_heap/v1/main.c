#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main()
{
    Heap *heap = heap_init(20);
    int a = 4,
        b = 3,
        c = 8,
        d = 10,
        e = 11,
        g = 5;
    heap_add_element(heap, &a, a);
    heap_add_element(heap, &b, b);
    heap_add_element(heap, &c, c);
    heap_add_element(heap, &d, d);
    heap_add_element(heap, &e, e);
    heap_add_element(heap, &g, g);
    heap_print_index(heap);
    heap_pop(heap);
    heap_print_index(heap);
    heap_pop(heap);
    heap_print_index(heap);

    return 0;
}