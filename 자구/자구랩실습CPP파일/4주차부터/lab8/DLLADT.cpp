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

void List::Insert_After(int num, string name, int num2) {
	Node *temp = new Node(num2, name);
	Node *p, *q;
	int count=0;
	int cnt = 0;
	
	if (!isEmpty()) {
		p = head;
		q = head;
		while ((p != 0)) { // temp data�� �������� �̵�
			q = p;
			p = p->next;
			count++;
		}
	}

	if (isEmpty() && num == 0)  // ù ����϶�
		head = temp;
	else if(isEmpty() && num !=0)
		cout << "����� ������ Nth ���ں��� �۽��ϴ�" << endl;
	if (!isEmpty() && count == num) { // �� �������� ��
		p = head;
		q = head;
		while ((p != 0)) {
			q = p;
			p = p->next;
		}
		q->next = temp;
		p->prev = temp;
	}

	if (!isEmpty() && num == 0) { // head �տ� ����, �Ǿ� ����
		temp->next = head;
		head->prev = temp;
	}
	else if (!isEmpty() && count<num)
		cout << "����� ������ Nth ���ں��� �۽��ϴ�" << endl;
	else if (!isEmpty() && count > num) {
		p = head;
		q = head;
		while ((p != 0) && (cnt != num)) {
			q = p;
			p = p->next;
			cnt++;
		}
		temp->next = p;
		temp->prev = q;
		q->next = temp;
		p->prev = temp;
	}
}

void List::Insert_Before(int num, string name, int num2) {
	Node *temp = new Node(num2, name);
	Node *p, *q;
	int count = 0;
	int cnt = 0;

	if (!isEmpty()) {
		p = head;
		q = head;
		while ((p != 0)) { // temp data�� �������� �̵�
			q = p;
			p = p->next;
			count++;
		}
	}

	if (isEmpty()) {  // ù ����϶�
		if (num == 0)
			head = temp;
		else if (num != 0)
			cout << "����� ������ Nth ���ں��� �۽��ϴ�" << endl;
	}

	else {
		if (num == 0) { // head �տ� ����, �Ǿ� ����
			temp->next = head;
			head->prev = temp;
		}
		else if (count < num)
			cout << "����� ������ Nth ���ں��� �۽��ϴ�" << endl;
		else if (count >= num) {
			p = head;
			q = head;
			if (count == 1) {
				temp->next = head;
				q->prev = temp;
				p->prev = temp;
			}
			else {
				while ((p != 0) && (cnt != num)) {
					q = p;
					p = p->next;
					cnt++;
				}
				p = q;
				q = q->prev;
				temp->next = p;
				temp->prev = q;
				q->next = temp;
				p->prev = temp;
			}
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
		if (p != 0)  // ���ϴ� num ���� List���� ã���� ���
			cout << num << " is in the List" << endl;
		else
			cout << num << " is not in the List" << endl;
	}
}

void List::find_Nth(int num) {
	Node *p, *q;
	if (isEmpty())
		cout << num << " is not found" << endl;
	else {
		p = head;
		q = head;
		int count = 0;
		int cnt = 0;
		while (p != 0) { // temp data�� �������� �̵�
			q = p;
			p = p->next;
			count++;
		}
		if (count >= num) {
			p = head;
			q = head;
			while (cnt != num) {
				q = p;
				p = p->next;
				cnt++;
			}
			cout << q->data << endl;
		}
	}

	
}

void List::forwardList() {
	if (isEmpty())
		cout << "Empty List" << endl;
	else {
		Node *p;
		p = head;
		cout << "----- Forward Listing -----" << endl;
		while (p != 0) {
			cout << p->data << " " << p->name << " ";
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