#include "LAB006 SLL.h"

int List::isEmpty() {
	if (head == 0)
		return 1;
	else
		return 0;
}

void List::quit() {
	exit(1);
}

/*
void List::insertNode(int data) {
	Node *temp=new Node;
	temp->data = data;
	Node *p, *q;
	q = head;

	if (isEmpty()) 
		head = temp;
	else if (temp->data < head->data) {  // �� �տ� ���Ե� ���
		temp->next = head;
		head = temp;
	}
	else {
		p = head;
		while ((p != 0) && (p->data < temp->data)) { 
			q = p;
			p = p->next;
		}
		if (p != 0) { // ��尡 �߰��� ���� �� ���
			temp->next = p;
			q->next = temp;
		}
		else // ��尡 �� �������� ���Ե� ���
			q->next = temp;
	}
}
*/

void List::deleteNode(int data){
	Node *p, *q;
	if(isEmpty())
		cout << "not found" << endl;
	else if (head->data == data){
		p = head;
		head = head->next;
		delete p;
	}
	else {
		p = head;
		q = head;
		while (p != 0 && p->data != data){
			q = p;
			p = p->next;
		}
		if (p != 0){
			q->next = p->next;
			delete p;
		}
		else
			cout <<"not found" << endl;
	}
}

void List::search(int data) { // �׳� ���
	Node *p;

	if (head != 0) { // ����Ʈ�� ������ ��
		p = head;
		while (p != 0 && p->data != data)
			p = p->next;
		if (p)  // �˻��Ȱ� ������
			cout << p->data <<" " << p->data2 << " is in the list" << endl;
		else
			cout << data << " is not in the list" << endl;
	}
	else
		cout << "List is empty" << endl;
}




void List::append(int data, string data2) { // ��带 �������� �������ִ� �Լ�
	Node *temp = new Node; // ���ο� temp��� ��� ���� ��
	temp->data = data; // temp�� ���ο� data���� �־��ְ�
	temp->data2 = data2;
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


/*
void List::Grade_display(char grade) { // ���ϴ� ������ ���
	Node *ptr;
	ptr = head;
	while (ptr) {
		if (ptr->data.at(9) == grade)
			cout << ptr->data << endl;
		ptr = ptr->next;
	}
}
*/
/*
void List::Major_display(char *major) { // ���ϴ� ������ ���
	Node *ptr;
	ptr = head;
	while (ptr) {
		if (ptr->data.at(6) == major[0] && ptr->data.at(7) == major[1])
			cout << ptr->data << endl;
		ptr = ptr->next;
	}
}
*/

void List::display() { // �׳� ���
	Node *ptr;
	ptr = head;
	while (ptr) {
		cout << ptr->data<<" " << ptr->data2 << "  " << endl;
		if (ptr)
			ptr = ptr->next;
		else
			cout << "List empty" << endl;
		//cout << endl;
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