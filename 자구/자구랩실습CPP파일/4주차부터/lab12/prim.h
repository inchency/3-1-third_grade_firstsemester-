#ifndef __PRIM_H__
#define __PRIM_H__

#include <iostream>
#include <string>

#define MaxVertices 50
#define MAX 6

using namespace std;

/*
class node {
	int vertex;
	node *next;
	int num2; // ���° ������� üũ�ϱ����� �������
	node(int num) { vertex = num; next = 0; }
	friend class Graph;
};
*/

class Graph {
private:
	//node *graph[MaxVertices];
	bool visited[MaxVertices]; // �湮�ߴ��� ���ߴ��� �Ǻ�
	int V = 1;
public:
	void initGraph(); // �׷��� �ʱ�ȭ �Լ�
	//void insertGraph(int num1, int num2); // �׷��� ���� �Լ�
	void displayGraph(); // �׷��� ��� �Լ�
	//void DFS(int v);
	void prim(int v);
	void prim2(int v);
};

#endif
