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


