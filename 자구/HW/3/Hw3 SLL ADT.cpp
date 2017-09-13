/*********************************************************
File Name : Hw3 SLL ADT.cpp
function : int List::isEmpty() SLL�� ��������� return 1;
	�Ⱥ�������� return 0;
	void List::append(string dataA) temp��� ���ο� ��带 
		���� �� ��带 �������� ������ �ִ� �Լ�
	void List::Grade_display(char grade) ����ڰ� ���ϴ� 
		�������� ������ �ڷᰪ�� ������ִ� �Լ�
	void List::Major_display(char *major) ����ڰ� ���ϴ�
		�������� ������ �ڷᰪ�� ����� �ִ� �Լ�
	void List::display() �ƹ��� ���� ���� ��� �� ���
		�� �ִ� �Լ�
	void List::sort() �̸��� ���� ���ĺ� ������������
		������ �ִ� �Լ�
description : SSL�� �ʿ��� ���� �Լ��鿡 ���� ������ �ִ�.
variables : head�� list�� ó���κ�, temp�� ���ο� ��带
	������ֱ� ����, data�� ����� data��, next�� �� ����
	���� ����Ŵ
*********************************************************/

#include "HW3 SLL.h"

int List::isEmpty() {
	if (head == 0)
		return 1;
	else
		return 0;
}

void List::append(string dataA) { // ��带 �������� �������ִ� �Լ�
	Node *temp = new Node; // ���ο� temp��� ��� ���� ��
	temp->data = dataA; // temp�� ���ο� data���� �־��ְ�
	temp->next = 0; // temp�� ����Ű�°��� �����Ѵ�.
	if (isEmpty())
		head = temp;
	else {
		Node *ptr = head;
		while (ptr->next != 0) // �� ������ ���� ����.
			ptr = ptr->next;
		ptr->next = temp; // �� ������ ����Ʈ���� temp ��带 �߰����ش�.
	}
}

void List::Grade_display(char grade) { // ���ϴ� ������ ���
	Node *ptr;
	ptr = head;
	while (ptr) {
		if (ptr->data.at(9) == grade)
			cout << ptr->data << endl;
		ptr = ptr->next;
	}
}

void List::Major_display(char *major) { // ���ϴ� ������ ���
	Node *ptr;
	ptr = head;
	while (ptr) {
		if (ptr->data.at(6) == major[0] && ptr->data.at(7) == major[1])
			cout << ptr->data << endl;
		ptr = ptr->next;
	}
}

void List::display() { // �׳� ���
	Node *ptr;
	ptr = head;
	while (ptr) {
		cout << ptr->data;
		ptr = ptr->next;
		cout << endl;
	}
}

void List::sort() {  // �������ִ� �Լ�
	Node *temp, **p;
	int count;

	temp = head;
	count = 0;
	while (temp != NULL) { // Singly linked List�� ������ Ȯ������
		count++;
		temp = temp->next;
	}
	p = (Node**)malloc(sizeof(Node*) * count); //p = (Node**) new Node; �� ��������
	temp = head;
	for (int i = 0; i < count; i++) { //p�� Singly linked List���� ����
		p[i] = temp;
		temp = temp->next;
	}

	for (int i = 0; i < count; i++) { // ���� ũ�⸸ŭ ����
		for (int j = i + 1; j < count; j++) {
			if (p[j]->data < p[i]->data) { // �տ����� ũ�� swap (�������� ����)
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
	head = p[0];
	temp = head;
	for (int i = 0; i < count - 1; i++) { // ���������� p�� �̿��� SLL�� �ٽ� �������
		temp->next = p[i + 1];
		temp = temp->next;
	}
	temp->next = 0;
	free(p); // p = (Node**)malloc(sizeof(Node*) * count) ���� �� delete p; 
}
