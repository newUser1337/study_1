#ifndef __DOUBLELINKEDLIST__H__
#define __DOUBLELINKEDLIST__H__

/*
  Double linked list node 
 */
typedef struct doublelinkedlistnode{
    void* data;
    struct doublelinkedlistnode* next;
    struct doublelinkedlistnode* prev;
} doublelinkedlistnode;

/*
  Double linked list
 */
typedef struct doublelinkedlist{
    doublelinkedlistnode* firstnode;
    doublelinkedlistnode* lastnode;
    doublelinkedlistnode* _current;
    long currentsize;
    void (*printdata)(void*);
} doublelinkedlist;

/*
 Initializes doublelinked list
*/
doublelinkedlist* doublelinkedlist_init(void (*)(void*));

/*
 Adds node to doublelinked list
*/
doublelinkedlistnode* doublelinkedlist_add(doublelinkedlist*, void*);

/*
 Inserts node in doublelinked list after specified node
*/
doublelinkedlistnode* doublelinkedlist_insert(doublelinkedlist*, doublelinkedlistnode*, void*);

/*
 Removes node from doublelinked list
*/
void doublelinkedlist_remove(doublelinkedlist*, doublelinkedlistnode*);

/*
 Finds node of linked list by data
*/
doublelinkedlistnode* doublelinkedlist_find(doublelinkedlist*, void*);

/*
 Deletes link list
*/
void doublelinkedlist_free(doublelinkedlist**);

/*
 Prints data of linked list
*/
void doublelinkedlist_print(doublelinkedlist*, int);
#endif
