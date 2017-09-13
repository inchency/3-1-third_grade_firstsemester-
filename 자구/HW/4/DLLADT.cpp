/*********************************************************
File Name : DLLADT.cpp
function : int List::isEmpty() SLL이 비어있으면 return true;
	안비어있으면 return false;
void List::Insert(int num, string name) temp라는 새로운 노드를 
	생성 후 맨처음 혹은 중간 혹은 마지막에 삽입해줌 (숫자오름차순)
void List::Delete(int num) 사용자가 원하는 숫자를 리스트에서
	찾아서 그 해당 노드를 삭제해 줌 이 때 여러가지 조건을 잘
	따져서 지워주어야함
void List::Search(int num) 사용자가 원하는 숫자를 검색해서
	있으면 그 숫자와 있다는 내용을 나타내주고 없으면 없다고
	출력해줌
void List::forwardList() 현재 리스트에 기록되어 있는 노드들의
	정보를 앞에서부터 순서대로 출력해줌
void List::backwardList() 현재 리스트에 기록되어 있는 노드들이ㅡ
	정보를 뒤에서부터 순서대로 출력해줌 p, q를 이용해서
	오른쪽 끝까지 보낸 후 다시 왼쪽으로 보내면서 출력하는
	방법을 사용함
void List::Quit() 프로그램 종료
description : DDL에 필요한 각종 함수들에 대한 정보가 있다.
variables : head는 list의 처음부분, temp는 새로운 노드를
만들어주기 위함, data는 노드의 data값, name은 노드의 이름값,
next는 그 다음 노드를 가르킴 prev는 그 전 노드를 가르킴
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

	if (isEmpty()) // 첫 노드일때
		head = temp;
	else if (temp->data < head->data) { // head 앞에 삽입
		temp->next = head;
		head->prev = temp;
	}
	else { // 가운데 삽입
		p = head;
		q = head;
		while ((p != 0) && (p->data < temp->data)) { // temp data값 직전까지 이동
			q = p;
			p = p->next;
		}
		if (p != 0) { // 중간일 경우 temp->data값을 List에 넣어준다. 
			temp->next = p;
			q->next = temp;
			temp->prev = q;
			p->prev = temp;
		}
		else { // temp가 커서 맨 마지막에 삽입 될 경우
			q->next = temp;
			temp->prev = q;
		}
	}
}

void List::Delete(int num) {
	Node *p, *q;
	if (isEmpty())
		cout << "Not found" << endl;
	if (head->data == num) { // 지울 값이 맨 앞인 경우
		if (head->next == NULL) { // 리스트에 노드가 헤드 하나만 남았을 경우
			p = head;
			head = NULL;
			cout << num << " is deleted" << endl;
			delete p;
		}
		else { // 지울값이 헤드이면서 리스트의 헤드 뒷부분에 노드가 더 있을 경우
			p = head;
			head = head->next;
			head->prev = NULL;
			cout << num << " is deleted" << endl;
			delete p;
		}
	}
	else { // 가운데 노드가 삭제될 경우
		p = head;
		q = head;
		while ((p != 0) && (p->data != num)) {
			q = p;
			p = p->next;
		}
		if (p != 0) { // List 중간에서 삭제할게 있을 때
			if (p->next != NULL) { // 맨 마지막 삭제가 아닌경우
				q->next = p->next;
				p->next->prev = q;
				cout << num << " is deleted" << endl;
				delete p;
			}
			else {  // 맨 마지막 삭제인 경우
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
		if (p!=0)  // 원하는 num 값을 List에서 찾으면 출력
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