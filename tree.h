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
