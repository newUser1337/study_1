#include "stack.h"
#include <stdio.h>
#include <string.h>

void strcopy(char * , const char* );


typedef struct buz{
    int pagecount;
    char name[50];
} buz;

int main() {

    
    // int a = 6, b = 9, c =12;
    // s = stack_init(3);
    // stack_push(&s, &a);
    // stack_push(&s, &b);
    // stack_push(&s, &c);

    // int *z;
    // z = (int*)stack_pop(&s);
    // printf("%d \n", *z);
    // z = (int*)stack_pop(&s);
    // printf("%d \n", *z);
    // z = (int*)stack_peek(&s);
    // printf("%d \n", *z);
    // z = (int*)stack_pop(&s);
    // printf("%d \n", *z);

    // z = (int*)stack_pop(&s);
    // if(z == NULL)
    //     printf("pop \n");

    // stack_free(&s);

    Stack s;
    s = stack_init(4);
    buz a1; 
    a1.pagecount = 20; 

    // a1.name = "Name1";
    strcpy(a1.name, "Name1");

    printf("%s\n", a1.name);

    buz a2; 
    a2.pagecount = 30; 
    // a2.name = "Name2"; 
    buz a3; 
    a3.pagecount = 40; 
    // a3.name = "Name3";
    stack_push(&s, &a1);
    stack_push(&s, &a2);
    stack_push(&s, &a3);

    buz *z = (buz*)stack_pop(&s);
    printf("%d  %s\n", z->pagecount, z->name);
    
    
    stack_free(&s);
    return 0;
}