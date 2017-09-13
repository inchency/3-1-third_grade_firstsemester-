/*********************************************************
File Name : LAB006 SLL Main.cpp
학번 : 20123339
이름 : 김동훈
*********************************************************/
#include "LAB006 SLL.h"
List SSL;
string play;
string name;
int num;


int main() {
	cout << "delete 10 -> insert 10 lee-> insert 5 kim-> print -> insert 30 choi-> search 5 -> delete 5 -> print 를 순서대로 입력하세요." << endl;
	while (1) {
		//cout << "취할 행동, 숫자 를 입력하세요" << endl;
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
			cout << "입력 오류!! 형식에 맞게 다시 입력해 주세요" << endl;
	}
}
		



	