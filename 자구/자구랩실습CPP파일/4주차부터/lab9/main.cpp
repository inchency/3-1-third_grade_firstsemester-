#include "Tree.h"

void main() {
	string menu;
	Tree tree;
	char data[20] = { 0 };

	cout << "Input : ";
		cin >> data;
		tree.insert(data);
		tree.displayInorder();
		cout << endl;
		tree.displayPostorder();
		cout << endl;
		tree.displayPreorder();
		cout << endl;
		cout << "Evaluation : ";
		tree.displayEvalTree();
}