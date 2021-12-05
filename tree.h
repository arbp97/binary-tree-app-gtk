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
#pragma once

#include "globals.h"

/*
  widget: representation of the node in the viewport
  x/y_pos: coordinates of the widget on the app
*/
typedef struct NodeTree
{
  /*
  height: stores the 'depth' of the node
  x_pos: horizontal position in viewport **
  y_pos: vertical position in viewport **

  **set when showing tree, using adjust_position
  */
  int data;
  int height;
  GtkWidget *widget;
  gint x_pos;
  gint y_pos;
  struct NodeTree *right;
  struct NodeTree *left;
} NodeTree;

typedef struct Tree
{
  struct NodeTree *root;
} Tree;

/******************************************************************************/

/*
  Creates a new tree, with the specified root
*/
Tree *create_tree(int data);

/*
  Creates a new independent node, with specified data
*/
NodeTree *create_node_tree(int data);

/*
  Uses search_tree function to insert the data into the
  specificed tree, creating a new node in the process
*/
bool add_node_tree(Tree *tree, int data);

/*
  Pushes the new node into the correct place in the tree:
    less than root (as in the root of any of the nodes),
    to the left, more than root, to the right
*/
bool push_node_tree(NodeTree **root, NodeTree *new_node);

/*
  Searches for the specified data in the tree. returns
  true if found
*/
NodeTree *search_tree(Tree *tree, int data);

/*
  Deletes specified tree and its children
*/
void delete_tree(Tree *tree);

/*
  Deletes all nodes from the root downwards, using
  post order algorithm
*/
void post_order_delete(NodeTree *root);

/*
  Searches for data inside a tree using pre order algorithm.
  Used by search_tree function
*/
NodeTree *pre_order_search(NodeTree *root, int data, NodeTree *result);

/*
  finds a tree with the same root
*/
Tree *find_tree_list(struct List *list, int tree_root);

/******************************************************************************/

//Search Operations

void pre_order(NodeTree *root);

void in_order(NodeTree *root);

void post_order(NodeTree *root);

/******************************************************************************/

// AVL Operations

// returns the height of a node
int height(NodeTree *node);

// returns the balance of a node in respect to its children
int get_balance(NodeTree *node);

/*
checks the balance of a node. if its unbalanced,
it will apply the necessary rotations to balance it.
*/
void balance(NodeTree **node);

NodeTree *rotate_right(NodeTree *node);

NodeTree *rotate_left(NodeTree *node);

NodeTree *rotate_right_left(NodeTree *node);

NodeTree *rotate_left_right(NodeTree *node);

#endif //_TREE_H_
