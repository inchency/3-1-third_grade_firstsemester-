/*******************************************************************
FileName : Lab03-1.cpp
name : 20123339 �赿��
date : 2016-03-16
**********************************************************************/

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

struct shape {
	char sh[10];
	double x, r, y;
	double size = 0;
}; shape sh[100];

int num = 0;

int main() {
	string a;
	cout.setf(ios::fixed);
	cout.precision(2);

	while (1) {
		cout << "���� triangle rectangle circle �� �ϳ��� �Է� �ϼ��� ���̸� ���ص帳�ϴ�." << endl;
		cin >> a;
		if (a == "triangle") {
			cout << "�غ�, ���� ������ ���ڸ� �Է��ϼ���" << endl;
			cin >> sh[num].x >> sh[num].y;
			cout << "triangle " << sh[num].x << " " << sh[num].y << " " << sh[num].x*sh[num].y*0.5 << endl;
		}
		else if (a == "rectangle") {
			cout << "�غ�, ���� ������ ���ڸ� �Է��ϼ���" << endl;
			cin >> sh[num].x >> sh[num].y;
			cout << "rectangle " << sh[num].x << " " << sh[num].y << " " << sh[num].x * sh[num].y << endl;
		}
		else if (a == "circle") {
			cout << "������ r�� ���ڸ� �Է��ϼ���" << endl;
			cin >> sh[num].r;
			cout << "circle " << sh[num].r << " " << sh[num].r * sh[num].r * 3.14 << endl;
		}
		else
			cout << "���� �Է� ���� ���縵�� Ȯ�����ּ���" << endl;
		num++;
	}
	return 0;
}
