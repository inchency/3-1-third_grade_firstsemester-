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
	int CIsFullQ(); // circle ť fullȮ��
	int IsEmptyQ(); 
	int CIsEmptyQ(); // circle ť empty Ȯ��
	void AddQ(char item); // �Ϲ� ť add
	char DeleteQ(); // �Ϲ� ť delete
	void EnQ(char item); // circle ť add
	char DeQ(); // circle ť delete
	void Print();
	void CPrint(); // circle ť print
};
#endif