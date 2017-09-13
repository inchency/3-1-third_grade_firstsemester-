#ifndef __SLL_H__
#define __SLL_H__

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

class Node {
public:
	//Node(int data);
	int data;
	string data2;
	char name[10];
	Node *next;
	friend class List; // List Ŭ�������� Node�� �̿��Ҽ� �ְ� ģ�� ������ ���־���.
};



class List {
private:
	Node *head;
public:
	List() { head = 0; }
	void append(int data, string data2);
	void insertNode(string data);
	void deleteNode(int data);
	void quit();
	void search(int data);
	void display(); // �׳����
	void sort();
	int isEmpty();
	//void Grade_display(char grade); // ���ϴ� ������ ���
	//void Major_display(char *major); // ���ϴ� ������ ���
};
#endif