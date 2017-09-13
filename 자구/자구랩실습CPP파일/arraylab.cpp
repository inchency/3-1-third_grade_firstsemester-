#include <iostream>
#include <fstream>
#define MAX_SIZE 100

using namespace std;

class SMarray { 
public: int col;
		int row;
		int value;
};
SMarray a[MAX_SIZE];
SMarray b[MAX_SIZE];

int row_change(int n, int b[MAX_SIZE][MAX_SIZE]);
void transpose(int acurrent, int n);

int main() {

	int n, acurrent;
	int matrix[MAX_SIZE][MAX_SIZE] = { 0 };

	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "error" << endl;
		return -1;
	}
	instream >> n;
	cout << "배열의 크기는 : " << n << endl;

	cout << "Sparse matrix" << endl;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			instream >> matrix[i][j];
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	acurrent=row_change(n, matrix);
	transpose(acurrent,n);

}

int row_change(int n, int b[MAX_SIZE][MAX_SIZE]) {
	int currenta = 0;
	cout << "row matrix " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (b[i][j] != 0) {
				a[currenta].row = i;
				a[currenta].col = j;
				a[currenta++].value = b[i][j];
			}
			
		}
	}
	for (int i = 0; i < currenta; i++)
		cout << a[i].row << " " << a[i].col << " " << a[i].value << endl;
	cout << endl;

	return currenta;
}

void transpose(int acurrent,int n) {
	int i, j, currentb;
	cout << "column major" << endl;
	if (a[0].value > 0) { /* 0이 아닌 행렬 */
		currentb = 0;
		for (i = 0; i < n; i++) { /* a에서 열별로 전치 여기서 (n은 0~5까지) */
			for (j = 0; j <acurrent; j++) { /* 현재의 열로부터 원소를 찾는다. 행의 갯수 8번*/
				if (a[j].col == i) { /*현재 열에 있는 원소를 b에 첨가  (0~5 일치하는지 검색)*/
					b[currentb].row = a[j].col;
					b[currentb].col = a[j].row;
					b[currentb].value = a[j].value;
					currentb++;
				}
			}
		}
	}
	for (int i = 0; i < currentb; i++)
		cout << b[i].row << " " << b[i].col << " " << b[i].value << endl;
}

