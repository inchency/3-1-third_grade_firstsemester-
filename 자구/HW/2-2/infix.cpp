/****************************************************************************
Name : 김동훈
Student ID : 20123339
Program ID : HW#2-2 Infix to Postfix Conversion & Postfix Evaluation
Description : 키보드로부터 수식데이터를 입력 받아 infix를 postfix로 변환 후 
	출력하고 postfix evaluation 알고리즘을 사용해 최종값을 출력한다.
Algorithm : postfix로 변환하는 알고리즘은 우선순위를 '*'= '/'  >  '+'= '-'  >  '('
	로 정해서 (가 나오면 무조건 push +,-가 나오면 top가 0이상이고 (괄호가
	나올 때 까지 pop 해준 후 push 해준다. *,/가 나오면 top이 0 이상, ( 괄호가 
	나올 때 까지, +,- 기호가 나올 때 까지 pop 해준 후 push 해준다. ) 괄호가
	나오면 (를 만날 때 까지 pop 해준다. 그리고 마지막으로 스택을 비워질 때
	까지 pop 해주면 변환이 완료 된다.
	이 변환 된 식을 임시버퍼배열 변수에 저장 하여 스택에 숫자를 쌓고 사칙연산이
	나오면 두 수를 pop 한 후 계산 한 다음 그 계산된 값을 다시 push한다. 식이
	끝날 때 까지 반복 하며 마지막에 남은 값을 pop 하면 계산 된 결과 값이 나온다.
Variables : 클래스 Stack a, typedef enum{}precedence, void postfix(),
	precedence get_token, char buffer[] 등의 변수와 함수를 사용하였다.
****************************************************************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include "infix.h"
#define MAX_SIZE 100

typedef enum { lparen, rparen, pplus, mminus, times, divide, mod, eos, operand }precedence;
void postfix(char *infix, int len);
int eval(char *str);
precedence get_token(char *symbol, int *n, char *infix);
Stack a(MAX_SIZE);
char buffer[MAX_SIZE] = {};

/****************************************************************************
function : int main()  메인 함수
description : 키보드로부터 수식 데이터를 받아 들여서 postfix함수와 eval 함수를
	거쳐 변환, 계산을 수행 하여 이를 출력한다.
variables : int len 변수는 식의 길이를 세기 위한 변수이다.
****************************************************************************/
int main() {
	char str[MAX_SIZE] = {};
	int len;

	cout << "Enter Data : ";
	cin >> str;
	len = strlen(str);
	cout << "Echo data (infix form) : ";
	for (int i = 0; i < len; i++)
		cout << str[i];
	cout << endl << "Conversion (postfix form): ";
	postfix(str, len);
	int k = 0;
	while (buffer[k] != NULL)
		cout << buffer[k++];
	cout << endl;
	cout << "Result	: " << " " << eval(buffer) << endl;
	return 0;
}
/****************************************************************************
function : void postfix(char *infix, int len) infix에서 postfix로 변환하는
	함수이다.
description : '*'= '/'  >  '+'= '-'  >  '('  의 우선순위로 (괄호가 나오면
	무조건 push하고 +,-가 나오면 *,/보다 우선순위가 낮으므로 top이 0이상,
	(괄호가 나올 때 까지 pop을 해준 후 +,-를 push 해준다. *,/가 나오면 이는
	+,-보다 우선순위가 높으므로 위의 조건에 +or-이 나올 때 까지 pop 해준 후
	push주는 조건을 추가해 준다. 즉 우선순위를 비교해서 앞에 것을 pop 해줄지를
	결정한다. 즉 우선순위가 가장 낮은) 괄호가 나오면 (가 나올 때 까지 pop해주면
	된다. 이 때 (괄호를 없애기 위해 한번 더 pop 해준다. 식 끝까지 비교 후
	stack이 비워질 때 까지 pop 하면 postfix로의 변환은 완료 된다.
variables : char *infix는 위에서 받은 식을 가르키는 변수이며 이를 배열로 나타
	낸 것이다. 또 변수를 통해 스택에 push 한다.
	int len 변수는 위의 식의 길이를 받기 위한 매개변수이다.
****************************************************************************/
void postfix(char *infix, int len) {    // 우선순위 '*'= '/'  >  '+'= '-'  >  '('  
	int j = 0;
	for (int i = 0; i < len; i++) {
		switch (infix[i]) {
		case '(': // (괄호가 나오면 무조건 push 해준다.
			a.push(infix[i]);
			break;
		case '+':
			while (a.get_top() >= 0 && a.set_stacktop() != '(') // top이 0이상, (괄호가 나올 때 까지 pop해준 후 push 해준다.
				buffer[j++] = a.pop();
			a.push(infix[i]);
			break;
		case '-': // -와 +는 우선순위가 같다.
			while (a.get_top() >= 0 && a.set_stacktop() != '(') // top이 0이상, (괄호가 나올 때 까지 pop해준 후 push 해준다.
				buffer[j++] = a.pop();
			a.push(infix[i]);
			break;
		case '*': // top이 0 이상, ( 괄호가 나올 때 까지, +,- 기호가 나올 때 까지 pop 해준 후 push 해준다.
			while (a.get_top() >= 0 && a.set_stacktop() != '(' && a.set_stacktop() != '-' && a.set_stacktop() != '+')
				buffer[j++] = a.pop();
			a.push(infix[i]);
			break;
		case '/': // *와 /는 우선순위가 같다.
			while (a.get_top() >= 0 && a.set_stacktop() != '(' && a.set_stacktop() != '-' && a.set_stacktop() != '+')
				buffer[j++] = a.pop();
			a.push(infix[i]);
			break;
		case ')': // (를 만날때 까지 pop를 해준다.
			while (a.set_stacktop() != '(')
				buffer[j++] = a.pop();
			a.pop(); // (도 한번 더 pop 해준다.
			break;
		default: // 사칙연산이나 괄호가 아닌 숫자인 경우 그냥 출력한다.
			buffer[j++] = infix[i];
		}
	}
	while (!a.isEmpty())  // 스택이 비어있을 때 까지 pop 해준다.
		buffer[j++] = a.pop();
	
}

/****************************************************************************
function : int eval(char *str) postfix로 변환된 식을 계산하는 함수이다.
description : 위에서 변환된 식을 바탕으로 식이 끝날 때 까지 반복하며 숫자가
	나오면 이를 ascii코드값에 맞춰서 변환 후 스택에 psuh 해주고 만약 사칙연산
	중 하나가 나오면 앞에 두 수를 pop 해준 후 이 사칙연산에 맞는 계산을 하여
	다시 push 해준다. 이를 반복하면 마지막에 남는 식(수)를 pop 해주면 계산이
	완료 된다.
variables : precedence token은 위의 enum{}에서 기호에 맞는 것을 문자로 변환시켜
	이를 비교할 수 있게 끔 만든 변수이다.
	char symbol은 아래 함수에서 설명하겠지만 식 하나 하나를 읽기 위해 
	설정해준 변수이다.
	int op1, op2 변수는 스택에 넣어두었던 숫자를 pop 하고 이를 저장시켜서 계산
	하기 위해 만든 변수이다.
****************************************************************************/
int eval(char *str) {
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0; // 수식 스트링을 위한 카운터
	token = get_token(&symbol, &n, str);
	while (token != eos) {
		if (token == operand)
			a.push(symbol - '0'); // 스택 삽입, ASCII코드값에 맞춰주려고 0을 빼주었다.
		else {
			op2 = a.pop();
			op1 = a.pop();

			switch (token) {
			case pplus:
				a.push(op1 + op2);
				break;
			case mminus:
				a.push(op1 - op2);
				break;
			case times:
				a.push(op1 * op2);
				break;
			case divide:
				a.push(op1 / op2);
				break;
			case mod:
				a.push(op1 % op2);
			}
		}
		token = get_token(&symbol, &n, str);
	}
	return a.pop();
}
/****************************************************************************
function : precedence get_token 각 기호및 숫자에 맞는 값을 문자형태로 변환시켜준다.
description : char *symbol, int *n, char *infix를 매개변수로 받아서 이를 이용하여
	위에 변환된 식을 하나 하나씩 비교해가며 숫자 혹은 기호 혹은 NULL값을 비교해
	이를 문자로 변환 시켜 반환한다.
variables : symbol은 postfix로 변환된 식에서 처음부터 차례대로 하나하나 읽어 
	숫자 혹은 사칙연산을 읽게 된다.
	case NULL:은 식이 끝나면 이라는 의미이고 default는 위의 계산기호가 아닌
	숫자가 나올 때 oerand를 반환하는 것이다.
****************************************************************************/

precedence get_token(char *symbol, int *n, char *infix) {
	/*다음 도큰을 취한다. symbol은 문자 표현이며, token은 그것의 열거
	된 값으로 표현되고, 명칭으로 반환된다.*/
	*symbol = infix[(*n)++];

	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return pplus;
	case '-': return mminus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case NULL: return eos;
	default: return operand;
	}
}