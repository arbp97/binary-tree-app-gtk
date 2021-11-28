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

/* Implementacion de primitivas*/
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

List* create_list()
{
	List* new = malloc(sizeof(List));
	new->head = NULL;
	new->tail = NULL;

	return new;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

NodeList* create_node_list(Data data_ptr)
{
	NodeList* new = malloc(sizeof(NodeList));
	new->data_ptr = data_ptr;
	new->next = NULL;
	new->prev = NULL;

	return new;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void add_node_list(List** list, NodeList** node)
{
	if(is_list_empty(&(*list)))
	{
		/* Si la lista se encuentra vacia, entonces se agrega el nuevo nodo
		 * como cabeza y cola al mismo tiempo. */

		(*list)->head = (*node);
		(*list)->tail = (*node);
		if((*list)->head == (*list)->tail) printf("checking");
	}
	else
	{	//MAYBE THE BUG IS IN THESE CHECKS
		if((*list)->head == (*list)->tail)
		{
			/* si la cola y la cabeza son iguales, hay solo un objeto en la lista.
			 * Se agrega el nuevo nodo al final de la lista, y se acomodan las
			 * referencias next y prev: el anterior de la cola es la cabeza, y el
			 * siguiente de la cabeza es la cola. */

			(*list)->tail = (*node);
			(*list)->tail->prev = (*list)->head;
			(*list)->head->next = (*list)->tail;
		}
		else
		{
			/* Si la cabeza y la cola no son iguales, existe mas de un objeto.
			 * Primero se agrega la referencia al objeto anterior al nuevo nodo,
			 * luego se agrega el nuevo nodo al final de la lista, y por ultimo
			 * se mueve la referencia a la cola de la lista a este nuevo objeto. */

			 (*node)->prev = (*list)->tail;
			 (*list)->tail->next = (*node);
			 (*list)->tail = (*node);
		}
	}
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool is_list_empty(List** list)
{
	bool value = true;

	if((*list)->head != NULL)
	{
		value = false;
	}

	return value;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

int length_of_list(List** list)
{
	NodeList* temp = create_node_list(NULL);
    temp = (*list)->head;
    int length=0;

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

void delete_node_list(List** list, NodeList** node_list_ptr)
{
	/* Primero se verifica si la lista no esta vacia y el puntero es valido */
	if((!is_list_empty(&(*list)) && ((*node_list_ptr) != NULL)))
	{
		if(((*node_list_ptr) == (*list)->head) && ((*list)->head == (*list)->tail))
		{
			/* Si el nodo a eliminar es el unico nodo de la lista,
			 * entonces se igualan a NULL la cabecera y cola de la misma
			*/

			(*list)->head = NULL;
			(*list)->tail = NULL;
		}
		else if((*node_list_ptr) == (*list)->head)
		{
			/* Si el nodo a eliminar es el primero de la lista, se asigna como
			 * primero de la lista al proximo de este. Hecho esto, se limpia
			 * el puntero al previo nodo de la nueva cabeza (ya que ahora es
			 * el primero) */

			(*list)->head = (*list)->head->next;
			(*list)->head->prev = NULL;
		}
		else if((*node_list_ptr) == (*list)->tail)
		{
			/* Si el nodo a eliminar es la cola de la lista, entonces se asigna
			como cola al nodo anterior al actual */

			(*list)->tail = (*list)->tail->prev;
			(*list)->tail->next = NULL;
		}
		else
		{
			/* Si el nodo a eliminar no es el primero, entonces se busca el nodo
			 * siguiente del ANTERIOR del nodo a eliminar, y se le asigna como
			 * proximo al nodo SIGUIENTE de dicho nodo a eliminar. */

			(*node_list_ptr)->prev->next = (*node_list_ptr)->next;
		}

		free((*node_list_ptr));
		(*node_list_ptr) = NULL;
	}
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void delete_list(List** list)
{
	NodeList* cursor = create_node_list(NULL); //nodo para recorrer la lista

	/*nodo auxiliar para conseguir el proximo nodo
	luego de borrar el cursor*/
	NodeList* auxPtr = create_node_list(NULL);
	cursor = (*list)->head;

	while (cursor != NULL)
	{
		auxPtr = cursor->next;

		delete_node_list(&(*list), &cursor);

		cursor = auxPtr;
	}

	free(cursor);
	free(auxPtr);
	free((*list));
	cursor = NULL;
	auxPtr = NULL;
	(*list) = NULL;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
