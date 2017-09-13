#include <iostream>
#include "Stack.h"

Stack::Stack(int size) :size(size) { // 데이터 초기화
	arrayOfData = new int[size];
	top = -1;
}

Stack::~Stack() {
	delete arrayOfData;
}

bool Stack::isFull() const {
	if (top == size - 1)
		return true;
	else
		return false;
}

bool Stack::isEmpty() const {
	if (top == -1)
		return true;
	else
		return false;
}

void Stack::push(int value) {
	if (isFull() == true)
		cout << "Stack is Full" << endl;
	else {
		++top;
		arrayOfData[top] = value;
	}
}

int Stack::pop() {
	if (isEmpty() == true)
		cout << "Stack is Empty" << endl;
	else 
		return arrayOfData[top--];
}

void Stack::print() const {
	if (isEmpty() == true)
		cout << "Stack is Empty" << endl;
	for (int i = 0; i <= top; i++) {
		cout << arrayOfData[i] << " ";
	}
	cout << endl;
}

Queue::Queue(int size) : size(size) { // 데이터 초기화
	arrayOfData = new char[size];
	top = -1;
	front = -1;
	rear = -1;
	count = 0;
}

int Queue::IsFullQ() {
	if (rear == size - 1)
		return 1;
	else
		return false;
}

int Queue::IsEmptyQ() {
	if (front == rear)
		return 1;
	else
		return 0;
}

void Queue::AddQ(char item) {
	/* queue에 item을 삽입 */
	if (IsFullQ())
		cout << "Queue Full" << endl;
	else
		arrayOfData[++rear] = item;
}

char Queue::DeleteQ() {
	char item;
	if (IsEmptyQ()) {
		cout << "Queue Empty" << endl;
		return;
	}
	else {
		item = arrayOfData[++front];
		return item;
	}
}

void Queue::EnQ(char item) {
	if (IsFullQ() && count == size)
		cout << "Queue Full" << endl;
	else {
		rear = (rear + 1) % size;
		arrayOfData[rear] = item;
		count++;
		top++;
	}
}

char Queue::DeQ() {
	char item;
	if (IsEmptyQ() && count == 0) {
		cout << "Queue Empty" << endl;
		return;
	}
	else {
		front = (front + 1) % size;
		item = arrayOfData[front];
		count--;
		top--;
	}
}
void Queue::print(){
	if (IsEmptyQ())
		cout << "Queue Empty" << endl;
	else {
		for (int i = front + 1; i <= rear; i++) 
			cout << arrayOfData[i];
	}
}



