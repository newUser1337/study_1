#include "stack.h"
#include <stdlib.h>

Stack *stack_init(size_t size)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = 0;
    stack->bufsize = size;
    stack->buf = (void **)malloc(sizeof(void *) * size);

    return stack;
}

void stack_free(Stack **stack)
{
    free((*stack)->buf);
    (*stack)->buf = NULL;
    free(*stack);
    *stack = NULL;
}

void* stack_peek(Stack * stack)
{
    if(stack->top == 0)
        return NULL;
    return stack->buf[stack->top-1];
}

void* stack_pop(Stack *stack)
{
    if(stack->top == 0)
        return NULL;
    return stack->buf[--stack->top];
}

void stack_push(Stack *stack, void* data)
{
    if(stack->top == stack->bufsize)
        exit(1);
    stack->buf[stack->top++]= data;
}