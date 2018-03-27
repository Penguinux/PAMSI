#ifndef AVLTREE_H_
#define AVLTREE_H_
#include<iostream>

template<class T>
class AVLTree {
public:
	struct Node {
		T value;			// node's value
		Node* parent;		// pointer at node's parent
		Node* left;			// pointer at node's left child
		Node* right;		// pointer at node's right child
		Node() :
				value(), parent(NULL), left(NULL), right(NULL) {// constructor
		}
	};
public:
	Node *root = new Node;  // declaration of root-basic node of the avl tree
	int treeheight = height(root); // stores height of the tree

	void add(Node* n, T x); // adds the node  to the avl tree

	void remove(Node* n, T x); // removes the  node from the avl tree

	void display(Node *ptr, int level); // displays the avl tree

	void clear(Node* n);  // removes entire tree

	void preorder(Node* n);		// prints  preorder traversal of the avl tree

	void postorder(Node* n); // prints  postorder traversal of the avl tree

	void inorder(Node* n); // prints  inorder traversal of the avl tree
private:
	int height(Node* n);	// returns height of the node

	int b_factor(Node* n); // returns balance factor of the node

	Node *rr_rotation(Node* n); // performs right-right rotation of the node

	Node *ll_rotation(Node* n);	// performs left-left rotation of the node

	Node *rl_rotation(Node* n);	// performs right-left rotation of the node

	Node *lr_rotation(Node* n);	// performs left-right rotation of the node

	Node* maxrightnode(Node* n); // finds successor of the node

	Node *balance(Node* n);  // balances the node

	Node *balance_r(Node* n); //balances the node and all nodes from this node to the root(used after removing)

};

#endif /* AVLTREE_H_ */
