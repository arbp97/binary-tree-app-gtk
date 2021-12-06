/* list.c

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

#include "list.h"

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

List *create_list()
{
	List *new = (List *)malloc(sizeof(List));
	new->head = NULL;
	new->tail = NULL;

	return new;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

NodeList *create_node_list(Data data_ptr)
{
	NodeList *new = (NodeList *)malloc(sizeof(NodeList));
	new->data_ptr = data_ptr;
	new->next = NULL;
	new->prev = NULL;

	return new;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void add_node_list(List *list, NodeList *node)
{
	if (is_list_empty(list))
	{
		/*
			If the list is empty, the new node is added as head and tail,
			because it'll be the only node in the list, duh.
		*/
		list->head = node;
		list->tail = list->head;
	}
	else
	{
		if (list->head == list->tail)
		{
			/*
				If there is only one element, then the new node is added at the
				end (tail) of the list, and we need to update the references
				in head/tail to reflect that.
			*/
			list->tail = node;
			list->tail->prev = list->head;
			list->head->next = list->tail;
		}
		else
		{
			/*
				If there is more than one element, things change a bit:
				set the previous reference in the new node to point to the old tail,
				set the next reference in this tail to point to our new tail.
			*/
			node->prev = list->tail;
			list->tail->next = node;
			list->tail = node;
		}
	}
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool is_list_empty(List *list)
{
	bool value = true;

	if (list->head != NULL)
	{
		value = false;
	}

	return value;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

int length_of_list(List *list)
{
	NodeList *temp = create_node_list(NULL);
	temp = list->head;
	int length = 0;

	while (temp != NULL)
	{
		length++;
		temp = temp->next;
	}

	free(temp);
	temp = NULL;

	return length;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void delete_node_list(List *list, NodeList *node_list_ptr)
{
	/*
		the list has to have at least one element, and the node
		has to be initialized.
	*/
	if ((!is_list_empty(list) && (node_list_ptr != NULL)))
	{
		if ((node_list_ptr == list->head) && (list->head == list->tail))
		{
			/*
				if there is only one element, we just change the references
				to point to NULL instead.
			*/
			list->head = NULL;
			list->tail = NULL;
		}
		else if (node_list_ptr == list->head)
		{
			/*
				If the node is the head, then the next node is set to be
				the new head, and we just delete the reference to it.
			*/
			list->head = list->head->next;
			list->head->prev = NULL;
		}
		else if (node_list_ptr == list->tail)
		{
			/*
				If the node is the last element of the list, we
				assign the previous node as the new tail.
			*/
			list->tail = list->tail->prev;
			list->tail->next = NULL;
		}
		else
		{
			/*
				If the node is in the middle of the list, we change the
				reference of the previous node's next pointer, and point it
				to the next reference of the deleted node.
			*/
			node_list_ptr->prev->next = node_list_ptr->next;
		}

		free(node_list_ptr);
		node_list_ptr = NULL;
	}
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void delete_list(List *list)
{
	NodeList *cursor = create_node_list(NULL);
	// auxPtr: used to get the next node after deleting the current cursor.
	NodeList *auxPtr = create_node_list(NULL);
	cursor = list->head;

	while (cursor != NULL)
	{
		auxPtr = cursor->next;

		delete_node_list(list, cursor);

		cursor = auxPtr;
	}

	free(cursor);
	free(auxPtr);
	free(list);
	cursor = NULL;
	auxPtr = NULL;
	list = NULL;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
