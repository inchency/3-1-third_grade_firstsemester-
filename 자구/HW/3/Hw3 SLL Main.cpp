/*********************************************************
Name: �赿��
Student ID : 20123339
Program ID : HW3 SSL
Description: Singly Linked List
Algorithm : data1.txt�� ���� �ҷ����� �� �޾Ƶ��� �ڷḦ sort()�Լ���
	����Ͽ� ���ĺ� ������������ ���� �� ������ش�.
	�״��� �л����� ���� �� �ڽ��� �����ϰ� ���� ������ (A)
	�Է� �� �� �� �������� �����ϴ� �ڷḦ ������ش�.
	�״��� data2.txt ������ �ҷ��� SSL�� �̾��� �� 
	�ٽ� sort() �Լ��� �̿��� ���ĺ� ������������ ���� ���ش�.
	�� �� �л����� ���� �� �ڽ��� �����ϰ� ���� ���� (CS)
	�� �Է� �� �� �� �������� �����ϴ� �ڷḦ ������ش�.
Variables : 
SSL.append(input);
SSL.sort();
SSL.Grade_display(grade);
SSL.Major_display(major);
�� �Լ��� ���� ������ Hw3 SLL ADT.cpp ���Ͽ��� �ϵ��� �ϰڴ�.
FileName : Hw3 SLL Main.cpp
**********************************************************/
#include "HW3 SLL.h"
List SSL;
string input;
/*********************************************************
function : int main() �����Լ�
description : data1.txt, data2.txt���� ���� �о� �䱸���׿�
	�˸°Բ� ����, ��� ���� ���ִ� ���� �Լ��̴�.
variables : char garde, char major[3] ���� ����ڰ� ���ϴ�
	���� �� ������ ������ �� �ֵ��� ������ �� �����̴�.
*********************************************************/
int main() {
	ifstream instream("data1.txt");
	if (!instream.is_open()) {
		cout << "data1.txt ������ �� �� �����ϴ�." << endl;
		return -1;
	}
	ifstream instream2("data2.txt");
	if (!instream2.is_open()) {
		cout << "data2.txt ������ �� �� �����ϴ�." << endl;
		return -1;
	}
	cout << "Print the LIST in ascending order bye the student name" << endl;
	while (getline(instream, input)) 
		SSL.append(input);
	SSL.sort();
	SSL.display();
	char grade;
	cout << "���� A~C �߿��� ������� ������ �Է��ϼ���. (�빮�ڷ� �Է��ϼ���)";
	cin >> grade;
	cout << "Print the student with grade '" << grade << "'" << endl;
	SSL.Grade_display(grade);
	while (getline(instream2, input))
		SSL.append(input);
	SSL.sort();
	char major[3];
	cout << "CS EE HI CH �� ������� ������ �Է��ϼ���. (�빮�ڷ� �Է��ϼ���)";
	cin >> major;
	cout << "MERGE the data file 2 into the previous Linked LIST, and Print " << major << " major student.";
	SSL.Major_display(major);
	return 0;
}