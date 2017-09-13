#include <iostream>

using namespace std;

int Fibo(int n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return (Fibo(n - 1) + Fibo(n - 2));
}

int main() {
	int a;
	cout << "정수를 입력 하세요";
	cin >> a;
	for (int i = 1; i <= a; i++) {
		cout << Fibo(i) << " ";
	}
	cout << endl << "Fibinacci(" << a << ") = " <<Fibo(a);
	cout << endl;
}