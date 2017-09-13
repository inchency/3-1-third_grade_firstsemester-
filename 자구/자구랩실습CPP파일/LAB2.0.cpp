/*********************************************
 ÀÌ¸§ : ±èµ¿ÈÆ
 ÇĞ¹ø : 20123339
 ID : LAB1-0
 date : 2016-03-09
 *********************************************/

#include <iostream>
#include <fstream>

using namespace std;

int binsearch(int* data, int number, int left, int right);
int compare(int a, int b);

int main() {
	int data[10];
	int min, temp = 0, number;
	int left = 0, right = 9;

	ifstream instreamFile("Lab1.dat");
	if (!instreamFile.is_open()) {
		cout << "error " << endl;
		return 1;
	}

	cout << "Data list : ";
	while (instreamFile >> data[temp]) {
		cout << data[temp] << " ";
		temp++;
	}
	cout << endl;
	cout << "Sorted list :" ;

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
	cout << "Enter number : ";
	cin >> number;
	temp = binsearch(data, number, left, right);
	if (temp != -1)
		cout << "Found in position " << temp + 1 << endl;
	else
		cout << "Not Found" << endl;

	return 0;
}

int binsearch(int* data, int number, int left, int right) {
	int middle;
	if (left <= right) {
		middle = (left + right) / 2;

		switch (compare(data[middle], number)) {
		case 0: return binsearch(data, number, middle + 1, right);
		case 1: return middle;
		case 2: return binsearch(data, number, left, middle - 1);
		}
	}
	return -1;
}

int compare(int a, int b) {
	if (a > b)
		return 2;
	else if (a < b)
		return 0;
	else
		return 1;
}

------------------------------------------------------------------------------------------------------

³»°¡´Ù½ÃÂ§°Å

#include <iostream>
#include <fstream>

using namespace std;

void swap(int *a, int *b);
int binsearch(int *data, int number, int left, int right);
int compare(int a, int b);

int main() {
	
	int data[10];
	int min, temp = 0, number;
	int left = 0, right = 9;

	fstream instream("Lab1.0.txt");
	if (!instream.is_open()) {
		cout << "error" << endl;
		return 1;
	}
cout << "Data list : ";
	while (instream >> data[temp]) {
		cout << data[temp] << " ";
		temp++;
	}
	cout << endl << "Sorted list : ";

	for (int i = 0; i < 10; i++) {
		min = i;
		for (int j = i + 1; j < 10; j++) {
			if (data[min] > data[j])
				min = j;
		}
		swap(data[i], data[min]);

		cout << data[i] << " ";
	}
	cout << endl << "Enter number : ";
	cin >> number;
	int k;
	k = binsearch(data, number, left, right);
	if (k == -1)
		cout << "Not Found" << endl;
	else
		cout << "Found in position " << k + 1;
		
}

void swap(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int binsearch(int *data, int number, int left, int right) {
	int middle;
	if (left <= right) {
		middle = (left + right) / 2;
		switch (compare(data[middle], number)) {
		case 0: return binsearch(data, number, middle + 1, right);
		case 1: return middle;
		case 2: return binsearch(data, number, left, middle - 1);
		}
	}
		return -1;
}

int compare(int a, int b) {
	if (a > b)
		return 2;
	else if (a < b)
		return 0;
	else
		return 1;
}

	