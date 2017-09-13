/*******************************************************************
FileName : Lab03.cpp
name : 20123339 �赿��
date : 2016-03-16
**********************************************************************/


#include <iostream>
#include <string>

using namespace std;

void padd(int starta, int finisha, int startb, int finishb, int *startc, int *finishc);
void psub(int starta, int finisha, int startb, int finishb, int *startc, int *finishc);
int COMPARE(int a, int b);
void attach(float coefficient, int exponent);
void Sattach(float coefficient, int exponent);

class Polynomial {
public:
	float coef;
	int expon;
};

Polynomial terms[100];

int avail = 0; // ������ ���Ǿ� �����̴� ����
void main() {
	int starta = 0, finisha = 0, startb, finishb, startc, finishc;
	bool check;
	string a;
	while (1) {												
		cout << "addition / subtraction ? : ";
		cin >> a;
		if (a == "addition") {
			check = true;
			break;
		}
		else if (a == "subtraction") {
			check = false;
			break;
		}
		else
			cout << "�Է� ���� �ٽ� �Է� �� �ּ���";
	}
	cout << "enter A(X): ";									
	while (1) {
		cin >> terms[avail].coef >> terms[avail].expon;
		avail++;
		if (terms[avail - 1].expon == 0) {  // // ������ 0�� ���� �Է¹����� A(X) �޴°� �ߴܽ�Ŵ
			finisha = avail - 1;
			startb = avail;
			break;
		}
	}

	cout << "enter B(X): ";									
	while (1) {
		cin >> terms[avail].coef >> terms[avail].expon;
		avail++;
		if (terms[avail - 1].expon == 0) {  // // ������ 0�� ���� �Է¹����� B(X) �޴°� �ߴܽ�Ŵ
			finishb = avail - 1;
			break;
		}
	}

	if (check == true){
		padd(starta, finisha, startb, finishb, &startc, &finishc);
		cout << "A(X) + B(X) = C(X)    ";
	}
	else {
		psub(starta, finisha, startb, finishb, &startc, &finishc);
		cout << "A(X) - B(X) = C(X)    ";
	}

	for (; startc <= finishc; startc++) {
		cout << terms[startc].coef << " ";
		cout << terms[startc].expon << " ";
	}
	cout << endl;
}

void padd(int starta, int finisha, int startb, int finishb, int *startc, int *finishc) {		
	float coefficient;				
	*startc = avail;
	while (starta <= finisha && startb <= finishb) {
		switch (COMPARE(terms[starta].expon, terms[startb].expon)) {
		case -1:					// A���� < B���� �� ���
			attach(terms[startb].coef, terms[startb].expon);
			startb++; break;  // B������ �� ũ�ϱ� B�� ��ĭ�� �������༭ �����ָ��
		case 0:  // A���� = B���� �� ���
			coefficient = terms[starta].coef + terms[startb].coef;   // A���+B����� �ӽ� �����ϴ� �������
			if (coefficient)
				attach(coefficient, terms[starta].expon);  // ��¥�� ������ �����Ƿ� starta��� startb�־ ��� x
			starta++; startb++; break;
		case 1:  //A ���� > B���� �� ���
			attach(terms[starta].coef, terms[starta].expon);
			starta++;
		}
	}
	for (; starta <= finisha; starta++)  //  ������ ���� ������ ���
		attach(terms[starta].coef, terms[starta].expon);
	for (; startb <= finishb; startb++)
		attach(terms[startb].coef, terms[startb].expon);
	*finishc = avail - 1;
}

void psub(int starta, int finisha, int startb, int finishb, int *startc, int *finishc) {		
	float coefficient;
	*startc = avail;
	while (starta <= finisha && startb <= finishb) {
		switch (COMPARE(terms[starta].expon, terms[startb].expon)) {
		case -1:  //  // A<B����
			Sattach(terms[startb].coef, terms[startb].expon);
			startb++; break;
		case 0:
			coefficient = terms[starta].coef - terms[startb].coef;
			if (coefficient)
				attach(coefficient, terms[starta].expon);
			starta++; startb++; break;
		case 1:
			attach(terms[starta].coef, terms[starta].expon);
			starta++;
		}
	}
	for (; starta <= finisha; starta++)
		attach(terms[starta].coef, terms[starta].expon);
	for (; startb <= finishb; startb++)
		Sattach(terms[startb].coef, terms[startb].expon);
	*finishc = avail - 1;
}

int COMPARE(int a, int b) {
	if (a < b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}

void attach(float coefficient, int exponent) {
	if (avail >= 100)
		cout << "���׽Ŀ� ���� �ʹ� �����ϴ�." << endl;
	terms[avail].coef = coefficient;
	terms[avail].expon = exponent;
	avail++;
}

void Sattach(float coefficient, int exponent) {
	if (avail >= 100)
		cout << "���׽Ŀ� ���� �ʹ� �����ϴ�." << endl;
	terms[avail].coef = coefficient *-1;
	terms[avail].expon = exponent;
	avail++;
}