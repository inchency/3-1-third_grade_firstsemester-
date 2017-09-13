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
	friend class List; // List 클래스에서 Node를 이용할수 있게 친구 선언을 해주었다.
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
	void display(); // 그냥출력
	void sort();
	int isEmpty();
	//void Grade_display(char grade); // 원하는 학점만 출력
	//void Major_display(char *major); // 원하는 전공만 출력
};
#endif