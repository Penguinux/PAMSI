
#include"AVLtree.h"
#include<iostream>
using namespace std;
template<typename T>
int AVLTree<T>::height(Node* n) {
	int h = 0;
	if (n != NULL) {
		if (n->left == NULL && n->right == NULL) { // if the node is external ->height=0
			return 0;
		} else {
			int l_height = height(n->left);
			int r_height = height(n->right);
			if (l_height > r_height)
				h = l_height + 1;
			else
				h = r_height + 1;
			return h;
		}

	}

	else			// if the node is empty->height=-1 ( it's used to simplify a balance factor of the node)
		return -1;
}
template<typename T>
int AVLTree<T>::b_factor(Node* n) {
	int bf = height(n->left) - height(n->right); // if height of the right child is greater than the left child -> bfactor is negative
	return bf;
}
template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::rr_rotation(Node* n) {

	Node *temp;
	if (n->parent == NULL) {         //if n is the root
		temp = n->right;
		if (temp->left != NULL) {    // it's necessary to avoid problems with wrong parenting
			temp->left->parent = n;
		}

		n->right = temp->left;

		temp->left = n;

		root = temp;
		temp->parent = NULL;
		n->parent = temp;

	} else {
		temp = n->right;
		if (temp->left != NULL) {
			temp->left->parent = n;
		}
		n->right = temp->left;

		temp->left = n;
		if (temp->value > n->parent->value) { //if value of a temp is grater than it's parent than temp is it's right child
			n->parent->right = temp;
		} else {
			n->parent->left = temp;
		}
		temp->parent = n->parent;
		n->parent = temp;
	}

	return temp;
}
template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::ll_rotation(Node* n) {

	Node *temp;
	if (n->parent == NULL) {
		temp = n->left;
		if (temp->right != NULL) {
			temp->right->parent = n;
		}
		n->left = temp->right;

		temp->right = n;

		root = temp;
		temp->parent = NULL;
		n->parent = temp;

	} else {

		temp = n->left;
		if (temp->right != NULL) {
			temp->right->parent = n;
		}
		n->left = temp->right;

		temp->right = n;

		if (temp->value > n->parent->value) {
			n->parent->right = temp;
		} else {
			n->parent->left = temp;
		}

		temp->parent = n->parent;

		n->parent = temp;
	}

	return temp;
}
template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::rl_rotation(Node* n) {
	Node *temp;
	temp = n->right;
	n->right = ll_rotation(temp);
	return rr_rotation(n);
}
template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::lr_rotation(Node* n) {
	Node *temp;
	temp = n->left;
	n->left = rr_rotation(temp);
	return ll_rotation(n);
}
template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::maxrightnode(Node* n) {

	if (n->right == NULL)
		return n;
	else
		maxrightnode(n->right);
}
template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::balance(Node* n) {

	if (b_factor(n) > 1) {		//the Node is left heavy
		if (b_factor(n->left) > 0)	//Nodes left child is left heavy
			n = ll_rotation(n);
		else						// Nodes left child is right heavy
			n = lr_rotation(n);

	} else if (b_factor(n) < -1) {	//the Node is right heavy
		if (b_factor(n->right) > 0) {// Nodes right child is left heavy

			n = rl_rotation(n);
		} else						//Nodes right child is right heavy
			n = rr_rotation(n);
	}
	return n;

}
template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::balance_r(Node* n) {
	n = balance(n);
	if (n->parent == NULL) {

		return n;
	} else {
		balance_r(n->parent);
		return n;
	}
}
template<typename T>
void AVLTree<T>::add(Node* n, T x) {

	if (root->value == 0)			// if root is empty
		root->value = x;
	else {

		if (x < n->value) {			// if adding value is less than nodes value

			if (n->left == NULL) {	// if nodes left child is empty create there a new node with value x
				Node *leaf = new Node;
				leaf->value = x;
				leaf->parent = n;
				n->left = leaf;

			} else {
				add(n->left, x);

				n = balance(n);

			}
		} else if (x > n->value) {	// if adding value is greater than nodes value
			if (n->right == NULL) {	// if nodes right child is empty create there a new node with value x
				Node *leaf = new Node;
				leaf->value = x;
				leaf->parent = n;
				n->right = leaf;
			} else {

				add(n->right, x);

				n = balance(n);

			}
		}
		else
			cout<<endl<<"This value already exist in the tree"<<endl;

	}

}
template<typename T>
void AVLTree<T>::remove(Node* n, T x) {
if(n==NULL)
	cout<<endl<<"This value does not exist"<<endl;
else{
	if (x > n->value) {
		remove(n->right, x);

	} else if (x < n->value) {
		remove(n->left, x);
	} else {
		if (n->parent == NULL) { // if the node is the root
			if (n->left == NULL && n->right == NULL) { // if the root is the only node
				root->value = 0;
			} else if (n->left != NULL && n->right == NULL) { // if the root has only a left child

				root->value = n->left->value;

				remove(root->left, root->value);
				root = balance_r(root);
			} else if (n->left == NULL && n->right != NULL) { // if the root has only a right child

				root->value = n->right->value;

				remove(root->right, root->right->value);
				root = balance_r(root);
			}

			else if (n->left != NULL && n->right != NULL) { // if the root has both children
				Node *temp;
				temp = maxrightnode(n->left);

				n->value = temp->value;

				remove(n->left, n->value);
				root = balance_r(root);

			}
		} else if (n->left == NULL && n->right == NULL) { // if the node is external

			if (x > n->parent->value) {		// if value of nodes parent is less than x

				n->parent->right = NULL;
			} else if (x < n->parent->value) { // if value of nodes parent is greater than x

				n->parent->left = NULL;
			}

			else if (n->parent->left != NULL && n->parent->left->value == x) { // only when removing root or a node with two children
				n->parent->left = NULL;
			} else if (n->parent->right != NULL
					&& n->parent->right->value == x) {

				n->parent->right = NULL;
			}

			n->parent = balance_r(n->parent);
			delete n;
		}

		else if (n->left == NULL && n->right != NULL) { // if the node has only a right  child


			if (x < n->parent->value) {		// if value of nodes parent is greater than x
				n->parent->left = n->right;
				n->right->parent = n->parent;

			} else if (x > n->parent->value) {	// if value of nodes parent is less than x

				n->parent->right = n->right;

				n->right->parent = n->parent;

			}

			else if (n->parent->left != NULL && n->parent->left->value == x) {  // only when removing root or a node with two children
				n->parent->left = n->right;
				n->right->parent = n->parent;
			} else if (n->parent->right != NULL
					&& n->parent->right->value == x) {
				n->parent->right = n->right;

				n->right->parent = n->parent;
			}
			n->parent = balance_r(n->parent);
			delete n;
		} else if (n->right == NULL && n->left != NULL) { // if the node has only a left child
			if (x < n->parent->value) {			// if value of nodes parent is greater than x
				n->parent->left = n->left;
				n->left->parent = n->parent;

			} else if (x > n->parent->value) {	// if value of nodes parent is less than x

				n->parent->right = n->left;

				n->left->parent = n->parent;

			} else if (n->parent->left != NULL && n->parent->left->value == x) { // only when removing root or a node with two children
				n->parent->left = n->left;
				n->left->parent = n->parent;
			} else if (n->parent->right != NULL
					&& n->parent->right->value == x) {

				n->parent->right = n->left;
				n->left->parent = n->parent;
			}
			n->parent = balance_r(n->parent);
			delete n;
		}

		else if (n->left != NULL && n->right != NULL) { // if the node has both children
			Node *temp;
			temp = maxrightnode(n->left);

			n->value = temp->value;

			remove(n->left, n->value);
			n = balance_r(n);

		}

	}
}
}
template<typename T>
void AVLTree<T>::display(Node *n, int level)

{

	if (n != NULL)

	{

		display(n->right, level + 1);
		cout << "        \n";
		if (n->value == root->value)

			cout << "Root -> ";

		for (int i = 0; i < level && n->value != root->value; i++)

			cout << "        ";

		cout << n->value;
		if (n->parent != NULL) {
			cout << ' ' << n->parent->value;
		}
		cout << '(' << b_factor(n) << ')' << '[' << height(n) << ']';
		if (n->left == NULL)
			cout << '0';
		else
			cout << n->left->value;
		if (n->right == NULL)
			cout << '0';
		else
			cout << n->right->value;

		display(n->left, level + 1);

	}

}
template<typename T>
void AVLTree<T>::clear(Node* n){
	if(n->value != 0){
		remove(n, n->value);
		clear(root);
	}

}
template<typename T>
void AVLTree<T>::preorder(Node* n) {
	if (n != NULL) {
		cout << n->value << ' ';
		preorder(n->left);
		preorder(n->right);
	}
}
template<typename T>
void AVLTree<T>::postorder(Node* n) {
	if (n != NULL) {
		postorder(n->left);
		postorder(n->right);
		cout << n->value << ' ';
	}
}
template<typename T>
void AVLTree<T>::inorder(Node* n) {

	if (n != NULL) {
		inorder(n->left);
		cout << n->value << ' ';
		inorder(n->right);
	}

}

