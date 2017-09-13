/****************************************************************************
Name : �赿��
Student ID : 20123339
Program ID : HW#2-2 Infix to Postfix Conversion & Postfix Evaluation
Description : Ű����κ��� ���ĵ����͸� �Է� �޾� infix�� postfix�� ��ȯ �� 
	����ϰ� postfix evaluation �˰����� ����� �������� ����Ѵ�.
Algorithm : postfix�� ��ȯ�ϴ� �˰����� �켱������ '*'= '/'  >  '+'= '-'  >  '('
	�� ���ؼ� (�� ������ ������ push +,-�� ������ top�� 0�̻��̰� (��ȣ��
	���� �� ���� pop ���� �� push ���ش�. *,/�� ������ top�� 0 �̻�, ( ��ȣ�� 
	���� �� ����, +,- ��ȣ�� ���� �� ���� pop ���� �� push ���ش�. ) ��ȣ��
	������ (�� ���� �� ���� pop ���ش�. �׸��� ���������� ������ ����� ��
	���� pop ���ָ� ��ȯ�� �Ϸ� �ȴ�.
	�� ��ȯ �� ���� �ӽù��۹迭 ������ ���� �Ͽ� ���ÿ� ���ڸ� �װ� ��Ģ������
	������ �� ���� pop �� �� ��� �� ���� �� ���� ���� �ٽ� push�Ѵ�. ����
	���� �� ���� �ݺ� �ϸ� �������� ���� ���� pop �ϸ� ��� �� ��� ���� ���´�.
Variables : Ŭ���� Stack a, typedef enum{}precedence, void postfix(),
	precedence get_token, char buffer[] ���� ������ �Լ��� ����Ͽ���.
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
function : int main()  ���� �Լ�
description : Ű����κ��� ���� �����͸� �޾� �鿩�� postfix�Լ��� eval �Լ���
	���� ��ȯ, ����� ���� �Ͽ� �̸� ����Ѵ�.
variables : int len ������ ���� ���̸� ���� ���� �����̴�.
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
function : void postfix(char *infix, int len) infix���� postfix�� ��ȯ�ϴ�
	�Լ��̴�.
description : '*'= '/'  >  '+'= '-'  >  '('  �� �켱������ (��ȣ�� ������
	������ push�ϰ� +,-�� ������ *,/���� �켱������ �����Ƿ� top�� 0�̻�,
	(��ȣ�� ���� �� ���� pop�� ���� �� +,-�� push ���ش�. *,/�� ������ �̴�
	+,-���� �켱������ �����Ƿ� ���� ���ǿ� +or-�� ���� �� ���� pop ���� ��
	push�ִ� ������ �߰��� �ش�. �� �켱������ ���ؼ� �տ� ���� pop ��������
	�����Ѵ�. �� �켱������ ���� ����) ��ȣ�� ������ (�� ���� �� ���� pop���ָ�
	�ȴ�. �� �� (��ȣ�� ���ֱ� ���� �ѹ� �� pop ���ش�. �� ������ �� ��
	stack�� ����� �� ���� pop �ϸ� postfix���� ��ȯ�� �Ϸ� �ȴ�.
variables : char *infix�� ������ ���� ���� ����Ű�� �����̸� �̸� �迭�� ��Ÿ
	�� ���̴�. �� ������ ���� ���ÿ� push �Ѵ�.
	int len ������ ���� ���� ���̸� �ޱ� ���� �Ű������̴�.
****************************************************************************/
void postfix(char *infix, int len) {    // �켱���� '*'= '/'  >  '+'= '-'  >  '('  
	int j = 0;
	for (int i = 0; i < len; i++) {
		switch (infix[i]) {
		case '(': // (��ȣ�� ������ ������ push ���ش�.
			a.push(infix[i]);
			break;
		case '+':
			while (a.get_top() >= 0 && a.set_stacktop() != '(') // top�� 0�̻�, (��ȣ�� ���� �� ���� pop���� �� push ���ش�.
				buffer[j++] = a.pop();
			a.push(infix[i]);
			break;
		case '-': // -�� +�� �켱������ ����.
			while (a.get_top() >= 0 && a.set_stacktop() != '(') // top�� 0�̻�, (��ȣ�� ���� �� ���� pop���� �� push ���ش�.
				buffer[j++] = a.pop();
			a.push(infix[i]);
			break;
		case '*': // top�� 0 �̻�, ( ��ȣ�� ���� �� ����, +,- ��ȣ�� ���� �� ���� pop ���� �� push ���ش�.
			while (a.get_top() >= 0 && a.set_stacktop() != '(' && a.set_stacktop() != '-' && a.set_stacktop() != '+')
				buffer[j++] = a.pop();
			a.push(infix[i]);
			break;
		case '/': // *�� /�� �켱������ ����.
			while (a.get_top() >= 0 && a.set_stacktop() != '(' && a.set_stacktop() != '-' && a.set_stacktop() != '+')
				buffer[j++] = a.pop();
			a.push(infix[i]);
			break;
		case ')': // (�� ������ ���� pop�� ���ش�.
			while (a.set_stacktop() != '(')
				buffer[j++] = a.pop();
			a.pop(); // (�� �ѹ� �� pop ���ش�.
			break;
		default: // ��Ģ�����̳� ��ȣ�� �ƴ� ������ ��� �׳� ����Ѵ�.
			buffer[j++] = infix[i];
		}
	}
	while (!a.isEmpty())  // ������ ������� �� ���� pop ���ش�.
		buffer[j++] = a.pop();
	
}

/****************************************************************************
function : int eval(char *str) postfix�� ��ȯ�� ���� ����ϴ� �Լ��̴�.
description : ������ ��ȯ�� ���� �������� ���� ���� �� ���� �ݺ��ϸ� ���ڰ�
	������ �̸� ascii�ڵ尪�� ���缭 ��ȯ �� ���ÿ� psuh ���ְ� ���� ��Ģ����
	�� �ϳ��� ������ �տ� �� ���� pop ���� �� �� ��Ģ���꿡 �´� ����� �Ͽ�
	�ٽ� push ���ش�. �̸� �ݺ��ϸ� �������� ���� ��(��)�� pop ���ָ� �����
	�Ϸ� �ȴ�.
variables : precedence token�� ���� enum{}���� ��ȣ�� �´� ���� ���ڷ� ��ȯ����
	�̸� ���� �� �ְ� �� ���� �����̴�.
	char symbol�� �Ʒ� �Լ����� �����ϰ����� �� �ϳ� �ϳ��� �б� ���� 
	�������� �����̴�.
	int op1, op2 ������ ���ÿ� �־�ξ��� ���ڸ� pop �ϰ� �̸� ������Ѽ� ���
	�ϱ� ���� ���� �����̴�.
****************************************************************************/
int eval(char *str) {
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0; // ���� ��Ʈ���� ���� ī����
	token = get_token(&symbol, &n, str);
	while (token != eos) {
		if (token == operand)
			a.push(symbol - '0'); // ���� ����, ASCII�ڵ尪�� �����ַ��� 0�� ���־���.
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
function : precedence get_token �� ��ȣ�� ���ڿ� �´� ���� �������·� ��ȯ�����ش�.
description : char *symbol, int *n, char *infix�� �Ű������� �޾Ƽ� �̸� �̿��Ͽ�
	���� ��ȯ�� ���� �ϳ� �ϳ��� ���ذ��� ���� Ȥ�� ��ȣ Ȥ�� NULL���� ����
	�̸� ���ڷ� ��ȯ ���� ��ȯ�Ѵ�.
variables : symbol�� postfix�� ��ȯ�� �Ŀ��� ó������ ���ʴ�� �ϳ��ϳ� �о� 
	���� Ȥ�� ��Ģ������ �а� �ȴ�.
	case NULL:�� ���� ������ �̶�� �ǹ��̰� default�� ���� ����ȣ�� �ƴ�
	���ڰ� ���� �� oerand�� ��ȯ�ϴ� ���̴�.
****************************************************************************/

precedence get_token(char *symbol, int *n, char *infix) {
	/*���� ��ū�� ���Ѵ�. symbol�� ���� ǥ���̸�, token�� �װ��� ����
	�� ������ ǥ���ǰ�, ��Ī���� ��ȯ�ȴ�.*/
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