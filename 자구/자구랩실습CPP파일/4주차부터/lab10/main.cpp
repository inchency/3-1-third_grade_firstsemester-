#include "BST.h"

void main() {
	string menu;
	tree tree;
	int num;

	while (1) {
		cin >> menu;
		if (menu == "Insert") {
			cin >> num;
			tree.insert(num);
		}
		else if (menu == "Delete") {
			cin >> num;
			tree.remove(num);
		}
		else if (menu == "Print") {
			tree.drawTree();
		}
		else if (menu == "Search") {
			cin >> num;
			tree.search(num);
		}
		else if (menu == "Quit") {
			exit(1);
		}
		else
			cout << "다시 입력해 주세요!!" << endl;
	}
}
// Insert 30 Insert 40 Insert 50 Insert 20 Insert 10