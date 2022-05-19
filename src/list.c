/*
 * @Author: Yarin Avisidris 
 * @Date: 2022-05-18 23:21:07 
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2022-05-19 00:21:49
 */
#include "../include/list.h"
#include <stdlib.h>
struct List {
    Item * GenericArray;
    Item * InternalIterator;
    size_t ArraySize; /* how many pointers to items */
    size_t items_no; /* how many set items*/
    Item (*ctor)(Item);;
    void (*dtor)(Item);
    int (*compar)(Item,Item);
};
#define base_len 2

List newList(Item (*ctor)(Item),
             void (*dtor)(Item),
             int (*compar)(Item,Item))  {
                 List  ret = malloc(sizeof(struct List));
                 /**
                  * @note handle later..
                  * 
                  */
                 if(!ret) {return NULL;}
                 
                 ret->ArraySize = base_len;
                 ret->GenericArray = calloc(ret->ArraySize,sizeof(Item));
                 /**
                  * @brief handle later..
                  * 
                  */
                 if(!ret->GenericArray){
                     free(ret);
                     return NULL;
                 }
                 ret->ctor      = ctor;
                 ret->dtor      = dtor;
                 ret->compar    = compar;

                 ret->items_no  = 0;
                 ret->InternalIterator = ret->GenericArray;
        return ret;
             }

void ListDestroy(List L) {
    size_t i;
    for(i=0;i<L->ArraySize;i++) {
        if(L->GenericArray[i]) {
            L->dtor(L->GenericArray[i]);
            L->GenericArray[i] = NULL;
        }
    }
    free(L->GenericArray);
}

Item ListFind(List L,Item clone) {
    size_t i;
    if(!L)
        return NULL;
    Item * Iterator = L->GenericArray;
    for(i=0;i<L->ArraySize;i++,Iterator++) {
        if(*(Iterator) && L->compar(*Iterator,clone) == 0)
            return *Iterator;
    }
return NULL;
}

void ListDelete(List L, Item clone) {
    size_t i;
    if(!L)
        return NULL;
    Item * Iterator = L->GenericArray;
    for(i=0;i<L->ArraySize;i++,Iterator++) {
        if(*(Iterator) && L->compar(*Iterator,clone) == 0) {
            L->dtor(*Iterator);
            *Iterator = NULL;
        }
    }
}

void ListInsert(List L, Item clone) {
    size_t i;
    if(!L || !clone)
        return;
    for(i=0;i<L->ArraySize;i++) {

    }
}
Item ListItRewind(List L) {
    size_t i;
    if(!L)
        return NULL;
    L->InternalIterator = L->GenericArray;
    for(i=0;i<L->ArraySize;i++,L->InternalIterator++) {
        if(*(L->InternalIterator))
            return *(L->InternalIterator);
    }
return NULL;
}

Item ListGetNextIt(List L) {
    size_t i;
    if(!L)
        return NULL;
        L->InternalIterator++;
    for(i=0;i<L->ArraySize-1;i++,L->InternalIterator++) {
        if(*(L->InternalIterator))
            return *(L->InternalIterator);
    }
return NULL;
}

size_t ListItemsCount(List L) {
    if(L)
        return L->items_no;
    return (0);
}

size_t ListSpaceLeft(List L) {
    if(L)
        return L->ArraySize - L->items_no;
    return 0;
}