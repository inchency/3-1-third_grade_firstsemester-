/*******************************************************************************
* FileName : LAB3.cpp
* Author : Hong, Yong Hyun, 20123432
*
*													Organiztion : Kookmin. Univ.
*													Date : 2016. 03. 16.
*******************************************************************************/

#include<iostream>
#include<fstream>
#include<cstring>
#define Max_Size 100

using namespace std;

class Element {
private:
	char p;
public:
	void push(char a);
	char pop();
	void stackFull();
	char stackEmpty();
};
Element Stack[Max_Size];
int top = -1;

void Element::push(char a) {
	if (top >= Max_Size-1) {
		stackFull();
	}
	Stack[top++].p = a;
}

char Element::pop() {
	if (top == -1) {
		return stackEmpty();
	}
	return Stack[--top].p;
}
void Element::stackFull() {
	cout << "Stack is Full!" << endl;
}

char Element::stackEmpty() {
	cout << "Stack is empty!" << endl;
	return NULL;
}

void palindrome(fstream &instreamFile);
int compare(char buffer, char pop);



int main() {
	fstream istreamFile("input.txt");
	if (!istreamFile.is_open()) {
		cout << "error : input.txt를 열 수 없습니다" << endl;
	}
	palindrome(istreamFile);

	return 0;
}

void palindrome(fstream &instreamFile) {
	char buffer[100];
	int len, i;
	while (instreamFile.getline(buffer, 80)) {									//한 line씩 처리함
		len = strlen(buffer);													//string의 길이, 글자수.
		if ((len % 2) == 0) {													//짝수		
			i = 0;
			while (i < (len / 2)) {												//length의 반만큼 PUSH. ‘abccba’ 의 경우 push a, push b, push c.
				Stack[top].push(buffer[i]);
				i++;
			}
			while (buffer[i] != '\0') {											// 이젠 buffer 에 cba 남았음
				if (compare(buffer[i], Stack[top].pop())) break;				// if not SAME, then BREAK;
				i++;
				if (buffer[i] == NULL) cout << "PALINDROME" << endl;
			}
		}
		else if ((len % 2) != 0) {												// len 홀수 이면
			i = 0;
			while (i < (len / 2)) {												//length의 반만큼 PUSH. ‘abckcba’의 경우 push a, push b, push c.
				Stack[top].push(buffer[i]);										// 이젠 buffer 에 kcba 남았음
				i++;
			}
			i++;																// k를 건너 뛴다.
			while (buffer[i] != '\0') {											// 이젠 buffer 에 cba 남았음
				if (compare(buffer[i], Stack[top].pop())) break;				// if not SAME, then BREAK;
				i++;
				if (buffer[i] == NULL) cout << "PALINDROME" << endl;
			}
		}
	}
}

int compare(char buffer, char pop) {
	if (buffer != pop) {
		cout << "NOT PALINDROME" << endl;
		return 1;
	}
	return 0;
}