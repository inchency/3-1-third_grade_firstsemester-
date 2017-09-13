/*******************************************************************
FileName : Lab03.cpp
name : 20123339 김동훈
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

int avail = 0; // 실제로 계산되어 움직이는 공간
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
			cout << "입력 오류 다시 입력 해 주세요";
	}
	cout << "enter A(X): ";									
	while (1) {
		cin >> terms[avail].coef >> terms[avail].expon;
		avail++;
		if (terms[avail - 1].expon == 0) {  // // 차수가 0인 값을 입력받으면 A(X) 받는걸 중단시킴
			finisha = avail - 1;
			startb = avail;
			break;
		}
	}

	cout << "enter B(X): ";									
	while (1) {
		cin >> terms[avail].coef >> terms[avail].expon;
		avail++;
		if (terms[avail - 1].expon == 0) {  // // 차수가 0인 값을 입력받으면 B(X) 받는걸 중단시킴
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
		case -1:					// A차수 < B차수 일 경우
			attach(terms[startb].coef, terms[startb].expon);
			startb++; break;  // B차수가 더 크니까 B만 한칸씩 움직여줘서 비교해주면됨
		case 0:  // A차수 = B차수 일 경우
			coefficient = terms[starta].coef + terms[startb].coef;   // A계수+B계수를 임시 저장하는 계수변수
			if (coefficient)
				attach(coefficient, terms[starta].expon);  // 어짜피 차수가 같으므로 starta대신 startb넣어도 상관 x
			starta++; startb++; break;
		case 1:  //A 차수 > B차수 일 경우
			attach(terms[starta].coef, terms[starta].expon);
			starta++;
		}
	}
	for (; starta <= finisha; starta++)  //  차수가 없는 숫자일 경우
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
		case -1:  //  // A<B차수
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
		cout << "다항식에 항이 너무 많습니다." << endl;
	terms[avail].coef = coefficient;
	terms[avail].expon = exponent;
	avail++;
}

void Sattach(float coefficient, int exponent) {
	if (avail >= 100)
		cout << "다항식에 항이 너무 많습니다." << endl;
	terms[avail].coef = coefficient *-1;
	terms[avail].expon = exponent;
	avail++;
}