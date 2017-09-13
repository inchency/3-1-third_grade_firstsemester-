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
	else if (temp->data < head->data) {  // 맨 앞에 삽입될 경우
		temp->next = head;
		head = temp;
	}
	else {
		p = head;
		while ((p != 0) && (p->data < temp->data)) { 
			q = p;
			p = p->next;
		}
		if (p != 0) { // 노드가 중간에 삽입 될 경우
			temp->next = p;
			q->next = temp;
		}
		else // 노드가 맨 마지막에 삽입될 경우
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

void List::search(int data) { // 그냥 출력
	Node *p;

	if (head != 0) { // 리스트가 존재할 때
		p = head;
		while (p != 0 && p->data != data)
			p = p->next;
		if (p)  // 검색된게 있으면
			cout << p->data <<" " << p->data2 << " is in the list" << endl;
		else
			cout << data << " is not in the list" << endl;
	}
	else
		cout << "List is empty" << endl;
}




void List::append(int data, string data2) { // 노드를 마지막에 삽입해주는 함수
	Node *temp = new Node; // 새로운 temp라는 노드 생성 후
	temp->data = data; // temp에 새로운 data값을 넣어주고
	temp->data2 = data2;
	temp->next = 0; // temp가 가르키는것은 없게한다.
	if (isEmpty())
		head = temp;
	else {
		Node *ptr = head;
		while (ptr->next != 0) // 맨 마지막 까지 간다.
			ptr = ptr->next;
		ptr->next = temp; // 맨 마지막 리스트에서 temp 노드를 추가해준다.
	}
}


/*
void List::Grade_display(char grade) { // 원하는 학점만 출력
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
void List::Major_display(char *major) { // 원하는 전공만 출력
	Node *ptr;
	ptr = head;
	while (ptr) {
		if (ptr->data.at(6) == major[0] && ptr->data.at(7) == major[1])
			cout << ptr->data << endl;
		ptr = ptr->next;
	}
}
*/

void List::display() { // 그냥 출력
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

 void List::sort() {  // 정렬해주는 함수
	Node *temp, **p;
	int count;

	temp = head;
	count = 0;
	while (temp != NULL) { // Singly linked List의 갯수를 확인해줌
		count++;
		temp = temp->next;
	}
	p = (Node**)malloc(sizeof(Node*) * count); //p = (Node**) new Node; 와 같은문장
	temp = head;
	for (int i = 0; i < count; i++) { //p에 Singly linked List값을 삽입
		p[i] = temp;
		temp = temp->next;
	}

	for (int i = 0; i < count; i++) { // 갯수 크기만큼 실행
		for (int j = i + 1; j < count; j++) {
			if (p[j]->data < p[i]->data) { // 앞에것이 크면 swap (오름차순 정렬)
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
	head = p[0];
	temp = head;
	for (int i = 0; i < count - 1; i++) { // 위에서구한 p를 이용해 SLL을 다시 만들어줌
		temp->next = p[i + 1];
		temp = temp->next;
	}
	temp->next = 0;
	free(p); // p = (Node**)malloc(sizeof(Node*) * count) 썼을 땐 delete p; 
}