#include "stack.h"
#include <stdlib.h>

Stack stack_init(size_t size)
{
    Stack s;
    s.top = 0;
    s.bufsize = size;
    s.buf = (void **)malloc(sizeof(void *) * size);

    return s;
}

void stack_free(Stack *s)
{
    free(s->buf);
    s->buf = NULL;
}

void* stack_peek(Stack * s)
{
    if(s->top == 0)
        return NULL;
    return s->buf[s->top-1];
}

void* stack_pop(Stack *s)
{
    if(s->top == 0)
        return NULL;
    return s->buf[--s->top];
}

void stack_push(Stack *s, void* data)
{
    if(s->top == s->bufsize)
        exit(1);
    s->buf[s->top++]= data;
}