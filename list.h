/* list.h

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef _LIST_H_
#define _LIST_H_
#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "events.h"

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* Used to store data inside a node*/
typedef void* Data;

/*
   The node that conforms the list.
   data_ptr: stores a void pointer to the data.
   next: the following node in the list.
   prev: the previous node.
*/
typedef struct NodeList
{
	Data data_ptr;
	struct NodeList* next;
	struct NodeList* prev;
} NodeList;

/*
   head: first node.
   tail: last node.
*/
typedef struct List
{
	struct NodeList* head;
	struct NodeList* tail;
} List;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
   Returns an empty list
*/
List* create_list();

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
   Returns a new node with specified data
*/
NodeList* create_node_list(Data data_ptr);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
   Puts the received node at the end of the list.
*/
void add_node_list(List* list, NodeList* node);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
   Removes the specified node from a list and deletes it.
*/
void delete_node_list(List* list, NodeList* node_list_ptr);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
   Deletes a list and all of its nodes.
*/
void delete_list(List* list);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
   Returns the length of the list.
*/
int length_of_list(List* list);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
   Checks if list is empty.
*/
bool is_list_empty(List* list);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#endif // !_LIST_H_
