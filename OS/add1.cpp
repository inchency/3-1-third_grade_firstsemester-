#include <iostream>
#include <fstream>
using namespace std;

int x;

int Load()
{
	ifstream ifile("input.data");
	if (!ifile.is_open())
	{
		cout << "error : input.data를 열수 없습니다." << endl;
		return 1;
	}
	while (ifile >> x);

	return x;

	ifile.close();
}

void Store(int data)
{
	ofstream ofile("input.data", ios::app);

	if (!ofile.is_open())
		cout << "error : input.data를 열수 없습니다." << endl;

	ofile << data << endl;

	ofile.close();
}

int Add(int i, int j)
{
	return i + j;
}

int main()
{
	for (int i = 0; i < 1000; i++)
	{
		x = Load();
		x = Add(x, 1);
		Store(x);
	}
}
