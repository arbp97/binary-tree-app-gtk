#ifndef _LIST_H_
#define _LIST_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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

List* create_list();

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

NodeList* create_node_list(Data data_ptr);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*
    Coloca el dato al final de la lista
   Pre: El nodo no debe estar agregado.
   Post:Agrega un nodo al final de la lista.
*/
void add_node_list(List** list, NodeList** node);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
   Elimina un nodo de la lista.
   Pre: El nodo debe haber sido creado.
   Post: Elimina el nodo pasado por parámetro.
*/
void delete_node_list(List** list, NodeList** node_list_ptr);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
   Elimina una lista
*/
void delete_list(List** list);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*  Devuelve el tamaño de la lista.
    Pre:La lista debe existir.
    Post:Devuelve un int con la cantidad de elementos de la lista.
*/
int length_of_list(List** list);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* Chequea si la lista esta vacia
   Pre: La lista debe existir.
   Post:Devuelve un booleano indicando si la lista está vacía o no.

*/
bool is_list_empty(List** list);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#endif // !_LIST_H_
