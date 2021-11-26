#include <stdlib.h>

#ifndef __STACK__
#define __STACK__

typedef struct Stack{

    size_t bufsize;
    size_t top;
    void **buf;
} Stack;

Stack *stack_init(size_t);
void stack_free(Stack **);

void* stack_peek(Stack *);
void* stack_pop(Stack *);
void stack_push(Stack *, void *);
#endif