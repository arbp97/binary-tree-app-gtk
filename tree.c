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

Tree *create_tree(int data)
{
	Tree *new = malloc(sizeof(Tree));
	new->root = create_node_tree(data);
	new->root->x_pos = ROOT_WIDGET_POS_X;
	new->root->y_pos = ROOT_WIDGET_POS_Y;

	return new;
}

NodeTree *create_node_tree(int data)
{
	NodeTree *new = malloc(sizeof(NodeTree));
	new->data = data;
	new->height = 0;
	new->left = NULL;
	new->right = NULL;

	char tmp[10];
	sprintf(tmp, "%i", data);
	new->widget = gtk_button_new_with_label(tmp);

	return new;
}

/******************************************************************************/

bool add_node_tree(Tree *tree, int data)
{
	NodeTree *new_node = create_node_tree(data);
	bool result;

	result = push_node_tree(&tree->root, new_node);

	tree->root->x_pos = ROOT_WIDGET_POS_X;
	tree->root->y_pos = ROOT_WIDGET_POS_Y;

	return result;
}

bool push_node_tree(NodeTree **root, NodeTree *new_node)
{
	bool result;

	/* If the new node is less than root node, then we
		put it to the left*/
	if (new_node->data < (*root)->data)
	{
		/* If the left node has not been set, then
			new node occupies it's place*/
		if (!(*root)->left)
		{
			(*root)->left = new_node;
			(*root)->left->height = 1 + fmax(height(new_node->left), height(new_node->right));

			result = true;
		}
		else
		{
			/* If the left node has been set, then we have to search
				again, in left node's sub tree */
			result = push_node_tree(&(*root)->left, new_node);
		}
	}
	/* If the new node is greater than root node, then we
		put it to the right*/
	else if (new_node->data > (*root)->data)
	{
		/* If the right node has not been set, then
			new node occupies it's place*/
		if (!(*root)->right)
		{
			(*root)->right = new_node;
			(*root)->right->height = 1 + fmax(height(new_node->left), height(new_node->right));

			result = true;
		}
		else
		{
			/* If the right node has been set, then we have to search
				again, in right node's sub tree */
			result = push_node_tree(&(*root)->right, new_node);
		}
	}
	else
	{
		/* throws an error and de-allocates the node
			(allocated in add_node_tree()) */
		printf("ERROR: Node was not pushed: Node already exists");
		free(new_node);
		new_node = NULL;
		result = false;
	}

	(*root)->height = 1 + fmax(height((*root)->left), height((*root)->right));

	balance(&(*root));

	return result;
}

/******************************************************************************/

void pre_order(NodeTree *root)
{
	/*
	Pre order algorithm:
		1. pass through root node
		2. go over the left sub-tree recursively
		3. go over the right sub-tree recursively
	*/

	/*->pass through root<-*/
	char tmp[16];
	sprintf(tmp, "[%i] ", root->data);
	console_log(tmp, TEXT_BUFFER_BUTTON_3, false);

	/*
	If the left node exists, then we go over the left
	sub-tree recursively
	*/
	if (root->left)
		pre_order(root->left);

	/*
	If the right node exists, then we go over the right
	sub-tree recursively
	*/
	if (root->right)
		pre_order(root->right);
}

void in_order(NodeTree *root)
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
	if (root->left)
		in_order(root->left);

	// pass through root
	char tmp[16];
	sprintf(tmp, "[%i] ", root->data);
	console_log(tmp, TEXT_BUFFER_BUTTON_4, false);

	/*
	If the right node exists, then we go over the right
	sub-tree recursively
	*/
	if (root->right)
		in_order(root->right);
}

void post_order(NodeTree *root)
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
	if (root->left)
		post_order(root->left);

	/*
	If the right node exists, then we go over the right
	sub-tree recursively
	*/
	if (root->right)
		post_order(root->right);

	/*
	pass through root
	*/
	char tmp[16];
	sprintf(tmp, "[%i] ", root->data);
	console_log(tmp, TEXT_BUFFER_BUTTON_5, false);
}

NodeTree *pre_order_search(NodeTree *root, int data, NodeTree *result)
{
	/* raises flag if the data is found */
	if (root->data == data)
		result = root;

	/*
	If the data hasn't been found in root and sub trees exist,
	then we go over them recursively
	*/
	if (root->left && !result)
		pre_order_search(root->left, data, result);

	if (root->right && !result)
		pre_order_search(root->right, data, result);

	return result;
}

void pre_order_show_tree(NodeTree *root, GtkWidget *viewport)
{
	adjust_tree_position(&root);

	gtk_fixed_put(GTK_FIXED(viewport),
				  root->widget, root->x_pos, root->y_pos);

	if (root->left)
		pre_order_show_tree(root->left, viewport);

	if (root->right)
		pre_order_show_tree(root->right, viewport);
}

Tree *find_tree_list(struct List *list, int tree_root)
{
	//node to go over the list
	NodeList *cursor = NULL;

	/*
	result is used to check the current cursor node's
	data, and to return it when found
	*/
	Tree *result = NULL;
	NodeTree *result_root = NULL;
	cursor = list->head;

	while (cursor != NULL)
	{
		result = (Tree *)cursor->data_ptr;
		result_root = result->root;

		if (result_root->data == tree_root)
		{
			/* set cursor to null to exit loop*/
			cursor = NULL;
		}
		else
		{
			cursor = cursor->next;
			/*
			set result to null in case it's
			the last loop and data was not found
			*/
			result = NULL;
		}
	}

	return result;
}

void post_order_delete(NodeTree *root)
{
	/*
	Deletes all nodes in a tree recursively, using
	post order algorithm
	*/

	if (root->left)
		post_order_delete(root->left);

	if (root->right)
		post_order_delete(root->right);

	free(root);
	root = NULL;
}

NodeTree *search_tree(Tree *tree, int data)
{
	NodeTree *result = NULL;

	if (!tree->root)
		console_log("ERROR: Empty tree", TEXT_BUFFER_BOTTOM_LEFT, true);
	else
		pre_order_search(tree->root, data, result);

	return result;
}

void delete_tree(Tree *tree)
{
	post_order_delete(tree->root);

	free(tree);
	tree = NULL;
}

int height(NodeTree *node)
{
	int height;

	if (node)
		height = node->height;
	else
		height = -1;

	return height;
}

int get_balance(NodeTree *node)
{
	int balance;

	if (node)
		balance = height(node->left) - height(node->right);
	else
		balance = 0;

	return balance;
}

void balance(NodeTree **node)
{
	int balance = get_balance(*node);

	if (balance > AVL_THRESHOLD)
	{
		if (get_balance((*node)->left) >= 0)
			*node = rotate_right(*node);
		else
			*node = rotate_left_right(*node);
	}
	else if (balance < -AVL_THRESHOLD)
	{
		if (get_balance((*node)->right) <= 0)
			*node = rotate_left(*node);
		else
			*node = rotate_right_left(*node);
	}
}

void adjust_tree_position(NodeTree **root)
{
	if ((*root)->x_pos == ROOT_WIDGET_POS_X &&
		(*root)->y_pos == ROOT_WIDGET_POS_Y)
	{
		/*
		special one time setting adding more space
		between the original node's sub trees, to
		partially overcome overlapping widgets.
		*/
		if ((*root)->left)
		{
			(*root)->left->x_pos = (*root)->x_pos - 150;
			(*root)->left->y_pos = (*root)->y_pos + 50;

			adjust_tree_position(&(*root)->left);
		}
		if ((*root)->right)
		{
			(*root)->right->x_pos = (*root)->x_pos + 150;
			(*root)->right->y_pos = (*root)->y_pos + 50;

			adjust_tree_position(&(*root)->right);
		}
	}
	else
	{
		if ((*root)->left)
		{
			(*root)->left->x_pos = (*root)->x_pos - 50;
			(*root)->left->y_pos = (*root)->y_pos + 50;

			adjust_tree_position(&(*root)->left);
		}

		if ((*root)->right)
		{
			(*root)->right->x_pos = (*root)->x_pos + 50;
			(*root)->right->y_pos = (*root)->y_pos + 50;

			adjust_tree_position(&(*root)->right);
		}
	}
}

NodeTree *rotate_right(NodeTree *node)
{
	NodeTree *temp = node->left;

	node->left = temp->right;
	temp->right = node;

	node->height = 1 + fmax(height(node->left), height(node->right));
	temp->height = 1 + fmax(height(temp->left), height(temp->right));

	return temp;
}

NodeTree *rotate_left(NodeTree *node)
{
	NodeTree *temp = node->right;

	node->right = temp->left;
	temp->left = node;

	node->height = 1 + fmax(height(node->left), height(node->right));
	temp->height = 1 + fmax(height(temp->left), height(temp->right));

	return temp;
}

NodeTree *rotate_right_left(NodeTree *node)
{
	NodeTree *temp;

	node->right = rotate_right(node->right);

	temp = rotate_left(node);
	return temp;
}

NodeTree *rotate_left_right(NodeTree *node)
{
	NodeTree *temp;
	node->left = rotate_left(node->left);
	temp = rotate_right(node);

	return temp;
}