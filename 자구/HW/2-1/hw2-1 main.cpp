/****************************************************************************
Name : �赿��
Student ID : 20123339
Program ID : HW#2-1 Infix to Postfix Conversion & Postfix Evaluation
Description : buffer�� �����͸� �޾Ƶ鿩�� ��ȣ�� ���� ���� ��Ī�ϸ� balance
			  ��Ī���� ������ unbalance�� ����Ѵ�. 
Algorithm : �����͸� ���پ� �о buffer���� ���� �� '{,[,(' �� ���� ���� ��ȣ�� ������
	���ÿ� ������ push ���ְ� �ݴ°�ȣ '}' �� ������ �켱������ ������ ����ִ°���
	�˻� �� �� ��������� unbalance �� ��� �� ���߿� ���������� Ȯ���� �κп���
	�ߺ����� �ʰ� check�� 1�� �ٲپ��ش�. �׸��� �񱳹��� �������´�. 
	������� ������ '}'�� ��Ī�Ǵ� '{' �ΰ��� �Ǻ��ϴµ� ���� ������ ��� 
	�������� �Ѿ��. ���� ��ġ ���� ������ ������ unbalance�� ���̹Ƿ� unbalance�� 
	����ϰ� ���� check�� 1�� ��ȭ�����ش�. ���̻� ���� �ʿ䰡 �����Ƿ� �������´�. 
	���������� ']'�� ')'�� �����ְ� ��� �� �� ������ ����� �ִ� ���¶�� balance�� 
	�����̴� balance�� ���, �׷��� ���� ���� unbalance���� ��������̴�. 
	�׷��� �� �� �ߺ� ����� �� �� ������ �Ʊ� check=1�� �� ���� ������ ��츸 ����ϰ� �Ѵ�. 
	�׸��� ����� ���� ���� ������ ����� �� ���� pop �ؼ� empty�ϰ� ����� �ش�.
Variables : Ŭ���� Stack a,void balance(char *bf, int len, int check), 
	void print_Unbal(int len), void print_Bal(int len) �Լ����� ����Ͽ���
****************************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include "Stack.h"
#define MAX_SIZE 100

Stack a(MAX_SIZE); // ũ�Ⱑ 100�� ���� a ����
void balance(char *bf, int len, int check); // balance���� unbalance���� �����ִ� �Լ�
void print_Unbal(int len); // unbalance�� ��츦 ����� �ִ� �Լ�
void print_Bal(int len);  // balance�� ��츦 ����� �ִ� �Լ�

/****************************************************************************
function : int main()  ���� �Լ�
description : input.txt���� �����Ͱ��� �о� �ӽ� ���۹迭�� ������ �� balance 
			�Լ��� ȣ���Ѵ�.
variables : char buffer[MAX_SIZE] : �����Ͱ��� ���� �� �ִ� �迭 ũ�Ⱑ 100��
			�ӽ÷� �����ų ����
			int len : ������ ���� �Է¹��� ���̺����̴�.
			int check : unbalanced �ߺ� ����� ���� ���� ������ �����̴�.
****************************************************************************/
int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt�� ã�� �� �����ϴ�" << endl;
		return -1;
	}
	char buffer[MAX_SIZE];
	while (instream.getline(buffer, 80)) {  // ���پ� �а� �ִ� 80����Ʈ���� �о buffer�� ����
		int len = strlen(buffer);
		int check = 0;  //  unbalance���� �ߺ� unbalance ����� ���� ���� ������ ����
		for (int k = 0; k < len; k++) { // �о���� ���� ���
			cout << buffer[k];
		}
		balance(buffer, len, check);
	}
	return 0;
}
/****************************************************************************
function : void balance(char *buffer, int len, int check)  :  
			balance���� �ƴ��� Ȯ���� �ִ� �Լ�
description : ���� ��ȣ�� ������ ������ stack�� ���� �ְ� �ݴ� ��ȣ�� ������
		������ ����ִ����� �켱 Ȯ���� �� ��������� unbalanced �ƴϸ�
		��ȣ�� ������ ���� if���� ���� �� ������ ���� ������.
****************************************************************************/
void balance(char *buffer, int len, int check) { // balance���� �ƴ��� Ȯ���� �ִ� �Լ�
	for (int i = 0; i < len; i++) {
		if (buffer[i] == '{' || buffer[i] == '[' || buffer[i] == '(') // ���� ��ȣ�� ������ push
			a.push(buffer[i]);
		else if (buffer[i] == '}') {  // }�� ��ȣ�� ������
			if (a.isEmpty()) { // ����ִ� ���� unbalance�� ���
				print_Unbal(len);
				check = 1; // �����ֱ� ���� ���� check�� 1�� ����
				break;
			}
			else if (a.pop() == '{')  // '{' �̸� ��Ī�Ǵ� ���̹Ƿ� ��� ����
				continue;
			else { // ��Ī���� �ʴ� ��ȣ�� ������ unbalance����ϰ� check=1�� ����
				print_Unbal(len);
				check = 1;
				break;
			}
		}
		else if (buffer[i] == ']') { // ���� ���� ����̴�.
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
		else if (buffer[i] == ')') { // ���� ���� ����̴�.
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
	if (a.isEmpty()) // ������ ����� ������ ��� ��Ī�Ǽ� balance�� ����̹Ƿ� balance ���
		print_Bal(len);
	else if (!a.isEmpty() && check == 0)  // ������ ��������� �ʰ� check�� 0�� ��� unbalance�� ��� �̹Ƿ� unbalance check==0�� ������ �ߺ���� ���� ����
		print_Unbal(len);
	else if (!a.isEmpty()) // ������ ��������� ������ ����������� pop ���ش�
		while (a.isEmpty())
			a.pop();
}


/****************************************************************************
function : void print_Unbal(int len) : ���Ŀ� �°Բ� unbalanced�� ������ִ� �Լ�
description : ��� ���Ŀ� �°Բ� unbalanced�� ����� �ش�.
****************************************************************************/
void print_Unbal(int len) { // ���Ŀ� �°Բ� unbalanced�� ������ִ� �Լ�
	for (int i = 0; i < 20 - len; i++) {
		cout << " ";
	}
	cout << "unbalanced" << endl;
}
/****************************************************************************
function : void print_Unbal(int len) : ���Ŀ� �°Բ� balanced�� ������ִ� �Լ�
description : ��� ���Ŀ� �°Բ� balanced�� ����� �ش�.
****************************************************************************/
void print_Bal(int len) {  // ���Ŀ� �°Բ� balanced�� ������ִ� �Լ�
	for (int i = 0; i < 20 - len; i++) {
		cout << " ";
	}
	cout << "balanced" << endl;
}