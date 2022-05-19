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
typedef struct List * List;
/**
 * @brief creates a new list.
 * 
 * @param ctor item constructor.
 * @param dtor item destructor.
 * @param compar comparison function between two items.
 * @return List a new list.
 */
List newList(Item (*ctor)(Item),
             void (*dtor)(Item),
             int (*compar)(Item,Item));
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
Item ListFind(List L,Item clone);

/**
 * @brief looks for clone using used defined compar function in list and calls user defined destructor if found,
 *        does nothing otherwise.
 * 
 * @param L the list. 
 * @param clone a clone of an item to look for.
 */
void ListDelete(List L, Item clone);

/**
 * @brief adds a clone item to the list.
 * 
 * @param L the list.
 * @param clone 
 */
void ListInsert(List L, Item clone);

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
size_t ListSpaceLeft(List L) {

}
/**
 * @brief resets the internal List iterator to the first Item
 *        that is set in the list, and returns that Item,
 *        otherwise returns NULL pointer.
 * 
 * @param L the list.
 * @return Item first set item.
 */
Item ListItRewind(List L);

/**
 * @brief advances the internal List iterator to the next item that is set
 *        if there is none then returns NULL or in any other case.
 * 
 * @param L the list. 
 * @return Item the next set item.
 */
Item ListGetNextIt(List L);
#ifdef __cplusplus
}
#endif
#endif