/**********************************************************************
Name: 김동훈
Student ID : 20123339
Program ID : HW3 SSL
Description: Double Linked List
Algorithm : "Insert"를 입력하면 숫자와 이름을 입력할 수 있고
	"Delete"를 입력하면 해당 숫자를 입력해 리스트에서 해당하는 노드 값을
	지운다.
	"Search"를 입력하면 해당하는 숫자가 있으면 찾아주고 없으면 없음을
	출력한다.
	"Forward"를 입력하면 현재까지 입력받은 List 목록들을 앞에서부터
	출력한다.
	"Backward"를 입력하면 현재까지 입력받은 List 목록들을 뒤에서부터
	출력한다.
	"Quit"을 입력하면 프로그램 종료
Variables : string str은 행할 명령(Insert, Delete, Search 등등..)
	int num은 받아들일 숫자, string name은 받아들일 이름 List DLL 선언
	DLL.Insert(num, name); DLL.Search(num); DLL.backwardList();
	DLL.Delete(num); DLL.forwardList(); DLL.Quit(); 
	int main() - 메인함수 실행
	이 함수에 대한 설명은 DLLADT.cpp 파일에서 하도록 하겠다.
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
			cout << "입력오류!!! Insert, Forward, Backward, Search 중에서 잘 입력해 주세요" << endl;
	}
}

// Insert 10 Kim Insert 20 Lee Forward Backward Search 10 Search 30 Delete 10 Delete 20 Forward