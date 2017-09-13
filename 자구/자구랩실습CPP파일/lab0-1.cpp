/*********************************
이름 : 김동훈
학번 : 20123339
ID : LAB0
********************************/


#include <iostream>
#include <fstream>

	using namespace std;

	int main()
	{
		int max = 0;
		int min;
		ifstream instreamFile("lab0-1.dat");
		int num;
		if (!instreamFile.is_open())
		{
			cout << "" << endl;
			return 1;
		}
		instreamFile >> num;
		min = num;
		max = num;

		for (int i = 0; num != NULL; i++)
		{
			if (min > num)
				min = num;
			if (max < num)
				max = num;
			num = NULL;
			instreamFile >> num;
		}

		cout << "최대값은 " << max << "입니다.";
		cout << "최소값은 " << min << " 입니다.";

		return 0;
	}




	