/* 
 * File:   LinkedList.c
 * Author: Dylan Yong
 *
 * Created on May 7, 2018, 3:17 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "BOARD.h"
/*
 * 
 */

/**
 * @file
 * This file provided a doubly-linked list implementation for storing strings (NULL-terminated
 * character arrays.
 * The list implementation relies on a chain metaphor: a list is merely a sequence of links
 * (ListItems) and there is no separate construct to represent the entire list, each ListItem in it
 * does that implicitly.
 * ListItems can store pointers to strings, but the strings themselves must be stored somewhere else.
 * This list supports NULL pointers as well.
 */

/*
 * This function starts a new linked list. Given an allocated pointer to data it will return a
 * pointer for a malloc()ed ListItem struct. If malloc() fails for any reason, then this function
 * returns NULL otherwise it should return a pointer to this new list item. data can be NULL.
 *
 * @param data The data to be stored in the first ListItem in this new list. Can be any valid 
 *             pointer value.
 * @return A pointer to the malloc()'d ListItem. May be NULL if an error occured.
 */
ListItem *LinkedListNew(char *data)
{
    int size = sizeof (ListItem);
    ListItem *newList = malloc(size);
    if (newList == NULL) {
        return NULL;
    } else {
        newList->nextItem = NULL;
        newList->previousItem = NULL;
        newList->data = data;
        return newList;
    }
}

/**
 * This function will remove a list item from the linked list and free() the memory that the
 * ListItem struct was using. It doesn't, however, free() the data pointer and instead returns it
 * so that the calling code can manage it.  If passed a pointer to NULL, LinkedListRemove() should
 * return NULL to signal an error.
 *
 * @param item The ListItem to remove from the list.
 * @return The data pointer from the removed item. May be NULL.
 */
char *LinkedListRemove(ListItem *item)
{
    //NULL check
    if (item == NULL) {
        return NULL;
    }
    char *store;
    store = item->data;
    //if this is the first item in a sequence
    if (item->nextItem != NULL && item->previousItem == NULL) {
        item->nextItem->previousItem = item->previousItem;
        free(item);
        //if this is an item in the middle of a sequence
    } else if (item->nextItem != NULL) {
        item->nextItem->previousItem = item->previousItem;
        item->previousItem->nextItem = item->nextItem;
        free(item);
        //if this is a lone item
    } else if (item->nextItem == NULL && item->previousItem == NULL) {
        free(item);
        //if this is an item at the end of a sequence
    } else if (item->nextItem == NULL && item->previousItem != NULL) {
        item->previousItem->nextItem = NULL;
        free(item);
        //item = item->previousItem;
    }
    return store;
}

/**
 * This function returns the total size of the linked list. This means that even if it is passed a
 * ListItem that is not at the head of the list, it should still return the total number of
 * ListItems in the list. A NULL argument will result in 0 being returned.
 *
 * @param list An item in the list to be sized.
 * @return The number of ListItems in the list (0 if `list` was NULL).
 */
int LinkedListSize(ListItem *list)
{
    int counter = 0;
    if (list == NULL) {
        return NULL;
    }
    list = LinkedListGetFirst(list);
    //printf("%s\n", list->data); //Get first is the issue
    while (list->nextItem != NULL) {
        list = list->nextItem;
        counter++;
    }
    ++counter;
    return counter;
}

/**
 * This function returns the head of a list given some element in the list. If it is passed NULL,
 * it will just return NULL. If given the head of the list it will just return the pointer to the
 * head anyways for consistency.
 *
 * @param list An element in a list.
 * @return The first element in the list. Or NULL if provided an invalid list.
 */
ListItem *LinkedListGetFirst(ListItem *list)
{
    //ListItem *tempList;
    if (list == NULL) {
        return NULL;
    }
    //printf("initial value %s\n", list->data);

    //TESTING
    if (list->previousItem != NULL) {
        //printf("previous initial value %s\n", list->previousItem->data); //this is a fundamental issue
    }

    while (list->previousItem != NULL) {
        list = list->previousItem;
        //printf("sort value %s\n", list->data);
    }
    //printf("return value %s\n", list->data);
    return list;
}

/**
 * This function allocates a new ListItem containing data and inserts it into the list directly
 * after item. It rearranges the pointers of other elements in the list to make this happen. If
 * passed a NULL item, InsertAfter() should still create a new ListItem, just with no previousItem.
 * It returns NULL if it can't malloc() a new ListItem, otherwise it returns a pointer to the new
 * item. The data parameter is also allowed to be NULL.
 *
 * @param item The ListItem that will be before the newly-created ListItem.
 * @param data The data the new ListItem will point to.
 * @return A pointer to the newly-malloc()'d ListItem.
 */
ListItem *LinkedListCreateAfter(ListItem *item, char *data)
{
    ListItem *nextList = malloc(sizeof (ListItem));
    if (nextList == NULL) {
        return NULL;
        //if this is at the end of a sequence
    } else if (item->nextItem == NULL) {
        nextList->data = data;
        nextList->previousItem = item;
        nextList->nextItem = NULL;
        item->nextItem = nextList;
        //item=item->nextItem;

        //printf("1\n");

        return item;

    }//if this is in the middle of a sequence
    else if (item->nextItem != NULL) {
        nextList->data = data;
        nextList->previousItem = item;
        nextList->nextItem = item->nextItem;

        item->nextItem->previousItem = nextList;
        item->nextItem = nextList;

        //printf("3\n");

        return nextList;
    }
    //if this is the first in a sequence
    nextList->data = data;
    nextList->previousItem = NULL;
    nextList->nextItem = NULL;

    //printf("4\n");

    return nextList;
}

/**
 * LinkedListSwapData() switches the data pointers of the two provided ListItems. This is most
 * useful when trying to reorder ListItems but when you want to preserve their location. It is used
 * within LinkedListSort() for swapping items, but probably isn't too useful otherwise. This
 * function should return STANDARD_ERROR if either arguments are NULL, otherwise it should return
 * SUCCESS. If one or both of the data pointers are NULL in the given ListItems, it still does
 * perform the swap and returns SUCCESS.
 *
 * @param firstItem One of the items whose data will be swapped.
 * @param secondItem Another item whose data will be swapped.
 * @return SUCCESS if the swap worked or STANDARD_ERROR if it failed.
 */
int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem)
{
    ListItem *tempList2 = malloc(sizeof (ListItem));
    if (firstItem == NULL || secondItem == NULL) {
        return STANDARD_ERROR;
    } else {
        tempList2->data = firstItem->data;
        firstItem->data = secondItem->data;
        secondItem->data = tempList2->data;
        return SUCCESS;
    }
}

/**
 * LinkedListSort() performs a selection sort on list to sort the elements into descending order. It
 * makes no guarantees of the addresses of the list items after sorting, so any ListItem referenced
 * before a call to LinkedListSort() and after may contain different data as only the data pointers
 * for the ListItems in the list are swapped. This function sorts the strings in ascending order
 * first by size (with NULL data pointers counting as 0-length strings) and then alphabetically
 * ascending order. So the list [dog, cat, duck, goat, NULL] will be sorted to [NULL, cat, dog,
 * duck, goat]. LinkedListSort() returns SUCCESS if sorting was possible. If passed a NULL pointer
 * for either argument, it will do nothing and return STANDARD_ERROR.
 *
 * @param list Any element in the list to sort.
 * @return SUCCESS if successful or STANDARD_ERROR is passed NULL pointers.
 */
int LinkedListSort(ListItem *list)
{
    int strLen1, strLen2;
    char *strCmp1, *strCmp2;
    ListItem *firstHolder;
    int i, listSize, clear, nullCounter;
    char *temp;
    //LinkedListPrint(list);
    listSize = LinkedListSize(list);
    //printf("list size %i\n", listSize);
    nullCounter = 0;

    //NULL CATCHER
    list = LinkedListGetFirst(list);
    firstHolder = LinkedListGetFirst(list);

    while (list != NULL) {
        //if this is data is null and there is nothing after it
        if (list->data == NULL && list->nextItem == NULL) {
            LinkedListRemove(list);
            nullCounter++;
            --listSize;
            list = list->previousItem->previousItem;
            break;
            //list = list->previousItem->previousItem;
        }//if the data is null and there is something after it
        else if (list->data == NULL && list->nextItem->data != NULL) {
            LinkedListRemove(list);
            nullCounter++;
            --listSize;
        }//if thedata is null and the next data is null
        else if (list->data == NULL && list->nextItem->data == NULL) {
            while (list->data == NULL) {
                LinkedListRemove(list);
                nullCounter++;
                --listSize;
                list = list->nextItem;

            }
        }
        list = list->nextItem;
    }
    //listSize = LinkedListSize(list);

    //NULL REMOVAL TEST
    //LinkedListPrint(list);

    //LENGTH SORT
    list = firstHolder;
    while (1) {

        clear = 0;
        i = 0;
        list = LinkedListGetFirst(list);
        listSize = listSize - 1;
        for (i = 0; i < listSize; i++) {
            strLen1 = strlen(list->data);
            strLen2 = strlen(list->nextItem->data);
            //printf("%d %d\n", strLen1, strLen2);
            //compare string length
            if (strLen1 > strLen2) {
                if (list == NULL || list->nextItem == NULL) {
                    return STANDARD_ERROR;
                }
                temp = list->data;
                list->data = list->nextItem->data;
                list->nextItem->data = temp;
                clear = 1;
            }
            list = list->nextItem;

        }
        if (clear == 0) {
            break;
        }

    }
    //LinkedListPrint(list);
    listSize = LinkedListSize(list);

    //ALPHA SORT
    while (1) {
        clear = 0;
        list = LinkedListGetFirst(list);
        for (i = 0; i < (listSize - 1); i++) {
            strCmp1 = list->data;
            strCmp2 = list->nextItem->data;
            strLen1 = strlen(list->data);
            strLen2 = strlen(list->nextItem->data);
            //printf("%d %d\n", strLen1, strLen2);
            //if string lengths equal then compare letters
            if (strLen1 == strLen2) {
                if (list == NULL || list->nextItem == NULL) {
                    return STANDARD_ERROR;
                }
                if (strcmp(strCmp1, strCmp2) > 0) {
                    temp = list->data;
                    list->data = list->nextItem->data;
                    list->nextItem->data = temp;
                    clear = 1;
                }
            }
            list = list->nextItem;
        }
        if (clear == 0) {
            break;
        }
    }

    //NULL reentry
    ListItem *nullAdder;
    //char *tempNext, *tempPrevious;
    list = LinkedListGetFirst(list);
    //place the nulls we removed at the beginning of the function 
    //into the beginning of the ListItem
    for (i = 0; i < nullCounter; i++) {
        nullAdder = malloc(sizeof (ListItem));
        nullAdder->previousItem = NULL;
        nullAdder->nextItem = list;
        nullAdder->data = NULL;
        list->previousItem = nullAdder;
        list = list->previousItem;

    }

    return SUCCESS;
}

/**
 * LinkedListPrint() prints out the complete list to stdout. This function prints out the given
 * list, starting at the head if the provided pointer is not the head of the list, like "[STRING1,
 * STRING2, ... ]" If LinkedListPrint() is called with a NULL list it does nothing, returning
 * STANDARD_ERROR. If passed a valid pointer, prints the list and returns SUCCESS.
 *
 * @param list Any element in the list to print.
 * @return SUCCESS or STANDARD_ERROR if passed NULL pointers.
 */
int LinkedListPrint(ListItem * list)
{
    int listLength, i;
    if (list == NULL) {
        return STANDARD_ERROR;
    }
    listLength = LinkedListSize(list);
    list = LinkedListGetFirst(list);
    //printf("List size = %i [ ", listLength); //Get size is the issue (testing)
    printf("[");
    for (i = 0; i < (listLength - 1); i++) {
        printf("%s ", list->data);
        list = list->nextItem;
    }
    //list=list->nextItem;
    printf("%s]\n", list->data);
    return SUCCESS;
}


