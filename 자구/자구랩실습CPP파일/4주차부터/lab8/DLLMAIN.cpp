/**********************************************************************
Name: 김동훈
Student ID : 20123339
Program ID :  Lab08 DDL
Description: Double Linked List
FileName : DLLMain.cpp
***********************************************************************/

#include "DLL.h"

string str;
int num;
int num2;
string name;
List DLL;

int main() {

	while (1) {
		cin >> str;

		if (str == "Insert") {
			cin >> num;
			DLL.Insert(num, name);
		}

		else if (str == "Delete") {
			cin >> num;
			DLL.Delete(num);
		}

		else if (str == "Find") {
			cin >> num;
			DLL.find_Nth(num);
		}

		else if (str == "Forward")
			DLL.forwardList();

		else if (str == "Backward")
			DLL.backwardList();

		else if (str == "Quit")
			DLL.Quit();
		else if (str == "Insertafter") {
			cin >> num;
			cin >> num2;
			DLL.Insert_After(num, name, num2);
		}
		else if (str == "Insertbefore") {
			cin >> num;
			cin >> num2;
			DLL.Insert_Before(num, name, num2);
		}
		else
			cout << "입력오류!!! Insert, Forward, Backward, Search 중에서 잘 입력해 주세요" << endl;
	}
}

// Insert 10 Insert 20 Insert 30 Forward Insertafter 2 40 Forward Insertbefore 3 50 Forward