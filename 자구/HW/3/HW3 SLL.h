/*********************************************************
File Name : HW3 SLL.h
description : Node Ŭ����, List Ŭ������ ���� ������
	�ԷµǾ� �ִ�.
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
	friend class List; // List Ŭ�������� Node�� �̿��Ҽ� �ְ� ģ�� ������ ���־���.
};

class List {
private:
	Node *head;
public:
	List() { head = 0; }
	void append(string dataA);
	void display(); // �׳����
	void sort();
	int isEmpty();
	void Grade_display(char grade); // ���ϴ� ������ ���
	void Major_display(char *major); // ���ϴ� ������ ���
};
#endif