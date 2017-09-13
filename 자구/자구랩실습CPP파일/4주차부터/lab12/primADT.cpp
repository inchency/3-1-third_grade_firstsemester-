// DFSADT.CPP

#include "prim.h"

int graphArray[MAX][MAX] = {  // �־��� adjacency Matrix
	{ 0,5,100, 12,100,100 },
	{ 5,0,6,10,24,100 },
	{ 100,6,0,17,100,30 },
	{ 12,10,17,0,20,100 },
	{ 100,24,100,20,0,13 },
	{ 100,100,30,100,13,0 } 
}; 

// ���ڸ� ���ڷ� ���� �ٲپ��ֱ� ���� ������ �迭
char changeChar[8] = {'A', 'B', 'C', 'D', 'E', 'F'};

/*******************************************************
function : void Graph::initGraph()
description : graph[i] ������ MaxVertices�� ��ŭ
0���� �ʱ�ȭ ���ش�.
variables : int i : MaxVertices���� �ݺ��� �����ϱ�����
��������
********************************************************/

void Graph::initGraph() {
	for (int i = 0; i < MaxVertices; i++) {
		//graph[i] = NULL;
		visited[i] = false; // �ʱⰪ�� ��� false
	}
}


void Graph::displayGraph() {
	cout << "	";
	for (int i = 0; i < 8; i++) 
		cout << changeChar[i] << "	";
	cout << endl;
	for (int i = 0; i < MAX; i++) {
		cout << changeChar[i] << "	";
		for (int j = 0; j < MAX; j++) {
			cout << graphArray[i][j] << "	";
		}
		cout << endl;
	}
}

void Graph::prim(int v) {
	cout << "Start "<< changeChar[v] << " : ";
	visited[v] = true;
	int c = 0;
	int start = v;
	int temp;
	int store;
	int sum = 0;
	
	//int vertex=0;
	//cout << "start : " << changeChar[v];
	while (c < MAX - 1) {
		int min = 100;
		temp = start;
		for (int i = 0; i < MAX; i++) {
			if (min > graphArray[start][i] && visited[i] == false) {
				min = graphArray[start][i];
				store = i;
				sum = sum + min;
			}
		}
		start = store;
		visited[start] = true;
		cout << changeChar[temp] << "," << changeChar[start];
		if (c != MAX - 2)
			cout << " -> ";
		c++;
	}
	cout << endl;
	cout << "Weight: " << sum;
}

void Graph::prim2(int v) {
	cout << "Start " << changeChar[v] << " : ";
	visited[v] = true;
	int c = 0;
	int start = v;
	int temp;
	int store;
	int sum = 0;
	int check;
	int checkcost;
	//int vertex=0;
	//cout << "start : " << changeChar[v];
	for (int i = 0; i < MAX-2; i++) {
		if (graphArray[V][i] != 0 && graphArray[V][i] != 100) {
			check = i;
			checkcost = graphArray[V][i];
		}
	}

	while (c < MAX - 1) {
		int min = 100;
		temp = start;
		for (int i = 0; i < MAX; i++) {
			if (min > graphArray[start][i] && visited[i] == false) {
				if (i == check) {
					if (checkcost < graphArray[start][i]) {
						min = checkcost;
						store = i;
						sum = sum + min;
						temp = V;
					}
				}
				else {
					min = graphArray[start][i];
					store = i;
					sum = sum + min;
				}
			}
		}
		start = store;
		visited[start] = true;
		cout << changeChar[temp] << "," << changeChar[start];
		if (c != MAX - 2)
			cout << " -> ";
		c++;
	}
	cout << endl;
	cout << "Weight: " << sum;
}