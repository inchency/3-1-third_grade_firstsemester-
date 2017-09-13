#include<iostream>
#include<fstream>

using namespace std;


int Loaded(int i) {
	int instance;
	// open file
	fstream instreamFile;
	instreamFile.open("data.txt", ios::in);
	if(i<10)
		instreamFile.seekg(-1L, ios::end);
	else if(i<100)
		instreamFile.seekg(-2L, ios::end);
	else
		instreamFile.seekg(-3L, ios::end);
	// read the las data
	instreamFile >> instance;
	// close file
	instreamFile.close();
	
	return instance;
}

void Store(int data) {
	// open file
	fstream instreamFile;
	instreamFile.open("data.txt", ios::app);
	// append the data
	instreamFile<<endl<<data;
	// close file
	instreamFile.close();
}

int Add(int i, int j) {
	return i + j;
}

int main() {
	int x;
	for (int i = 0; i < 1000; i++) {
		x = Loaded(i);
		x = Add(x, 1);
		Store(x);
	}
}