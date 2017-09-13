#include "prim.h"

int main() {
	Graph g;

	g.initGraph();
	cout << "Output" << endl;
	g.displayGraph();
	cout << endl;
	cout << "Minimal Spanning Tree(S 에서 시작하면)" << endl;
	g.prim(0);
	cout << endl;
	g.initGraph();
	g.prim2(0);
	cout << endl;

	return 0;
}