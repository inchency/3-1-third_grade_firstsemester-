#ifndef __BST_H__
#define __BST_H__

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <iomanip>


using namespace std;



class treeNode{
private:
	int value;
	treeNode *left, *right;
	treeNode(int val) : value(val), left(NULL), right(NULL) {}   //持失切

	friend class tree;
};



class tree{
private:
	void recursiveInsert(treeNode *&, int);
	void recursiveRemove(treeNode *&, int);
	void preorderRecursivePrint(treeNode*);
	void postorderRecursivePrint(treeNode*);
	void inorderRecursivePrint(treeNode*);
	void recursiveSearch(treeNode *&, int key);

public:
	treeNode *root;
	tree() : root(NULL) { }   //持失切
	void insert(int);
	void remove(int);
	void preorderPrint();
	void postorderPrint();
	void inorderPrint();
	void drawTree();
	void drawBSTree(treeNode *, int);
	void search(int key);
};


#endif
