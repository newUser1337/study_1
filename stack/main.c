#include "stack.h"
#include <stdio.h>
#include <string.h>

void strcopy(char * , const char* );


typedef struct buz{
    int pagecount;
    char name[50];
} buz;

int main() {
    Stack *stack;
    stack = stack_init(4);
    buz a1; 
    a1.pagecount = 20; 

    strcpy(a1.name, "Name1");

    printf("%stack\n", a1.name);

    buz a2; 
    a2.pagecount = 30; 
    buz a3; 
    a3.pagecount = 40; 
    stack_push(stack, &a1);
    stack_push(stack, &a2);
    stack_push(stack, &a3);

    buz *z = (buz*)stack_pop(stack);
    printf("%d  %stack\n", z->pagecount, z->name);
    
    
    stack_free(&stack);
    return 0;
}