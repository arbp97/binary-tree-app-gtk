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
	Tree *new;
	new->root = create_node(data);

	return new;
}

Node *create_node(int data)
{
	Node *new;
	new->data = data;
	new->left = NULL;
	new->right = NULL;

	return new;
}

/******************************************************************************/

void insert(Tree *tree, int data)
{
	Node *new_node = create_node(data);
	push(tree->root, new_node);
}

void push(Node *node, Node *new_node)
{
	/* Si el nuevo nodo es menor que root (node), debemos
		 colocarlo a la izquierda */
	if (new_node->data < node->data)
	{
		// Si el hijo izquierdo no ha sido seteado...
		if (!node->left)
		{
			// el nuevo nodo ocupa su lugar
			node->left = new_node;
		}
		else
		{
			/*
					Caso contrario, llamamos recursivamente a la funcion
					para buscar en el subarbol correspondiente
				*/
			push(node->left, new_node);
		}
	}
	/*
			Si el nuevo nodo es mayor que root, se debe colocar a la derecha
		*/
	else if (new_node->data > node->data)
	{
		// si el hijo derecho no ha sido seteado
		if (!node->right)
		{
			// se setea con el nuevo nodo
			node->right = new_node;
		}
		else
		{
			push(node->right, new_node);
		}
	}
	else
	{
		/*std::cout << "Node not created: " << new_node->data
			<< " Node already exists..." << std::endl;*/
	}
}

/******************************************************************************/

void pre_order(Node *root)
{
	/*
		Recorrido en preOrden:
			1. visita la raiz
			2. recorre subarbol izquierdo en preOrden
			3. recorre subarbol derecho en preOrden
	*/

	/*std::cout << "[" << root->data << "], ";*/

	/*
		si el hijo izquierdo del root existe, entonces
		se recorre el subarbol izquierdo recursivamente
	*/
	if (root->left)
		pre_order(root->left);

	/*
		si el hijo derecho del root existe, entonces
		se recorre el subarbol derecho recursivamente
	*/
	if (root->right)
		pre_order(root->right);
}

void in_order(Node *root)
{
	/*
		Recorrido en Orden:
			1. recorre subarbol izquierdo en simetrico
			2. visita la raiz
			3. recorre subarbol derecho en simetrico
	*/

	// si existe hijo izquierdo de root, entramos en su subarbol
	if (root->left)
		in_order(root->left);

	// si ya no existe un hijo izquierdo, se imprime el root actual,
	// que seria el hijo izquierdo del root anterior
	/*std::cout << "[" << root->data << "], ";*/

	// luego de verificar el hijo izquierdo, se pasa por el derecho
	// hasta llegar al fondo
	if (root->right)
		in_order(root->right);
}

bool pre_order_search(Node *root, int data, bool *result)
{
	/* Si se encuentra el dato, se levanta el flag */
	if (root->data == data)
		*result = true;

	/*
		Si el dato aun no se ha encontrado, sigue recorriendo los
		subarboles
	*/
	if (root->left && !(*result))
		pre_order_search(root->left, data, result);

	if (root->right && !(*result))
		pre_order_search(root->right, data, result);

	return result;
}

void post_order(Node *root)
{
	/*
		Recorrido en postOrden:
			1.recorre subarbol izquierdo en orden final
			2. recorre subarbol derecho en orden final
			3. visita la raiz
	*/

	// si existe hijo izquierdo de root, entramos en su subarbol
	if (root->left)
		post_order(root->left);

	// luego de verificar el hijo izquierdo, se pasa por el derecho
	if (root->right)
		post_order(root->right);

	/*
		cuando agotamos las posibilidades, llegando al fondo del arbol,
		se imprime la raiz
	*/
	/*std::cout << "[" << root->data << "], ";*/
}

bool search(Tree *tree, int data)
{
	bool result = false;

	if (!tree->root)
		/*std::cout << "\nError: empty tree" << '\n';*/

		pre_order_search(tree->root, data, &result);

	return result;
}
