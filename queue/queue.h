#include <stdlib.h>

#ifndef __QUEUE__
#define __QUEUE__

typedef struct Queue{
    size_t bufsize;
    void **buf;
    size_t st;
    size_t end;
    size_t length;
} Queue;


Queue queue_init(size_t);
void queue_free(Queue *);
void queue_queue(Queue *, void *);
void* queue_dequeue(Queue *);
void queue_print(Queue*, void (*)(void*));
#endif