#include <iostream>
#include <fstream>
#define MAX_SIZE 100

using namespace std;

class MatrixA {
public:
	int row;
	int col;
	int val;
};

MatrixA a[MAX_SIZE] = { 0 };
MatrixA b[MAX_SIZE] = { 0 };

void transpose();

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "error : input.txt file not found" << endl;
		return -1;
	}
	instream >> a[0].row >> a[0].col >> a[0].val;
	cout << "Matrix A" << endl;
	cout << a[0].row << " " << a[0].col << " " << a[0].val << endl << "------" << endl;
	int temp = 1;
	while (instream >> a[temp].row >> a[temp].col >> a[temp].val) {
		cout << a[temp].row << " " << a[temp].col << " " << a[temp].val << endl;
		temp++;
	}
	cout << endl;
	cout << "Matrix B " << endl;
	transpose();
	cout << b[0].row << " " << b[0].col << " " << b[0].val << endl << "------"<<endl;
	for (int i = 1; i <= a[0].val; i++) {
		cout << b[i].row << " " << b[i].col << " " << b[i].val << endl;
	}
}

void transpose(){
	b[0].row = a[0].row;
	b[0].col = a[0].col;
	b[0].val = a[0].val;

	if (a[0].val > 0) {
		int count = 1;
		for (int i = 0; i < a[0].col; i++) {
			for (int j = 1; j <= a[0].val; j++) {
				if (a[j].col == i) {
					b[count].row = a[j].col;
					b[count].col = a[j].row;
					b[count].val = a[j].val;
					count++;
				}
			}
		}
	}
}