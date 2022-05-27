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
typedef void * Item;
typedef const void * CItem;
typedef struct List * List;
typedef Item const * ItemIt;

/**
 * @brief creates a new list.
 * 
 * @param ctor item constructor.
 * @param dtor item destructor.
 * @param compar comparison function between two items, returns distance between two Items, 
 *        if their distance is 0, they are equal, conforming to stdlib compar.
 * @return List a new list.
 */
List newList(Item (*ctor)(CItem),
             void (*dtor)(Item),
             int (*compar)(CItem,CItem));
/**
 * @brief sorts the list using the compar function that was set in creating a new list if
 *        compar is NULL pointer, or uses given compar function if it's not NULL.
 *   
 * 
 * @param L the list.
 * @param compar alternative compar function.
 */
void SortList(List L,int (*compar)(Item,Item));

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
 * @return Item the returned item in list ( not a clone but a reference to the actual item).
 */
Item ListFind(List L,CItem clone);

/**
 * @brief looks for clone using used defined compar function in list and calls user defined destructor if found,
 *        does nothing otherwise.
 * 
 * @param L the list. 
 * @param clone a clone of an item to look for.
 */
void ListDelete(List L, CItem clone);

/**
 * @brief adds a clone item to the list.
 * 
 * @param L the list.
 * @param clone 
 * @return a reference to the item inserted to list ,or a NULL reference if insertion failed 
 *         ( example : growing the list or allocating new item.)
 */
Item ListInsert(List L, CItem clone);

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


Item const * ListGetBeginIt(List L);

Item const * ListGetEndIt(List L);


/**
 * @brief returns item located at index from 0 to ItemsCount.
 * 
 * @param L the List
 * @param index the index.
 * @return Item returned Item if index is valid, NULL otherwise.
 */
Item ListGet(List L,size_t index);
#ifdef __cplusplus
}
#endif
#endif