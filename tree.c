/* tree.c

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

#include "tree.h"

Tree* create_tree(int data)
{
	Tree *new = malloc(sizeof(new));
	new->root = create_node_tree(data);

	return new;
}

NodeTree* create_node_tree(int data)
{
	NodeTree* new = malloc(sizeof(new));
	new->data = data;
	new->left = NULL;
	new->right = NULL;

	return new;
}

/******************************************************************************/

void add_node_tree(Tree** tree, int data)
{
	NodeTree* new_node = create_node_tree(data);

	push_node_tree(&(*tree)->root, &new_node);
}

void push_node_tree(NodeTree** root, NodeTree** new_node)
{
	/* If the new node is less than root node, then we
		put it to the left*/
	if ((*new_node)->data < (*root)->data)
	{
		/* If the left node has not been set, then
			new node occupies it's place*/
		if (!(*root)->left)
		{
			(*root)->left = (*new_node);
		}
		else
		{
			/* If the left node has been set, then we have to search
				again, in left node's sub tree */
			push_node_tree(&(*root)->left, &(*new_node));
		}
	}
	/* If the new node is greater than root node, then we
		put it to the right*/
	else if ((*new_node)->data > (*root)->data)
	{
		/* If the right node has not been set, then
			new node occupies it's place*/
		if (!(*root)->right)
		{
			(*root)->right = (*new_node);
		}
		else
		{
			/* If the right node has been set, then we have to search
				again, in right node's sub tree */
			push_node_tree(&(*root)->right, &(*new_node));
		}
	}
	else
	{
		console_log("ERROR: Tree was not created: Node already exists");
	}
}

/******************************************************************************/

void pre_order(NodeTree** root)
{
	/*
	Pre order algorithm:
		1. pass through root node
		2. go over the left sub-tree recursively
		3. go over the right sub-tree recursively
	*/

	/*->pass through root<-*/
	char tmp[16];
	sprintf(tmp,"[%i] ",(*root)->data);
	console_log(tmp);

	/*
	If the left node exists, then we go over the left
	sub-tree recursively
	*/
	if ((*root)->left)
		pre_order(&(*root)->left);

	/*
	If the right node exists, then we go over the right
	sub-tree recursively
	*/
	if ((*root)->right)
		pre_order(&(*root)->right);
}

void in_order(NodeTree** root)
{
	/*
	In order algorithm:
		1. go over the left sub-tree recursively
		2. pass through root node
		3. go over the right sub-tree recursively
	*/

	/*
	If the left node exists, then we go over the left
	sub-tree recursively
	*/
	if ((*root)->left)
		in_order(&(*root)->left);

	// pass through root
	char tmp[16];
	sprintf(tmp,"[%i] ",(*root)->data);
	console_log(tmp);

	/*
	If the right node exists, then we go over the right
	sub-tree recursively
	*/
	if ((*root)->right)
		in_order(&(*root)->right);
}

void post_order(NodeTree** root)
{
	/*
	Post order algorithm:
		1. go over the left sub-tree recursively
		2. go over the right sub-tree recursively
		3. pass through root node
	*/

	/*
	If the left node exists, then we go over the left
	sub-tree recursively
	*/
	if ((*root)->left)
		post_order(&(*root)->left);

	/*
	If the right node exists, then we go over the right
	sub-tree recursively
	*/
	if ((*root)->right)
		post_order(&(*root)->right);

	/*
	pass through root
	*/
	char tmp[16];
	sprintf(tmp,"[%i] ",(*root)->data);
	console_log(tmp);
}

bool pre_order_search(NodeTree** root, int data, bool* result)
{
	/* raises flag if the data is found */
	if ((*root)->data == data)
		*result = true;

	/*
	If the data hasn't been found in root and sub trees exist,
	then we go over them recursively
	*/
	if ((*root)->left && !*result)
		pre_order_search(&(*root)->left, data, result);

	if ((*root)->right && !*result)
		pre_order_search(&(*root)->right, data, result);

	return result;
}

void post_order_delete(NodeTree** root)
{
	/*
	Deletes all nodes in a tree recursively, using
	post order algorithm
	*/

	if ((*root)->left)
		post_order_delete(&(*root)->left);

	if ((*root)->right)
		post_order_delete(&(*root)->right);

	free((*root));
	(*root) = NULL;
}

bool search_tree(Tree** tree, int data)
{
	bool result = false;

	//if (!(*tree)->root)
		/*std::cout << "\nError: empty tree" << '\n';*/
	pre_order_search(&(*tree)->root, data, &result);

	return result;
}

void delete_tree(Tree** tree)
{
	post_order_delete(&(*tree)->root);

	free((*tree));
	(*tree) = NULL;
}