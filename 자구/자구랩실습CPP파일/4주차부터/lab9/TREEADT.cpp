#include "Tree.h"

//char prec[4][2] = { '*', 2, '/', 2, '+', 1, '-', 1 };
char prec[5][2] = { '^', 3 , '*' , 2 , '/' , 2, '+', 1, '-', 1 };

void Tree::insert(char *op)
{
	Node *p;
	for (int i = 0; i < strlen(op); i++)
	{
		p = new Node(op[i]);
		for (int j = 0; j < 5; j++)
		{
			if (p->data == prec[j][0])
				p->prio = prec[j][1];
		}
		if (p->prio == 4)
			Operand(p); // 숫자일때
		else
			Operator(p); // 사칙연산 및 ^ 일때
	}
}

void Tree::Operand(Node *ptr){ // 숫자일 때
	if (root == NULL)
		root = ptr;
	else
	{
		Node *p = root;
		while (p->right != NULL)
			p = p->right;
		p->right = ptr;
	}
}

void Tree::Operator(Node *ptr) {
	if (root->prio >= ptr->prio){
		ptr->left = root;
		root = ptr;
	}
	else{
		ptr->left = root->right;
		root->right = ptr;
	}
}

void Tree::inorder(Node *ptr){
	if (ptr) {
		inorder(ptr->left);
		cout << ptr->data;
		inorder(ptr->right);
	}
}

void Tree::postorder(Node *ptr){
	if (ptr) {
		postorder(ptr->left);
		postorder(ptr->right);
		cout << ptr->data;
	}
}

void Tree::preorder(Node *ptr){
	if (ptr) {
		cout << ptr->data;
		preorder(ptr->left);
		preorder(ptr->right);
	}
}

int Tree::evalTree(Node *ptr){
	int value = 0, left, right;
	if (ptr != NULL) {
		if (ptr->data >= '0' && ptr->data <= '9')
			value = ptr->data - '0';
		else {
			left = evalTree(ptr->left);
			right = evalTree(ptr->right);
			switch (ptr->data) {
			case '+':
				value = left + right;
				break;
			case '-':
				value = left - right;
				break;
			case '*':
				value = left * right;
				break;
			case '/':
				value = left / right;
				break;
			case '^':
				if (right == 1)
					value = left;
				else {
					for (int i = 0; i < right; i++)
						value = value * left;
				}
			}
		}
	}
	else
		cout << "Empty tree" << endl;

	return value;
}

void Tree::displayInorder(){
	cout << "Inorder : ";
	inorder(root);
}

void Tree::displayPostorder() {
	cout << "Postorder : ";
	postorder(root);
}

void Tree :: displayPreorder() {
	cout << "Preorder : ";
	preorder(root);
}

void Tree::displayEvalTree() {
	cout << evalTree(root);
}