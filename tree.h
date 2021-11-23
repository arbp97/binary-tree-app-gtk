/* tree.h

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

#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdbool.h>

typedef struct Node
{
  int data;
  struct Node* right;
  struct Node* left;
} Node;

typedef struct Tree
{
  struct Node* root;
} Tree;

/******************************************************************************/

Tree* create_tree(int data);

Node* create_node(int data);

/*
  Utiliza la funcion search para insertar el dato que recibe
  en el arbol indicado, creando un nuevo nodo
*/
void insert (Tree * tree, int data);

/*
  Busca el lugar indicado para un nuevo nodo en el arbol, segun
  el valor del root indicado (node), y lo inserta
*/
void push (Node * node, Node * newNode);

/*
  Busca el dato indicado en el arbol
*/
bool search (Tree * tree, int data);

/******************************************************************************/

//Search Operations

void pre_order (Node * root);

void in_order (Node * root);

bool pre_order_search (Node * root, int data, bool * result);

void post_order (Node * root);

#endif //_TREE_H_
