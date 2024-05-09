#pragma once
/********************************************/
/*   list.h                                 */
/*   a dynamic  linked list with a header   */
/********************************************/


#ifndef _LIST_
#define _LIST_

#include "def.h"


/*** Definitions ***/

// Node
typedef struct node
{
	DATA key;
	struct node* next;
}NODE;

// List
typedef struct
{
	NODE head;
}LIST;


/*** Function prototypes ***/

BOOL L_init(LIST* pList);					// create new list

NODE* L_insert(NODE* pNode, DATA Value);	// add new node after *pNode

BOOL L_delete(NODE* pNode, void(*freeElem)(void*)); // erase node after *pNode

const NODE* L_find(const NODE* pNode, DATA Value, int(*compare)(const void* v1, const void* v2));
// return a pointer to the node 

BOOL L_free(LIST* pList, void(*freeElem)(void*)); // free list memory

int L_print(const LIST* pList, void(*print)(const void*)); // print the list content

#endif
