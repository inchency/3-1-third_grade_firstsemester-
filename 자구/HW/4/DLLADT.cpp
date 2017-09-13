/*********************************************************
File Name : DLLADT.cpp
function : int List::isEmpty() SLL�� ��������� return true;
	�Ⱥ�������� return false;
void List::Insert(int num, string name) temp��� ���ο� ��带 
	���� �� ��ó�� Ȥ�� �߰� Ȥ�� �������� �������� (���ڿ�������)
void List::Delete(int num) ����ڰ� ���ϴ� ���ڸ� ����Ʈ����
	ã�Ƽ� �� �ش� ��带 ������ �� �� �� �������� ������ ��
	������ �����־����
void List::Search(int num) ����ڰ� ���ϴ� ���ڸ� �˻��ؼ�
	������ �� ���ڿ� �ִٴ� ������ ��Ÿ���ְ� ������ ���ٰ�
	�������
void List::forwardList() ���� ����Ʈ�� ��ϵǾ� �ִ� ������
	������ �տ������� ������� �������
void List::backwardList() ���� ����Ʈ�� ��ϵǾ� �ִ� �����̤�
	������ �ڿ������� ������� ������� p, q�� �̿��ؼ�
	������ ������ ���� �� �ٽ� �������� �����鼭 ����ϴ�
	����� �����
void List::Quit() ���α׷� ����
description : DDL�� �ʿ��� ���� �Լ��鿡 ���� ������ �ִ�.
variables : head�� list�� ó���κ�, temp�� ���ο� ��带
������ֱ� ����, data�� ����� data��, name�� ����� �̸���,
next�� �� ���� ��带 ����Ŵ prev�� �� �� ��带 ����Ŵ
*********************************************************/

#include "DLL.h"

bool List::isEmpty() {
	if (head == NULL)
		return true;
	else
		return false;
}

void List::Insert(int num, string name) {
	Node *temp = new Node(num, name);
	Node *p, *q;

	if (isEmpty()) // ù ����϶�
		head = temp;
	else if (temp->data < head->data) { // head �տ� ����
		temp->next = head;
		head->prev = temp;
	}
	else { // ��� ����
		p = head;
		q = head;
		while ((p != 0) && (p->data < temp->data)) { // temp data�� �������� �̵�
			q = p;
			p = p->next;
		}
		if (p != 0) { // �߰��� ��� temp->data���� List�� �־��ش�. 
			temp->next = p;
			q->next = temp;
			temp->prev = q;
			p->prev = temp;
		}
		else { // temp�� Ŀ�� �� �������� ���� �� ���
			q->next = temp;
			temp->prev = q;
		}
	}
}

void List::Delete(int num) {
	Node *p, *q;
	if (isEmpty())
		cout << "Not found" << endl;
	if (head->data == num) { // ���� ���� �� ���� ���
		if (head->next == NULL) { // ����Ʈ�� ��尡 ��� �ϳ��� ������ ���
			p = head;
			head = NULL;
			cout << num << " is deleted" << endl;
			delete p;
		}
		else { // ���ﰪ�� ����̸鼭 ����Ʈ�� ��� �޺κп� ��尡 �� ���� ���
			p = head;
			head = head->next;
			head->prev = NULL;
			cout << num << " is deleted" << endl;
			delete p;
		}
	}
	else { // ��� ��尡 ������ ���
		p = head;
		q = head;
		while ((p != 0) && (p->data != num)) {
			q = p;
			p = p->next;
		}
		if (p != 0) { // List �߰����� �����Ұ� ���� ��
			if (p->next != NULL) { // �� ������ ������ �ƴѰ��
				q->next = p->next;
				p->next->prev = q;
				cout << num << " is deleted" << endl;
				delete p;
			}
			else {  // �� ������ ������ ���
				q->next = NULL;
				cout << num << " is deleted" << endl;
				delete p;
			}
		}
		else
			cout << "Not found" << endl;
	}
}

void List::Search(int num) {
	if (isEmpty())
		cout << num << " is not found" << endl;
	else {
		Node *p = head;
		while ((p != 0) && (p->data != num))
			p = p->next;
		if (p!=0)  // ���ϴ� num ���� List���� ã���� ���
			cout << num << " is in the List" << endl;
		else
			cout << num << " is not in the List" << endl;
	}
}

void List::forwardList() {
	if (isEmpty())
		cout << "Empty List" << endl;
	else {
		Node *p = head;
		cout << "----- Forward Listing -----" << endl;
		while (p != 0) {
			cout << p->data << " " << p->name<< " ";
			p = p->next;
		}
		cout << endl << "---------------------------" << endl;
	}
}

void List::backwardList() {
	if (isEmpty())
		cout << "List is empty" << endl;
	else {
		Node *p = head;
		Node *q = head;
		while (p != 0) {
			q = p;
			p = p->next;
		}
		cout << "----- Backward Listing -----" << endl;
		while (q != 0) {
			p = q;
			q = q->prev;
			cout << p->data << " " << p->name << " ";
		}
		cout << endl << "----------------------------" << endl;
	}
}

void List::Quit() {
	exit(1);
}