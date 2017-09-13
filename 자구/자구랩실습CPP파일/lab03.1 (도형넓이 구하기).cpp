/*******************************************************************
FileName : Lab03-1.cpp
name : 20123339 김동훈
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
		cout << "도형 triangle rectangle circle 중 하나를 입력 하세요 넓이를 구해드립니다." << endl;
		cin >> a;
		if (a == "triangle") {
			cout << "밑변, 높이 순으로 숫자를 입력하세요" << endl;
			cin >> sh[num].x >> sh[num].y;
			cout << "triangle " << sh[num].x << " " << sh[num].y << " " << sh[num].x*sh[num].y*0.5 << endl;
		}
		else if (a == "rectangle") {
			cout << "밑변, 높이 순으로 숫자를 입력하세요" << endl;
			cin >> sh[num].x >> sh[num].y;
			cout << "rectangle " << sh[num].x << " " << sh[num].y << " " << sh[num].x * sh[num].y << endl;
		}
		else if (a == "circle") {
			cout << "반지름 r의 숫자를 입력하세요" << endl;
			cin >> sh[num].r;
			cout << "circle " << sh[num].r << " " << sh[num].r * sh[num].r * 3.14 << endl;
		}
		else
			cout << "도형 입력 오류 스펠링을 확인해주세요" << endl;
		num++;
	}
	return 0;
}
