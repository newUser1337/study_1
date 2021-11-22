#include <stdio.h>
#include <stdlib.h>
#include "doublelinkedlist.h"

doublelinkedlistnode* _doublelinkedlistnode_create(void*);
void _doublelinkedlistnode_free(doublelinkedlistnode**);

doublelinkedlist* doublelinkedlist_init(void (*printdata)(void*))
{
    doublelinkedlist *dll = (doublelinkedlist *)malloc(sizeof(doublelinkedlist));
    dll->currentsize = 0;
    dll->printdata = printdata;
    dll->firstnode = NULL;
    dll->lastnode = NULL;

    return dll;
}

doublelinkedlistnode* doublelinkedlist_add(doublelinkedlist *dll, void *data)
{
    doublelinkedlistnode *dllnode = _doublelinkedlistnode_create(data);

    dll->currentsize++;
    if (dll->firstnode == NULL)
        dll->firstnode = dllnode;  
    if (dll->lastnode != NULL)
    {
        dll->lastnode->next = dllnode;
        dllnode->prev = dll->lastnode;
    }
    dll->lastnode = dllnode;

    return dllnode;
}

doublelinkedlistnode* doublelinkedlist_insert(doublelinkedlist *dll, doublelinkedlistnode *dllnode, void *data)
{
    doublelinkedlistnode *newdllnode = _doublelinkedlistnode_create(data);
    newdllnode->next = dllnode->next;
    newdllnode->prev = dllnode;
    dllnode->next = newdllnode;
    newdllnode->next->prev = newdllnode;
    dll->currentsize++;

    return newdllnode;
}

void doublelinkedlist_remove(doublelinkedlist *dll, doublelinkedlistnode *dllnode)
{

    if (dll->firstnode == dllnode)
    {
        dll->firstnode = dllnode->next;
        if (dllnode->next == NULL)
            dll->lastnode = dllnode->next;
        else 
            dllnode->next->prev = NULL;
    }
    else
    {
        dllnode->prev->next = dllnode->next;
        if (dllnode->next == NULL)
            dll->lastnode = dllnode->prev;
            
        else
            dllnode->prev->next->prev = dllnode->prev;
    }
    dll->currentsize--;
    _doublelinkedlistnode_free(&dllnode);
}

doublelinkedlistnode* doublelinkedlist_find(doublelinkedlist *dll, void *data)
{
    doublelinkedlistnode *dllnode = dll->firstnode;
    while(dllnode != NULL && dllnode->data != data)
        dllnode = dllnode->next;
    
    return dllnode;
}

doublelinkedlistnode* _doublelinkedlistnode_create(void *data)
{
    doublelinkedlistnode *dllnode = (doublelinkedlistnode *)malloc(sizeof(doublelinkedlistnode));
    dllnode->data = data;
    dllnode->next = NULL;
    dllnode->prev = NULL;

    return dllnode;
}

void _doublelinkedlistnode_free(doublelinkedlistnode **dllnode)
{
    free(*dllnode);
    *dllnode=NULL;
}

void doublelinkedlist_free(doublelinkedlist **dll)
{
    doublelinkedlistnode *dlldtemp, *dlld;

    if ((*dll)->firstnode == NULL)
    {
        free(*dll);
        *dll=NULL;
        return;
    }

    dlld = (*dll)->firstnode;
    do
    {
        dlldtemp = dlld->next;
        _doublelinkedlistnode_free(&dlld);
        dlld=dlldtemp;
    } while (dlld != NULL);

    free(*dll);
    *dll=NULL;
}

void doublelinkedlist_print(doublelinkedlist *dll, int count)
{
    doublelinkedlistnode *dlld = dll->firstnode;
    int i = 1;

    if (dll->printdata == NULL)
    {
        printf("Print function is not specified\n");
        return;
    }
    if (dlld == NULL)
    {
        printf("Elements not found\n");
        return;
    }
    if (count <= 0)
    {
        printf("Incorrect count of elements\n");
        return;
    }

    printf("Node count %ld\n", dll->currentsize);

    do
    {
        dll->printdata(dlld->data);
        dlld = dlld->next;
    } while (dlld != NULL && ++i <= count);

    printf("\n");
}