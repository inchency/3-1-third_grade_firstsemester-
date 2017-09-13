#include "BST.h"

void tree::recursiveInsert(treeNode *&node, int val)

{

	if (node == NULL)

		node = new treeNode(val);   //Ž���ϰ� �ִ� ��尡 NULL�̸� ���� �����(����)



	else if (val > node->value)

		recursiveInsert(node->right, val);   //������ ���� ����� ������ ũ�� ������ Child�� Ž��



	else if (val < node->value)

		recursiveInsert(node->left, val);   //������ ���� ����� ������ ������ ���� Child�� Ž��

}



void tree::recursiveRemove(treeNode *& node, int val)

{

	treeNode *removal = new treeNode(0);



	if (node == NULL) {
		cout << "Not Found" << endl;
		return;      //ã�������� ��� �����ؼ� �Լ�����
	}

	else if (val > node->value)

		recursiveRemove(node->right, val);   //������ ���� ����� ������ ũ�� ������ Child�� Ž��

	else if (val < node->value)

		recursiveRemove(node->left, val);   //������ ���� ����� ������ ������ ���� Child�� Ž��



	else //������ ��带 ã����(���� 3���� ���� ������ �ִ�)

	{

		if (node->left == NULL && node->right == NULL) //��� 1: ����� Child�� ������

		{

			delete node;

			node = NULL;

		}



		else if (node->left == NULL)   //��� 2-1: ����� Child�� ������ �ϳ��� ��

		{

			removal = node;

			node = node->right;

			delete removal;

		}

		else if (node->right == NULL)   //��� 2-2: ����� Child�� ���� �ϳ��� ��

		{

			removal = node;

			node = node->left;

			delete removal;

		}

		else                     //��� 3: ����� Child�� �ΰ��� ��

		{

			removal = node->right;

			while (removal->left != NULL)   //����� ������ Subtree���� �ּҰ��� ���� ��带 ã�´�.

				removal = removal->left;



			int minVal = removal->value;   //�ּҰ������ ���� ����صд�.

			recursiveRemove(root, minVal);   //�ּҰ���带 �����Ѵ�

			node->value = minVal;         //����� �ּҰ��� "���� ������ ���� ���� ���"�� ���� �����

		}

	}



}



void tree::preorderRecursivePrint(treeNode *node)

{

	if (node != NULL)

	{

		cout << node->value << endl;      //���� ������ node�� ����Ѵ�.

		preorderRecursivePrint(node->left);   //Left Child�� ���������� �ִ��� �������� Ž���Ѵ�.

		preorderRecursivePrint(node->right);//�� ���� Right Child�� Ž���Ѵ�.

	}

}



void tree::inorderRecursivePrint(treeNode *node)

{

	if (node != NULL)

	{

		inorderRecursivePrint(node->left); //Left Child�� ���������� �ִ��� �������� Ž���Ѵ�.

		cout << node->value << endl;      //����Ѵ�.   

		inorderRecursivePrint(node->right);//�� ���� Right Child�� Ž���Ѵ�.

	}

}



void tree::postorderRecursivePrint(treeNode *node)

{

	if (node != NULL)

	{

		postorderRecursivePrint(node->left); //Left Child�� ���������� �ִ��� �������� Ž���Ѵ�.

		postorderRecursivePrint(node->right);//�� ���� Right Child�� Ž���Ѵ�.

		cout << node->value << endl;       //����Ѵ�.   

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
			cout << "��" << endl;
		else if (p->left != 0)
			cout << "��" << endl;
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


///////////////////WRAPPING FUNCTION(�Լ����� main���� ���ϰ� ����Ҽ� �ְ� WRAP���ݴϴ�)//////////////////////



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