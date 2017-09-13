#ifndef __INFIX_H__
#define __INFIX_H__
using namespace std;

class Stack {
public:
private:
	int *arrayOfData;
	int top;
	const int size;
public:
	Stack(int size);
	virtual~Stack();
	bool isFull() const;
	bool isEmpty() const;
	void push(int value);
	char pop();
	void print() const;
	int get_top();
	int set_stacktop();
};

#endif