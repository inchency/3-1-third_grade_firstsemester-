#ifndef __STACK_H__
#define __STACK_H__
using namespace std;

class Stack{
public:
	private:
		char *arrayOfData;
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
};

class Queue {
private:
	char *arrayOfData;
	int size;
	int top;
	int front, rear;
	int count;
public:
	Queue(int size);
	int IsFullQ();
	int CIsFullQ(); // circle 큐 full확인
	int IsEmptyQ(); 
	int CIsEmptyQ(); // circle 큐 empty 확인
	void AddQ(char item); // 일반 큐 add
	char DeleteQ(); // 일반 큐 delete
	void EnQ(char item); // circle 큐 add
	char DeQ(); // circle 큐 delete
	void Print();
	void CPrint(); // circle 큐 print
};
#endif