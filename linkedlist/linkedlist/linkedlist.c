#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

linkedlistnode *_linkedlistnode_create(void *);
void _linkedlistnode_free(linkedlistnode **);

linkedlist *linkedlist_init(void (*printdata)(void *))
{
    linkedlist *ll = (linkedlist *)malloc(sizeof(linkedlist));
    ll->currentsize = 0;
    ll->printdata = printdata;
    ll->firstnode = NULL;
    ll->lastnode = NULL;
    ll->_current = NULL;

    return ll;
}

linkedlistnode *linkedlist_add(linkedlist *ll, void *data)
{
    linkedlistnode *llnode = _linkedlistnode_create(data);

    ll->currentsize++;
    if (ll->firstnode == NULL)
    {
        ll->firstnode = llnode;
        ll->_current = llnode;
    }
    else
        ll->lastnode->next = llnode;
    ll->lastnode = llnode;

    return llnode;
}

linkedlistnode *linkedlist_insert(linkedlist *ll, linkedlistnode *llnode, void *data)
{
    linkedlistnode *newllnode = _linkedlistnode_create(data);
    newllnode->next = llnode->next;
    llnode->next = newllnode;
    ll->currentsize++;

    return newllnode;
}

void linkedlist_remove(linkedlist *ll, linkedlistnode *llnode)
{
    linkedlistnode *llnodeprev;

    if (ll->firstnode == llnode)
    {
        ll->firstnode = llnode->next;
        if (ll->lastnode == llnode)
        {
            ll->lastnode = llnode->next;
            ll->_current = llnode->next;
        }
    }
    else
    {
        llnodeprev = ll->firstnode;
        while (llnodeprev->next != llnode)
            llnodeprev = llnodeprev->next;
        if(llnodeprev == NULL)
            return;
        if(ll->_current == llnode)
            ll->_current = llnodeprev;
        if (llnode->next == NULL)
        {
            ll->lastnode = llnodeprev;
            llnodeprev->next = NULL;

        }
        else
        {
            llnodeprev->next = llnode->next;
        }
    }
    ll->currentsize--;
    _linkedlistnode_free(&llnode);
}

linkedlistnode *linkedlist_getcurrentnode(linkedlist *ll)
{
    return ll->_current;
}

linkedlistnode *linkedlist_getnextnode(linkedlist *ll)
{
    ll->_current = ll->_current->next;

    return ll->_current;
}

void linkedlist_reset(linkedlist *ll)
{
    ll->_current = ll->firstnode;
}

linkedlistnode *linkedlist_find(linkedlist *ll, void *data)
{
    linkedlistnode *llnode = ll->firstnode;
    while (llnode != NULL && llnode->data != data)
        llnode = llnode->next;

    return llnode;
}

linkedlistnode *_linkedlistnode_create(void *data)
{
    linkedlistnode *llnode = (linkedlistnode *)malloc(sizeof(linkedlistnode));
    llnode->data = data;
    llnode->next = NULL;

    return llnode;
}

void _linkedlistnode_free(linkedlistnode **llnode)
{
    free(*llnode);
    *llnode = NULL;
}

void linkedlist_free(linkedlist **ll)
{
    linkedlistnode *lldtemp, *lld;
    
    lld = (*ll)->firstnode;
    while (lld != NULL)
    {
        lldtemp = lld->next;
        _linkedlistnode_free(&lld);
        lld = lldtemp;
    }
    free(*ll);
    *ll = NULL;
}

void linkedlist_print(linkedlist *ll, int count)
{
    linkedlistnode *lld = ll->firstnode;
    int i = 1;

    if (ll->printdata == NULL)
    {
        printf("Print function is not specified\n");
        return;
    }
    if (lld == NULL)
    {
        printf("Elements not found\n");
        return;
    }
    if (count <= 0)
    {
        printf("Incorrect count of elements\n");
        return;
    }

    printf("Node count %ld\n", ll->currentsize);

    do
    {
        ll->printdata(lld->data);
        lld = lld->next;
    } while (lld != NULL && ++i <= count);

    printf("\n");
}
