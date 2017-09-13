/**********************************************************************
Name: �赿��
Student ID : 20123339
Program ID : HW3 SSL
Description: Double Linked List
Algorithm : "Insert"�� �Է��ϸ� ���ڿ� �̸��� �Է��� �� �ְ�
	"Delete"�� �Է��ϸ� �ش� ���ڸ� �Է��� ����Ʈ���� �ش��ϴ� ��� ����
	�����.
	"Search"�� �Է��ϸ� �ش��ϴ� ���ڰ� ������ ã���ְ� ������ ������
	����Ѵ�.
	"Forward"�� �Է��ϸ� ������� �Է¹��� List ��ϵ��� �տ�������
	����Ѵ�.
	"Backward"�� �Է��ϸ� ������� �Է¹��� List ��ϵ��� �ڿ�������
	����Ѵ�.
	"Quit"�� �Է��ϸ� ���α׷� ����
Variables : string str�� ���� ���(Insert, Delete, Search ���..)
	int num�� �޾Ƶ��� ����, string name�� �޾Ƶ��� �̸� List DLL ����
	DLL.Insert(num, name); DLL.Search(num); DLL.backwardList();
	DLL.Delete(num); DLL.forwardList(); DLL.Quit(); 
	int main() - �����Լ� ����
	�� �Լ��� ���� ������ DLLADT.cpp ���Ͽ��� �ϵ��� �ϰڴ�.
FileName : DLL_Main.cpp
***********************************************************************/

#include "DLL.h"

string str;
int num;
string name;
List DLL;

int main() {

	while (1) {
		cin >> str;

		if (str == "Insert") {
			cin >> num >> name;
			DLL.Insert(num, name);
		}

		else if (str == "Delete") {
			cin >> num;
			DLL.Delete(num);
		}

		else if (str == "Search") {
			cin >> num;
			DLL.Search(num);
		}

		else if (str == "Forward")
			DLL.forwardList();

		else if (str == "Backward")
			DLL.backwardList();

		else if (str == "Quit")
			DLL.Quit();

		else
			cout << "�Է¿���!!! Insert, Forward, Backward, Search �߿��� �� �Է��� �ּ���" << endl;
	}
}

// Insert 10 Kim Insert 20 Lee Forward Backward Search 10 Search 30 Delete 10 Delete 20 Forward