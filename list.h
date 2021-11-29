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

/* Definicion de tipos de datos */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* Puntero a la informacion del nodo de la lista*/
typedef void* Data;

/* Nodos que conforman la lista.
 * Contiene el dato y un puntero al siguiente nodo */
typedef struct NodeList
{
	Data data_ptr;
	struct NodeList* next;
	struct NodeList* prev; //previous
} NodeList;

/* Estructura de la lista.
 * Contiene dos punteros a nodos, uno al principio de la lista, y otro al final*/
typedef struct List
{
	struct NodeList* head;
	struct NodeList* tail;
} List;

/* Definicion de primitivas */
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
    Coloca el dato al final de la lista
   Pre: El nodo no debe estar agregado.
   Post:Agrega un nodo al final de la lista.
*/
void add_node_list(List* list, NodeList* node);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
   Elimina un nodo de la lista.
   Pre: El nodo debe haber sido creado.
   Post: Elimina el nodo pasado por parámetro.
*/
void delete_node_list(List* list, NodeList* node_list_ptr);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
   Elimina una lista
*/
void delete_list(List* list);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*  Devuelve el tamaño de la lista.
    Pre:La lista debe existir.
    Post:Devuelve un int con la cantidad de elementos de la lista.
*/
int length_of_list(List* list);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* Chequea si la lista esta vacia
   Pre: La lista debe existir.
   Post:Devuelve un booleano indicando si la lista está vacía o no.

*/
bool is_list_empty(List* list);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#endif // !_LIST_H_
