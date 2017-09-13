/*********************************************************
Name: 김동훈
Student ID : 20123339
Program ID : HW3 SSL
Description: Singly Linked List
Algorithm : data1.txt를 먼저 불러들인 후 받아들인 자료를 sort()함수를
	사용하여 알파벳 오름차순으로 정렬 후 출력해준다.
	그다음 학생들의 성적 중 자신이 열람하고 싶은 성적을 (A)
	입력 한 후 그 성적만을 포함하는 자료를 출력해준다.
	그다음 data2.txt 파일을 불러와 SSL에 이어준 후 
	다시 sort() 함수를 이용해 알파벳 오름차순으로 정렬 해준다.
	그 후 학생들의 전공 중 자신이 열람하고 싶은 전공 (CS)
	을 입력 한 후 그 전공만을 포함하는 자료를 출력해준다.
Variables : 
SSL.append(input);
SSL.sort();
SSL.Grade_display(grade);
SSL.Major_display(major);
이 함수에 대한 설명은 Hw3 SLL ADT.cpp 파일에서 하도록 하겠다.
FileName : Hw3 SLL Main.cpp
**********************************************************/
#include "HW3 SLL.h"
List SSL;
string input;
/*********************************************************
function : int main() 메인함수
description : data1.txt, data2.txt에서 값을 읽어 요구사항에
	알맞게끔 정렬, 출력 등을 해주는 메인 함수이다.
variables : char garde, char major[3] 등은 사용자가 원하는
	성적 및 전공을 열람할 수 있도록 선언해 준 변수이다.
*********************************************************/
int main() {
	ifstream instream("data1.txt");
	if (!instream.is_open()) {
		cout << "data1.txt 파일을 열 수 없습니다." << endl;
		return -1;
	}
	ifstream instream2("data2.txt");
	if (!instream2.is_open()) {
		cout << "data2.txt 파일을 열 수 없습니다." << endl;
		return -1;
	}
	cout << "Print the LIST in ascending order bye the student name" << endl;
	while (getline(instream, input)) 
		SSL.append(input);
	SSL.sort();
	SSL.display();
	char grade;
	cout << "성적 A~C 중에서 보고싶은 학점을 입력하세요. (대문자로 입력하세요)";
	cin >> grade;
	cout << "Print the student with grade '" << grade << "'" << endl;
	SSL.Grade_display(grade);
	while (getline(instream2, input))
		SSL.append(input);
	SSL.sort();
	char major[3];
	cout << "CS EE HI CH 중 보고싶은 전공을 입력하세요. (대문자로 입력하세요)";
	cin >> major;
	cout << "MERGE the data file 2 into the previous Linked LIST, and Print " << major << " major student.";
	SSL.Major_display(major);
	return 0;
}