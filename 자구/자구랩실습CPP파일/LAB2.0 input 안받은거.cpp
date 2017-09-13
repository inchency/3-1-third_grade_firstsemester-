#include <iostream>

using namespace std;

int binsearch(int* data, int number, int left, int right);
int compare(int a, int b);
//void error();

void main() {
	int data[10] = { 40,20,50,70,10,30,60,80,90,100 };
	int min;
	int temp;
	int number;
	int left = 0;
	int right = 9;

	for (int i = 0; i < 10; i++) {
		min = i;
		for (int j = i + 1; j < 10; j++) {
			if (data[min] > data[j])
				min = j;
		}
		temp = data[i];
		data[i] = data[min];
		data[min] = temp;
		cout << data[i] << " ";
	}
	cout << "Search Number : ";
	cin >> number;
	int k = binsearch(data, number, left, right);
	if (k == -3)
		cout << "Not Found";
	else
		cout << "Find " << number << " Position : " << k + 1;
}

int binsearch(int* data, int number, int left, int right) {
	int middle;
	if (left <= right) {
		middle = (left + right) / 2;

		switch (compare(data[middle], number)) {
			case -1 : return binsearch(data, number, middle + 1, right); 
			case 0 : return middle;
			case 1 : return binsearch(data, number, left, middle - 1);
		}
	}
	//error();
	return -3;
}

int compare(int a, int b) {
	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}

/*
void error() {
	cout << "이 숫자는 존재하지 않습니다. 오류코드 : ";
}
*/

