/*********************************************************
File Name : DLL.h
description : Node 클래스, List 클래스에 대한 정보가
입력되어 있다.
*********************************************************/
#ifndef __DLL_H__
#define __DLL_H__

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

class Node {
private:
	int data;
	string name;
	Node *next;
	Node *prev;
	Node(int val, string str) {
		data = val;
		name = str;
		next = 0;
		prev = 0;
	}
	friend class List; // List 클래스에서 Node를 이용할수 있게 친구 선언을 해주었다.
};

class List {
private:
	Node *head;
public:
	List() { head = 0; }
	void Insert(int num, string name);
	void Insert_After(int num, string name, int num2);
	void Insert_Before(int num, string name, int num2);
	void Delete(int num);
	void Search(int num);
	void Quit();
	bool isEmpty();
	void forwardList();
	void backwardList();
	void find_Nth(int num);
};
#endif