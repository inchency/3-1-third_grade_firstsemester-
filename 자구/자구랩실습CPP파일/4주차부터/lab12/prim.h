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
	int num2; // 몇번째 노드인지 체크하기위해 만들어줌
	node(int num) { vertex = num; next = 0; }
	friend class Graph;
};
*/

class Graph {
private:
	//node *graph[MaxVertices];
	bool visited[MaxVertices]; // 방문했는지 안했는지 판별
	int V = 1;
public:
	void initGraph(); // 그래프 초기화 함수
	//void insertGraph(int num1, int num2); // 그래프 삽입 함수
	void displayGraph(); // 그래프 출력 함수
	//void DFS(int v);
	void prim(int v);
	void prim2(int v);
};

#endif
