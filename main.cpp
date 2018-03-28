#include"AVLtree.cpp"
#include<iostream>
#include<cstdlib>
using namespace std;

void menu() {
	cout << "---------- AVL TREE ----------" << endl;
	cout << " 1. Menu" << endl;
	cout << " 2. Insert  element" << endl;
	cout << " 3. Remove element" << endl;
	cout << " 4. Display" << endl;
	cout << " 5. Advanced display" << endl;
	cout << " 6. Clear" << endl;
	cout << " 7. Height of the tree" << endl;
	cout << " 8. Preorder traversal" << endl;
	cout << " 9. Postorder traversal" << endl;
	cout << "10. Inorder traversal" << endl;
	cout << "11. Exit" << endl;
}
int main() {
	int choice;
	int value;

	AVLTree<int> avl;
	menu();
	while (1) {

		cin >> choice;

		switch (choice) {
		case 1:
			menu();
			break;
		case 2:

			cin >> value;

			avl.add(avl.root, value);

			break;
		case 3:

			cin >> value;

			avl.remove(avl.root, value);

			break;
		case 4:
			cout << endl;
			avl.display(avl.root, 0);
			cout << endl;
			break;
		case 5:
			cout << endl;
			avl.display_adv(avl.root, 0);
			cout << endl;

			break;
		case 6:
			avl.clear(avl.root);
			break;
		case 7:
			avl.treeheight();
			break;
		case 8:
			cout << endl;
			avl.preorder(avl.root);
			cout << endl;

			break;
		case 9:
			cout << endl;
			avl.postorder(avl.root);
			cout << endl;
			break;

		case 10:
			cout << endl;
			avl.inorder(avl.root);
			cout << endl;
			break;
		case 11:
			exit(1);
			break;
		default:
			cout << endl << "Wrong choice" << endl;
		}
	}

	return 0;
}
