/*********************************************
 �̸� : �赿��
 �й� : 20123339
 ID : LAB0
 *********************************************/




#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	int count = 0;
	ifstream instreamFile("lab0-1.dat");
	char buffer[100];
	if (!instreamFile.is_open())
	{
		cout << "" << endl;
		return 1;
	}

	while (buffer[0] != 0)
	{
		instreamFile >> buffer;
		cout << buffer << endl;
		count++;
	}
	count--;

	cout << "������ " << count << "�Դϴ�.";
	
	cout << buffer << endl;
	return 0;
}