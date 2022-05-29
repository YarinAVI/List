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
    LItem * GenericArray;
    LItem * InternalIterator;
    size_t ArraySize; /* how many pointers to items */
    size_t LItemsNo; /* how many set items*/
    LItem (*ctor)(CLItem);
    void (*dtor)(LItem);
    int (*compar)(CLItem,CLItem);
};
#define base_len 2

List newList(LItem (*ctor)(CLItem),
             void (*dtor)(LItem),
             int (*compar)(CLItem,CLItem))  {
                 List  ret = malloc(sizeof(struct List));
                 /**
                  * @note handle later..
                  * 
                  */
                 if(!ret) {return NULL;}
                 
                 ret->ArraySize = base_len;
                 ret->GenericArray = calloc(ret->ArraySize,sizeof(LItem));
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

                 ret->LItemsNo  = 0;
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
    LItem * temp;
    size_t i = L->ArraySize;
    L->ArraySize *=2;
    temp = realloc(L->GenericArray,L->ArraySize * sizeof(LItem));
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

LItem ListFind(List L,CLItem clone) {
    LItem * Iterator;
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

void ListDelete(List L,CLItem clone) {
    LItem * Iterator;
    size_t i;
    if(!L)
        return;
     Iterator = L->GenericArray;
    for(i=0;i<L->ArraySize;i++,Iterator++) {
        if(*(Iterator) && L->compar(*Iterator,clone) == 0) {
            L->dtor(*Iterator);
            *Iterator = NULL;
            L->LItemsNo--;
        }
    }
}

LItem ListInsert(List L,CLItem  clone) {
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
    L->LItemsNo++;
    return L->GenericArray[i];
}
size_t ListItemsCount(List L) {
    if(L)
        return L->LItemsNo;
    return (0);
}

size_t ListSpaceLeft(List L) {
    if(L)
        return L->ArraySize - L->LItemsNo;
    return 0;
}


LItem const *  ListGetBeginIt(List L) {
    if(!L)
        return NULL;
    return L->GenericArray;
}


LItem const *  ListGetEndIt(List L) {
    if(!L)
        return NULL;
    return L->GenericArray + L->ArraySize;
}
LItem ListGet(List L,size_t index) {
    LItemIt begin = ListGetBeginIt(L);
    LItemIt end = ListGetEndIt(L);
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