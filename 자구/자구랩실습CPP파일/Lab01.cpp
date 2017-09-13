#include <iostream>
#include <fstream>

using namespace std;

void swap(int *a, int * b);

int main() {

	int num[10];
	int temp = 0;

	fstream instream("input.txt");
	if (!instream) {
		cout << "Error" << endl;
		return 1;
	}

	cout << "Data list : ";

	while (instream >> num[temp]) {
		cout << num[temp] << " ";
		temp++;
	}
	cout << endl << "Sorted list: ";
	for (int i = 0; i < 10; i++) {
		int min = i;
		for (int j = i + 1; j < 10; j++) {
			if (num[min] > num[j])
			min = j;
		}
		swap(num[i], num[min]);
		cout << num[i] << " ";
	}
	cout << endl << "Enter Number : ";
	int a;
	int p = 0;
	cin >> a;

	for (int i = 0; i < 10; i++) {
		if (a == num[i]) 
			p = i;
	}
	if (p == 0)
		cout << "Not Found";
	else
		cout << "Found in position : " << p + 1;
	return 0;
}

void swap(int * a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}


-------------------------------------------------------------------------------------------------------

RecursiveÇÏ°Ô