/*********************************************
이름 : 김동훈
학번 : 20123339
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
		cout << "input.txt를 찾을 수 없습니다" << endl;
		return -1;
	}
	char buffer[MAX_SIZE];
	while (instream.getline(buffer, 80)) {  // 한줄씩 읽고 최대 80바이트까지 읽어서 buffer에 넣음
		int len = strlen(buffer);
		for (int k = 0; k < len; k++) {
			cout << buffer[k];
		}
		cout << "	";
		int i=0;
		if (len % 2 == 0) {// len이 짝수이면
			while (i < (len / 2)) {
				a.push(buffer[i]);
				i++;
			}
			while (buffer[i] != '\0') {   // buffer 중간부터 읽어들이고 끝까지
				if (compare(buffer[i], a.pop()) == 1) {
					cout << "not a palindrome" << endl;
					break;
				}
				else {
					i++;
					if (buffer[i] == NULL)  // 끝까지 비교해서 일치하면
						cout << "a palindrome" << endl;
				}
			}
		}
		else{ // len이 홀수이면
			while (i < (len / 2)) {
				a.push(buffer[i]);
				i++;
			}
			i++;  // 가운데 값 한 번 더 뛰어넘음
			while (buffer[i] != '\0') { // buffer 중간+1부터 읽어들이고 끝까지
				if (compare(buffer[i], a.pop()) == 1) {
					cout << "not a palindrome" << endl;
					break;
				}
				else {
					i++;
					if (buffer[i] == NULL) // 끝까지 비교해서 일치하면
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