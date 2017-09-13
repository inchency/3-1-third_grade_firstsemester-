/*********************************************
�̸� : �赿��
�й� : 20123339
ID : LAB4 STACK
date : 2016-03-30
*********************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include "Stack.h"
#define MAX_SIZE 100

Stack a(MAX_SIZE);

int compare(char b, char p);

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt�� ã�� �� �����ϴ�" << endl;
		return -1;
	}
	char buffer[MAX_SIZE];
	while (instream.getline(buffer, 80)) {  // ���پ� �а� �ִ� 80����Ʈ���� �о buffer�� ����
		int len = strlen(buffer);
		for (int k = 0; k < len; k++) {
			cout << buffer[k];
		}
		cout << "	";
		int i=0;
		if (len % 2 == 0) {// len�� ¦���̸�
			while (i < (len / 2)) {
				a.push(buffer[i]);
				i++;
			}
			while (buffer[i] != '\0') {   // buffer �߰����� �о���̰� ������
				if (compare(buffer[i], a.pop()) == 1) {
					cout << "not a palindrome" << endl;
					break;
				}
				else {
					i++;
					if (buffer[i] == NULL)  // ������ ���ؼ� ��ġ�ϸ�
						cout << "a palindrome" << endl;
				}
			}
		}
		else{ // len�� Ȧ���̸�
			while (i < (len / 2)) {
				a.push(buffer[i]);
				i++;
			}
			i++;  // ��� �� �� �� �� �پ����
			while (buffer[i] != '\0') { // buffer �߰�+1���� �о���̰� ������
				if (compare(buffer[i], a.pop()) == 1) {
					cout << "not a palindrome" << endl;
					break;
				}
				else {
					i++;
					if (buffer[i] == NULL) // ������ ���ؼ� ��ġ�ϸ�
						cout << "a palindrome" << endl;
				}
			}
		}
	}
	while (a.isEmpty())
		a.pop();

	//a.~Stack();
	return 0;
}

int compare(char b, char p) {
	if (b != p) {
		return 1;
	}
	else
		return 0;
}