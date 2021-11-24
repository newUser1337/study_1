#include <stdio.h>
#include <string.h>
#include "queue.h"

typedef struct Book
{
    int pagecount;
    char name[50];
} Book;

void print_book(void *);

int main()
{
    Queue *q = queue_init(3, print_book);

    Book b1;
    b1.pagecount = 20;
    strcpy(b1.name, "Name1");

    Book b2;
    b2.pagecount = 30;
    strcpy(b2.name, "Name2");

    Book b3;
    b3.pagecount = 40;
    strcpy(b3.name, "Name3");

    Book *cur;
    queue_queue(q, &b1);
    queue_queue(q, &b2);
    cur = queue_dequeue(q);
    cur = queue_dequeue(q);
    queue_queue(q, &b3);
    queue_queue(q, &b1);
    queue_print(q);

    queue_free(&q);
    return 0;
}

void print_book(void *val)
{
    printf("Pages %d, name: %s\n", ((Book *)val)->pagecount, ((Book *)val)->name);
}