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

void List::Insert_After(int num, string name, int num2) {
	Node *temp = new Node(num2, name);
	Node *p, *q;
	int count=0;
	int cnt = 0;
	
	if (!isEmpty()) {
		p = head;
		q = head;
		while ((p != 0)) { // temp data값 직전까지 이동
			q = p;
			p = p->next;
			count++;
		}
	}

	if (isEmpty() && num == 0)  // 첫 노드일때
		head = temp;
	else if(isEmpty() && num !=0)
		cout << "노드의 갯수가 Nth 숫자보다 작습니다" << endl;
	if (!isEmpty() && count == num) { // 맨 마지막일 때
		p = head;
		q = head;
		while ((p != 0)) {
			q = p;
			p = p->next;
		}
		q->next = temp;
		p->prev = temp;
	}

	if (!isEmpty() && num == 0) { // head 앞에 삽입, 맨앞 삽입
		temp->next = head;
		head->prev = temp;
	}
	else if (!isEmpty() && count<num)
		cout << "노드의 갯수가 Nth 숫자보다 작습니다" << endl;
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
		while ((p != 0)) { // temp data값 직전까지 이동
			q = p;
			p = p->next;
			count++;
		}
	}

	if (isEmpty()) {  // 첫 노드일때
		if (num == 0)
			head = temp;
		else if (num != 0)
			cout << "노드의 갯수가 Nth 숫자보다 작습니다" << endl;
	}

	else {
		if (num == 0) { // head 앞에 삽입, 맨앞 삽입
			temp->next = head;
			head->prev = temp;
		}
		else if (count < num)
			cout << "노드의 갯수가 Nth 숫자보다 작습니다" << endl;
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
		if (p != 0)  // 원하는 num 값을 List에서 찾으면 출력
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
		while (p != 0) { // temp data값 직전까지 이동
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