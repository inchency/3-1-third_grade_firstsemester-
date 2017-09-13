/**********************************
20123339 ±èµ¿ÈÆ LAB 10 BFS1
***********************************/


#include <iostream>
using namespace std;

#define MAX 100
int graph[MAX][MAX] = {
	{ 0, 1, 0, 0, 1, 0, 0, 0 },
	{ 1, 0, 1, 0, 1, 0, 0, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 1, 1, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 0, 0, 0, 0, 1, 0, 1 },
	{ 0, 0, 0, 0, 0, 0, 1, 0 }
};

char changeChar[8] = { 'S', 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
bool visited[MAX] = { false };
int queue[MAX] = { 0 };
int front = -1;
int rear = -1;

void enqueue(int n)
{
	queue[++front] = n;
}
int dequeue()
{
	return queue[++rear];
}

void BFS(int n)
{
	visited[n] = true;
	enqueue(n);
	cout << changeChar[n] << " ";

	for (int i = 0; i < MAX; i++)
	{
		n = dequeue();

		for (int j = 0; j < MAX; j++)
		{
			if (graph[n][j] == 1)
			{
				if (!visited[j])
				{
					enqueue(j);
					visited[j] = true;
					cout << changeChar[j] << " ";
				}
			}
		}
	}
}

void main(void)
{
	cout << "***** Adjacent Matrix" << endl;
	cout << "    S  A  B  C  D  E  F  G" << endl;
	for (int i = 0; i < 8; i++) {
		cout << changeChar[i] << "   ";
		for (int j = 0; j < 8; j++) {
			cout << graph[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl << endl;
	cout << "***** Breadth First Search (BFS)" << endl;
	BFS(0);
	cout << endl;

}