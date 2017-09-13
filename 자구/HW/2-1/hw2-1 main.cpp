/****************************************************************************
Name : 김동훈
Student ID : 20123339
Program ID : HW#2-1 Infix to Postfix Conversion & Postfix Evaluation
Description : buffer에 데이터를 받아들여서 괄호에 따라 서로 대칭하면 balance
			  대칭하지 않으면 unbalance를 출력한다. 
Algorithm : 데이터를 한줄씩 읽어서 buffer값에 넣은 후 '{,[,(' 와 같이 여는 괄호가 나오면
	스택에 무조건 push 해주고 닫는괄호 '}' 이 나오면 우선적으로 스택이 비어있는가를
	검사 한 후 비어있으면 unbalance 를 출력 후 나중에 최종적으로 확인할 부분에서
	중복되지 않게 check를 1로 바꾸어준다. 그리고 비교문을 빠져나온다. 
	비어있지 않으면 '}'와 대칭되는 '{' 인가를 판별하는데 만약 맞으면 계속 
	다음으로 넘어간다. 만약 일치 하지 않으면 무조건 unbalance한 것이므로 unbalance를 
	출력하고 역시 check를 1로 변화시켜준다. 더이상 비교할 필요가 없으므로 빠져나온다. 
	마찬가지로 ']'와 ')'를 비교해주고 모두 비교 후 스택이 비워져 있는 상태라면 balance한 
	상태이니 balance를 출력, 그렇지 않은 경우는 unbalance하지 않은경우이다. 
	그런데 이 때 중복 출력이 될 수 있으니 아까 check=1로 된 것을 제외한 경우만 출력하게 한다. 
	그리고 비워져 있지 않은 스택을 비워질 때 까지 pop 해서 empty하게 만들어 준다.
Variables : 클래스 Stack a,void balance(char *bf, int len, int check), 
	void print_Unbal(int len), void print_Bal(int len) 함수들을 사용하였다
****************************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include "Stack.h"
#define MAX_SIZE 100

Stack a(MAX_SIZE); // 크기가 100인 스택 a 생성
void balance(char *bf, int len, int check); // balance한지 unbalance인지 비교해주는 함수
void print_Unbal(int len); // unbalance한 경우를 출력해 주는 함수
void print_Bal(int len);  // balance한 경우를 출력해 주는 함수

/****************************************************************************
function : int main()  메인 함수
description : input.txt에서 데이터값을 읽어 임시 버퍼배열에 저장한 후 balance 
			함수를 호출한다.
variables : char buffer[MAX_SIZE] : 데이터값을 저장 할 최대 배열 크기가 100인
			임시로 저장시킬 버퍼
			int len : 데이터 값을 입력받은 길이변수이다.
			int check : unbalanced 중복 출력을 막기 위해 선언한 변수이다.
****************************************************************************/
int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt를 찾을 수 없습니다" << endl;
		return -1;
	}
	char buffer[MAX_SIZE];
	while (instream.getline(buffer, 80)) {  // 한줄씩 읽고 최대 80바이트까지 읽어서 buffer에 넣음
		int len = strlen(buffer);
		int check = 0;  //  unbalance에서 중복 unbalance 출력을 막기 위해 선언한 변수
		for (int k = 0; k < len; k++) { // 읽어들인 버퍼 출력
			cout << buffer[k];
		}
		balance(buffer, len, check);
	}
	return 0;
}
/****************************************************************************
function : void balance(char *buffer, int len, int check)  :  
			balance인지 아닌지 확인해 주는 함수
description : 여는 괄호를 만나면 무조건 stack에 집어 넣고 닫는 괄호가 나오면
		스택이 비어있는지를 우선 확인한 후 비어있으면 unbalanced 아니면
		괄호의 종류에 따라 if문을 통해 식 끝까지 비교해 나간다.
****************************************************************************/
void balance(char *buffer, int len, int check) { // balance인지 아닌지 확인해 주는 함수
	for (int i = 0; i < len; i++) {
		if (buffer[i] == '{' || buffer[i] == '[' || buffer[i] == '(') // 여는 괄호를 만나면 push
			a.push(buffer[i]);
		else if (buffer[i] == '}') {  // }의 괄호를 만나면
			if (a.isEmpty()) { // 비어있는 경우는 unbalance한 경우
				print_Unbal(len);
				check = 1; // 비교해주기 위한 변수 check를 1로 변경
				break;
			}
			else if (a.pop() == '{')  // '{' 이면 대칭되는 것이므로 계속 진행
				continue;
			else { // 대칭되지 않는 괄호가 나오면 unbalance출력하고 check=1로 변경
				print_Unbal(len);
				check = 1;
				break;
			}
		}
		else if (buffer[i] == ']') { // 위와 같은 방법이다.
			if (a.isEmpty()) {
				print_Unbal(len);
				check = 1;
				break;
			}
			else if (a.pop() == '[')
				continue;
			else {
				print_Unbal(len);
				check = 1;
				break;
			}
		}
		else if (buffer[i] == ')') { // 위와 같은 방법이다.
			if (a.isEmpty()) {
				print_Unbal(len);
				check = 1;
				break;
			}
			else if (a.pop() == '(')
				continue;
			else {
				print_Unbal(len);
				check = 1;
				break;
			}
		}
	}
	if (a.isEmpty()) // 스택이 비어져 있으면 계속 대칭되서 balance한 경우이므로 balance 출력
		print_Bal(len);
	else if (!a.isEmpty() && check == 0)  // 스택이 비워져있지 않고 check가 0인 경우 unbalance한 경우 이므로 unbalance check==0한 이유는 중복출력 막기 위함
		print_Unbal(len);
	else if (!a.isEmpty()) // 스택이 비워져있지 않으면 비워질때까지 pop 해준다
		while (a.isEmpty())
			a.pop();
}


/****************************************************************************
function : void print_Unbal(int len) : 형식에 맞게끔 unbalanced를 출력해주는 함수
description : 출력 형식에 맞게끔 unbalanced를 출력해 준다.
****************************************************************************/
void print_Unbal(int len) { // 형식에 맞게끔 unbalanced를 출력해주는 함수
	for (int i = 0; i < 20 - len; i++) {
		cout << " ";
	}
	cout << "unbalanced" << endl;
}
/****************************************************************************
function : void print_Unbal(int len) : 형식에 맞게끔 balanced를 출력해주는 함수
description : 출력 형식에 맞게끔 balanced를 출력해 준다.
****************************************************************************/
void print_Bal(int len) {  // 형식에 맞게끔 balanced를 출력해주는 함수
	for (int i = 0; i < 20 - len; i++) {
		cout << " ";
	}
	cout << "balanced" << endl;
}