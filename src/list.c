/*
 * @Author: Yarin Avisidris 
 * @Date: 2022-05-18 23:21:07 
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2022-05-19 00:21:49
 * @C90 ( ansi C ).
 */
#include "../include/list.h"
#include <stdlib.h>
struct List {
    Item * GenericArray;
    Item * InternalIterator;
    size_t ArraySize; /* how many pointers to items */
    size_t ItemsNo; /* how many set items*/
    Item (*ctor)(CItem);
    void (*dtor)(Item);
    int (*compar)(CItem,CItem);
};
#define base_len 2

List newList(Item (*ctor)(CItem),
             void (*dtor)(Item),
             int (*compar)(CItem,CItem))  {
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

                 ret->ItemsNo  = 0;
                 ret->InternalIterator = ret->GenericArray;
        return ret;
             }
/**
 * @brief doubles the array pointers.
 * 
 * @param L the list. 
 * @return int error status(-1) failed, (0) success.
 */
static int ListGrow(List L) {
    Item * temp;
    size_t i = L->ArraySize;
    L->ArraySize *=2;
    temp = realloc(L->GenericArray,L->ArraySize * sizeof(Item));
    if(!temp) {
        L->ArraySize /=2;
        return -1;
    }
    L->GenericArray = temp;
    for(;i<L->ArraySize;i++)
        L->GenericArray[i] = NULL;
    
    return 0;
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
    free(L);
}

Item ListFind(List L,CItem clone) {
    Item * Iterator;
    size_t i;
    if(!L)
        return NULL;
    Iterator = L->GenericArray;
    for(i=0;i<L->ArraySize;i++,Iterator++) {
        if(*(Iterator) && L->compar(*Iterator,clone) == 0)
            return *Iterator;
    }
return NULL;
}

void ListDelete(List L,CItem clone) {
    Item * Iterator;
    size_t i;
    if(!L)
        return;
     Iterator = L->GenericArray;
    for(i=0;i<L->ArraySize;i++,Iterator++) {
        if(*(Iterator) && L->compar(*Iterator,clone) == 0) {
            L->dtor(*Iterator);
            *Iterator = NULL;
            L->ItemsNo--;
        }
    }
}

Item ListInsert(List L,CItem  clone) {
    size_t i;
    if(!L || !clone)
        return NULL;;
    for(i=0;i<L->ArraySize && L->GenericArray[i];i++);

    if(i == L->ArraySize)  {
            /* need to increase size */
            if(ListGrow(L))
                return NULL;
    }
    L->GenericArray[i] = L->ctor(clone);
    L->ItemsNo++;
    return L->GenericArray[i];
}
size_t ListItemsCount(List L) {
    if(L)
        return L->ItemsNo;
    return (0);
}

size_t ListSpaceLeft(List L) {
    if(L)
        return L->ArraySize - L->ItemsNo;
    return 0;
}


Item const *  ListGetBeginIt(List L) {
    if(!L)
        return NULL;
    return L->GenericArray;
}


Item const *  ListGetEndIt(List L) {
    if(!L)
        return NULL;
    return L->GenericArray + L->ArraySize;
}
Item ListGet(List L,size_t index) {
    ItemIt begin = ListGetBeginIt(L);
    ItemIt end = ListGetEndIt(L);
    while(begin !=end) {
        if(*begin) {
            if(index == 0) {
                return *begin;
            }
            --index;
        }
        begin++;
    }
    return NULL;
}