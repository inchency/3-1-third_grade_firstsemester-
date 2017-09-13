/*********************************************************
File Name : HW3 SLL.h
description : Node 클래스, List 클래스에 대한 정보가
	입력되어 있다.
*********************************************************/


#ifndef __SLL_H__
#define __SLL_H__

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

class Node {
private:
	string data;
	Node *next;
	friend class List; // List 클래스에서 Node를 이용할수 있게 친구 선언을 해주었다.
};

class List {
private:
	Node *head;
public:
	List() { head = 0; }
	void append(string dataA);
	void display(); // 그냥출력
	void sort();
	int isEmpty();
	void Grade_display(char grade); // 원하는 학점만 출력
	void Major_display(char *major); // 원하는 전공만 출력
};
#endif