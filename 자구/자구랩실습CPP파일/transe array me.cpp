#include <iostream>
#include <fstream>
#define MAX_SIZE 100

using namespace std;

int row_change(int n, int (*arr1)[MAX_SIZE]);
void col_change(int counta, int n);
int row_array[MAX_SIZE][3] = { 0 };

int main() {
	
	int n; // n은 배열의 크기
	int matrix[MAX_SIZE][MAX_SIZE] = { 0 };
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "Error input.txt 파일을 찾을 수 없습니다." << endl;
		return -1;
	}

	instream >> n;
	cout << "배열의 크기는  : "<< n << " 입니다." << endl;
	cout << "Sparse matrix" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			instream >> matrix[i][j];
			cout << matrix[i][j] << "	";
		}
		cout << endl;
	}
	int counta = row_change(n, matrix);
	col_change(counta, n);
	return 0;
}

int row_change(int n, int(*arr1)[MAX_SIZE]) {
	int counta = 0;
	cout << "row matrix " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr1[i][j] != 0) {
				row_array[counta][0] = i; // 행
				row_array[counta][1] = j; // 열
				row_array[counta][2] = arr1[i][j]; // value값
				counta++;
			}
		}
	}
	for (int i = 0; i < counta; i++) {
		for (int k = 0; k < 3; k++)
			cout << row_array[i][k] << "	";
		cout << endl;
	}
	return counta;
}

void col_change(int counta, int n) {
	int col_array[MAX_SIZE][3] = { 0 };
	int countb = 0;
	cout << endl << "column major" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < counta; j++) {
			if (row_array[j][1] == i) { // 0부터 5까지 검색
				col_array[countb][0] = row_array[j][1];
				col_array[countb][1] = row_array[j][0];
				col_array[countb][2] = row_array[j][2];
				countb++;
			}
		}
	}
	for (int i = 0; i < countb; i++) {
		for (int j = 0; j < 3; j++) {
			cout << col_array[i][j] << " ";
		}
		cout << endl;
	}
}