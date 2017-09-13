#include<iostream>
#include<fstream>

using namespace std;

int Load(int a);
void Store(int data);
int Add(int i, int j);

int main() {
	int x=0;
	for (int i = 0; i < 1000; i++) {
		x = Load(x);
		x = Add(x, 1);
		Store(x);
	}
}

int Load(int a) {
	ifstream instream("data.txt");
	while (instream >> a);
	instream.close();
	return a;
}

void Store(int data) {
	ofstream instream("data.txt", ios::app);
	instream << data << endl;
	instream.close();
}

int Add(int i, int j) {
	return i + j;
}
