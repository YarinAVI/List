/*
 * @Author: Yarin Avisidris
 * @Date: 2022-05-18 23:20:54
 * @Last Modified by: Yarin Avisidris
 * @Last Modified time: 2022-05-19 00:05:52
 */

#ifndef __LIST__H_
#define __LIST__H_
#include <stddef.h>
#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @brief List type.
 * 
 */
typedef struct List * List;
/**
 * @brief List Item type.
 * 
 */
typedef void * LItem;
/**
 * @brief Constant List Type.
 * 
 */
typedef const void * CLItem;
/**
 * @brief List Item iterator
 * 
 */
typedef LItem const * LItemIt;

/**
 * @brief creates a new list.
 * 
 * @param ctor item constructor.
 * @param dtor item destructor.
 * @param compar comparison function between two items, returns distance between two LItems, 
 *        if their distance is 0, they are equal, conforming to stdlib compar.
 * @return List a new list.
 */
List newList(LItem (*ctor)(CLItem),
             void (*dtor)(LItem),
             int (*compar)(CLItem,CLItem));
/**
 * @brief sorts the list using the compar function that was set in creating a new list if
 *        compar is NULL pointer, or uses given compar function if it's not NULL.
 *   
 * 
 * @param L the list.
 * @param compar alternative compar function.
 */
void SortList(List L,int (*compar)(LItem,LItem));

/**
 * @brief Destroys the entire list by calling user defined destructor on each
 *        element, and destroys the list itself.
 * 
 * @param L the list.
 */
void ListDestroy(List L);

/**
 * @brief looks for clone in list, returns a pointer to it if found,
 *        or returns NULL otherwise.
 * 
 * @param L the list. 
 * @param clone a clone of an item to look for.
 * @return LItem the returned item in list ( not a clone but a reference to the actual item).
 */
LItem ListFind(List L,CLItem clone);

/**
 * @brief looks for clone using used defined compar function in list and calls user defined destructor if found,
 *        does nothing otherwise.
 * 
 * @param L the list. 
 * @param clone a clone of an item to look for.
 */
void ListDelete(List L, CLItem clone);

/**
 * @brief adds a clone item to the list.
 * 
 * @param L the list.
 * @param clone 
 * @return a reference to the item inserted to list ,or a NULL reference if insertion failed 
 *         ( example : growing the list or allocating new item.)
 */
LItem ListInsert(List L, CLItem clone);

/**
 * @brief returns how many item are set in the list.
 * 
 * @param L the list.
 * @return size_t number of items set.
 */
size_t ListItemsCount(List L);

/**
 * @brief returns how many items are not set ( how many slots are free in the list).
 * 
 * @param L the list.
 * @return size_t number of free slots in the set.
 */
size_t ListSpaceLeft(List L);


LItem const * ListGetBeginIt(List L);

LItem const * ListGetEndIt(List L);


/**
 * @brief returns item located at index from 0 to LItemsCount.
 * 
 * @param L the List
 * @param index the index.
 * @return LItem returned LItem if index is valid, NULL otherwise.
 */
LItem ListGet(List L,size_t index);

/**
 * @brief iteration macro in order for list.
 * 
 */
#define LIST_FOR_EACH(L,begin,end) for(begin = ListGetBeginIt(L),end = ListGetEndIt(L);begin!=end;begin++)

/**
 * @brief iteration macro reverse order for list.
 * 
 */
#define LIST_FOR_EACH_REVERSE(L,begin,end) for(begin = ListGetBeginIt(L),end = ListGetEndIt(L)-1;begin<=end;end--)

#ifdef __cplusplus
}
#endif
#endif