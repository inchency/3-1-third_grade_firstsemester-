#ifndef __STACK_H__
#define __STACK_H__
using namespace std;

class Stack{
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
	int pop();
	void print() const;
};

class Queue {
private:
	char *arrayOfData;
	int size;
	int top;
	int front, rear;
	bool flag;
public:
	Queue(int size);
	int IsFullQ();
	int IsEmptyQ();
	void AddQ(char item);
	char DeleteQ();
	void EnQ(char item);
	char DeQ();
	void print() const;
}
	



};
#endif