#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

void init_array(int *, int);
void print_array(int *, int);
void heapify(int *, int);
void make_heap(int *, int);
void _heapify(int *, int, int);
void swap(int *, int *);

void heap_sort(int *, int);

int main()
{
    int array[SIZE];
    init_array(array, SIZE);
    print_array(array, SIZE);

    make_heap(array, SIZE);
    print_array(array, SIZE);

    heap_sort(array, SIZE);
    print_array(array, SIZE);
    return 0;
}

void heap_sort(int *A, int size)
{
    for (int i = size - 1; i > 0; i--)
    {
        swap(&A[0], &A[i]);
        _heapify(A, 0, i);
    }
}

void make_heap(int *A, int size)
{
    for (int i = size / 2; i > 0; i--)
        _heapify(A, i, size);
}

void heapify(int *array, int size)
{
    _heapify(array, 0, size);
}
void _heapify(int *A, int index, int size)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;
    if (left < size && A[left] > A[largest])
        largest = left;
    if (right < size && A[right] > A[largest])
        largest = right;
    if (largest != index)
    {
        swap(&A[index], &A[largest]);
        _heapify(A, largest, size);
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void init_array(int *array, int size)
{
    for (int i = 0; i < size; i++)
        array[i] = rand() % 15;
}

void print_array(int *array, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}