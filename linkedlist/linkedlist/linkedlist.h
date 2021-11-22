#ifndef __LINKEDLIST__H__
#define __LINKEDLIST__H__ 

/*
  Linked list node 
 */
typedef struct linkedlistnode{
    void* data;
    struct linkedlistnode* next;
} linkedlistnode;

/*
  Linked list
 */
typedef struct linkedlist{
    linkedlistnode* firstnode;
    linkedlistnode* lastnode;
    linkedlistnode* _current;
    long currentsize;
    void (*printdata)(void*);
} linkedlist;

/*
 Initializes linked list
*/
linkedlist* linkedlist_init(void (*)(void*));

/*
 Adds node to linked list
*/
linkedlistnode* linkedlist_add(linkedlist*, void*);

/*
 Inserts node in linked list after specified node
*/
linkedlistnode* linkedlist_insert(linkedlist*, linkedlistnode*, void*);

/*
 Removes node from linked list
*/
void linkedlist_remove(linkedlist*, linkedlistnode*);

/*
 Gets current node in linked list
*/
linkedlistnode* linkedlist_getcurrentnode(linkedlist*);

/*
 Gets next node in linked list
*/
linkedlistnode* linkedlist_getnextnode(linkedlist*);

/*
 Resets current node to first node of linked list
*/
void linkedlist_reset(linkedlist*);

/*
 Finds node of linked list by data
*/
linkedlistnode* linkedlist_find(linkedlist*, void*);

/*
 Deletes link list
*/
void linkedlist_free(linkedlist**);

/*
 Prints data of linked list
*/
void linkedlist_print(linkedlist*, int);

#endif
