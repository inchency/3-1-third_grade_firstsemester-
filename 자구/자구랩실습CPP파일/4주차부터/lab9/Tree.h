#ifndef __TREE_H__
#define __TREE_H__

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <iomanip>


using namespace std;

class Node {
private:
	char data;
	int prio; // 우선순위
	Node *left;
	Node *right;
	Node(char val)
	{
		data = val;
		prio = 4; 
		left = 0;
		right = 0;
	}
	friend class Tree;
};

class Tree {
private:
	Node *root;
public:
	Node *head;
	Tree() { root = 0; }
	void insert(char *text);
	void Operand(Node *ptr);
	void Operator(Node *ptr);
	void inorder(Node *ptr);
	void postorder(Node *ptr);
	void preorder(Node *ptr);
	int evalTree(Node *ptr);
	void displayInorder();
	void displayPostorder();
	void displayPreorder();
	void displayEvalTree();
};

#endif
