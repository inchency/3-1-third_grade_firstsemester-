/*********************************************************
File Name : Hw3 SLL ADT.cpp
function : int List::isEmpty() SLL이 비어있으면 return 1;
	안비어있으면 return 0;
	void List::append(string dataA) temp라는 새로운 노드를 
		생성 후 노드를 마지막에 삽입해 주는 함수
	void List::Grade_display(char grade) 사용자가 원하는 
		성적만을 포함한 자료값을 출력해주는 함수
	void List::Major_display(char *major) 사용자가 원하는
		전공만을 포함한 자료값을 출력해 주는 함수
	void List::display() 아무런 조건 없이 모두 다 출력
		해 주는 함수
	void List::sort() 이름에 따라 알파벳 오름차순으로
		정렬해 주는 함수
description : SSL에 필요한 각종 함수들에 대한 정보가 있다.
variables : head는 list의 처음부분, temp는 새로운 노드를
	만들어주기 위함, data는 노드의 data값, next는 그 다음
	노드롤 가르킴
*********************************************************/

#include "HW3 SLL.h"

int List::isEmpty() {
	if (head == 0)
		return 1;
	else
		return 0;
}

void List::append(string dataA) { // 노드를 마지막에 삽입해주는 함수
	Node *temp = new Node; // 새로운 temp라는 노드 생성 후
	temp->data = dataA; // temp에 새로운 data값을 넣어주고
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

void List::Grade_display(char grade) { // 원하는 학점만 출력
	Node *ptr;
	ptr = head;
	while (ptr) {
		if (ptr->data.at(9) == grade)
			cout << ptr->data << endl;
		ptr = ptr->next;
	}
}

void List::Major_display(char *major) { // 원하는 전공만 출력
	Node *ptr;
	ptr = head;
	while (ptr) {
		if (ptr->data.at(6) == major[0] && ptr->data.at(7) == major[1])
			cout << ptr->data << endl;
		ptr = ptr->next;
	}
}

void List::display() { // 그냥 출력
	Node *ptr;
	ptr = head;
	while (ptr) {
		cout << ptr->data;
		ptr = ptr->next;
		cout << endl;
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
