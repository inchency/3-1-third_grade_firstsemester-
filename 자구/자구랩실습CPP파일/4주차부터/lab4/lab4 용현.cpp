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
		cout << "error : input.txt�� �� �� �����ϴ�" << endl;
	}
	palindrome(istreamFile);

	return 0;
}

void palindrome(fstream &instreamFile) {
	char buffer[100];
	int len, i;
	while (instreamFile.getline(buffer, 80)) {									//�� line�� ó����
		len = strlen(buffer);													//string�� ����, ���ڼ�.
		if ((len % 2) == 0) {													//¦��		
			i = 0;
			while (i < (len / 2)) {												//length�� �ݸ�ŭ PUSH. ��abccba�� �� ��� push a, push b, push c.
				Stack[top].push(buffer[i]);
				i++;
			}
			while (buffer[i] != '\0') {											// ���� buffer �� cba ������
				if (compare(buffer[i], Stack[top].pop())) break;				// if not SAME, then BREAK;
				i++;
				if (buffer[i] == NULL) cout << "PALINDROME" << endl;
			}
		}
		else if ((len % 2) != 0) {												// len Ȧ�� �̸�
			i = 0;
			while (i < (len / 2)) {												//length�� �ݸ�ŭ PUSH. ��abckcba���� ��� push a, push b, push c.
				Stack[top].push(buffer[i]);										// ���� buffer �� kcba ������
				i++;
			}
			i++;																// k�� �ǳ� �ڴ�.
			while (buffer[i] != '\0') {											// ���� buffer �� cba ������
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