/*********************************************************
File Name : LAB006 SLL Main.cpp
�й� : 20123339
�̸� : �赿��
*********************************************************/
#include "LAB006 SLL.h"
List SSL;
string play;
string name;
int num;


int main() {
	cout << "delete 10 -> insert 10 lee-> insert 5 kim-> print -> insert 30 choi-> search 5 -> delete 5 -> print �� ������� �Է��ϼ���." << endl;
	while (1) {
		//cout << "���� �ൿ, ���� �� �Է��ϼ���" << endl;
		cin >> play;
		if (play == "insert") {
			cin >> num;
			cin >> name;
			SSL.append(num, name);
		}
		else if (play == "delete") {
			cin >> num;
			SSL.deleteNode(num);
		}
		else if (play == "print") {
			//SSL.display();
			cout << "list : ";
			SSL.sort();
			//cout << endl;
			SSL.display();
			
		}
		else if (play == "search") {
			cin >> num;
			SSL.search(num);
		}
		else if (play == "quit")
			SSL.quit();
		else
			cout << "�Է� ����!! ���Ŀ� �°� �ٽ� �Է��� �ּ���" << endl;
	}
}
		



	