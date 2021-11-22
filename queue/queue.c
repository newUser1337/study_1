#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "queue.h"

Queue queue_init(size_t bufsize)
{
    Queue q;
    q.bufsize = bufsize;
    q.st = 0;
    q.end = 0;
    q.length = 0;
    q.buf = (void **)malloc(sizeof(void *) * bufsize);

    return q;
}

void queue_free(Queue *q)
{
    free(q->buf);
    q->buf = NULL;
    q->st = 0;
    q->end = 0;
    q->length = 0;
    q->bufsize = 0;
}

void queue_queue(Queue *q, void *data)
{
    if (q->st == q->end && q->length)
    {
        errno = ENOMEM;
        perror("Queue is full.");
        exit(1);
    }
    q->buf[q->end++] = data;
    q->end = q->end % q->bufsize;
    q->length++;
}

void *queue_dequeue(Queue *q)
{
    if (q->st == q->end && !q->length)
        return NULL;

    void *tmp;
    tmp = q->buf[q->st++];
    q->st = q->st % q->bufsize;
    q->length--;
    return tmp;
}

void queue_print(Queue *q, void (*p_func)(void *data))
{
    printf("Printing queue, bufsize = %zd, lenght = %zd, st = %zd, end = %zd \n",
           q->bufsize, q->length, q->st, q->end);
    size_t cur_pos = q->st;
    size_t cur_len = q->length;
    while (cur_len)
    {
        p_func(q->buf[cur_pos++]);
        cur_pos = cur_pos % q->bufsize;
        cur_len--;
    }
}