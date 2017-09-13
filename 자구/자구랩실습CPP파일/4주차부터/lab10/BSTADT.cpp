#include "BST.h"

void tree::recursiveInsert(treeNode *&node, int val)

{

	if (node == NULL)

		node = new treeNode(val);   //탐색하고 있는 노드가 NULL이면 새로 만든다(삽입)



	else if (val > node->value)

		recursiveInsert(node->right, val);   //삽입할 값이 노드의 값보다 크면 오른쪽 Child를 탐색



	else if (val < node->value)

		recursiveInsert(node->left, val);   //삽입할 값이 노드의 값보다 작으면 왼쪽 Child를 탐색

}



void tree::recursiveRemove(treeNode *& node, int val)

{

	treeNode *removal = new treeNode(0);



	if (node == NULL) {
		cout << "Not Found" << endl;
		return;      //찾지못했을 경우 리턴해서 함수종료
	}

	else if (val > node->value)

		recursiveRemove(node->right, val);   //삭제할 값이 노드의 값보다 크면 오른쪽 Child를 탐색

	else if (val < node->value)

		recursiveRemove(node->left, val);   //삭제할 값이 노드의 값보다 작으면 왼쪽 Child를 탐색



	else //삭제할 노드를 찾았음(이제 3가지 경우로 나눌수 있다)

	{

		if (node->left == NULL && node->right == NULL) //경우 1: 노드의 Child가 없을때

		{

			delete node;

			node = NULL;

		}



		else if (node->left == NULL)   //경우 2-1: 노드의 Child가 오른쪽 하나일 때

		{

			removal = node;

			node = node->right;

			delete removal;

		}

		else if (node->right == NULL)   //경우 2-2: 노드의 Child가 왼쪽 하나일 때

		{

			removal = node;

			node = node->left;

			delete removal;

		}

		else                     //경우 3: 노드의 Child가 두개일 때

		{

			removal = node->right;

			while (removal->left != NULL)   //노드의 오른쪽 Subtree에서 최소값을 가진 노드를 찾는다.

				removal = removal->left;



			int minVal = removal->value;   //최소값노드의 값을 백업해둔다.

			recursiveRemove(root, minVal);   //최소값노드를 삭제한다

			node->value = minVal;         //백업한 최소값을 "실제 삭제된 값을 가진 노드"의 값에 덮어쓴다

		}

	}



}



void tree::preorderRecursivePrint(treeNode *node)

{

	if (node != NULL)

	{

		cout << node->value << endl;      //먼저 당장의 node를 출력한다.

		preorderRecursivePrint(node->left);   //Left Child가 없을때까지 최대한 왼쪽으로 탐색한다.

		preorderRecursivePrint(node->right);//그 다음 Right Child를 탐색한다.

	}

}



void tree::inorderRecursivePrint(treeNode *node)

{

	if (node != NULL)

	{

		inorderRecursivePrint(node->left); //Left Child가 없을때까지 최대한 왼쪽으로 탐색한다.

		cout << node->value << endl;      //출력한다.   

		inorderRecursivePrint(node->right);//그 다음 Right Child를 탐색한다.

	}

}



void tree::postorderRecursivePrint(treeNode *node)

{

	if (node != NULL)

	{

		postorderRecursivePrint(node->left); //Left Child가 없을때까지 최대한 왼쪽으로 탐색한다.

		postorderRecursivePrint(node->right);//그 다음 Right Child를 탐색한다.

		cout << node->value << endl;       //출력한다.   

	}

}

void tree::drawTree() {
	drawBSTree(root, 1);
}

void tree::drawBSTree(treeNode *p, int level) {
	if (p != 0 && level <= 7) {
		drawBSTree(p->right, level + 1);
		for (int i = 1; i <= (level - 1); i++)
			cout << "   ";
		cout << setw(2) << p->value;
		if (p->left != 0 && p->right != 0)
			cout << "<" << endl;
		else if (p->right != 0)
			cout << "↗" << endl;
		else if (p->left != 0)
			cout << "↘" << endl;
		else
			cout << endl;
		drawBSTree(p->left, level + 1);
	}
}

void tree::recursiveSearch(treeNode *& ptr, int key) {
	if (ptr == NULL)
		cout << "NOT Found" << endl;
	else {
		if (key == ptr->value)
			cout << "Find " << key << endl;
		else if (key > ptr->value)
			recursiveSearch(ptr->right, key);
		else if (key < ptr->value)
			recursiveSearch(ptr->left, key);
	}
}


///////////////////WRAPPING FUNCTION(함수들을 main에서 편하게 사용할수 있게 WRAP해줍니다)//////////////////////



void tree::insert(int val)

{

	recursiveInsert(root, val);

}



void tree::remove(int val)

{

	recursiveRemove(root, val);

}



void tree::preorderPrint()

{

	cout << "PREORDER" << endl;

	preorderRecursivePrint(root);

}



void tree::inorderPrint()

{

	cout << "INORDER" << endl;

	inorderRecursivePrint(root);

}



void tree::postorderPrint()

{

	cout << "POSTORDER" << endl;

	postorderRecursivePrint(root);

}

void tree::search(int key) {
	recursiveSearch(root, key);
}