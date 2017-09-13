/*******************************************************************************
ÀÌ¸§ : ±èµ¿ÈÆ
ÇÐ¹ø : 20123339
ID : LAB5 Stack And Queue Practice
date : 2016-04-6
*******************************************************************************/

#include <iostream>
#include <string>
#include "StackandQ.h"
#define STACK_SIZE 2
#define QUEUE_SIZE 3

using namespace std;

Stack S(STACK_SIZE);
Queue Q(QUEUE_SIZE);


int main() {
	string str;
	char a[100] = {};
	int count = 0;
	string b;
	cout << "Please input data push 'a'-> enque 'b'-> enque 'c'-> enque 'd'-> push 'e'" << endl;
	while (1) {
		cin >> str;
		if (str == "push") {
			cin >> a;
			while (!a[count] == NULL)
				count++;
			S.push(a[count-2]);
			//cout << "push " << a << endl;
		}
		else if (str == "pop") 
			cout << S.pop() << endl;
		else if (str == "enque" || str == "enqueue") {
			cin >> a;
			while (!a[count] == NULL)
				count++;
			Q.AddQ(a[count-2]);
			//cout << "enque " << a << endl;
		}
		else if (str == "deque" || str == "dequeue") 
			cout << Q.DeleteQ() << endl;
		else if (str == "Display") {
			cin >> b;
			if (b == "Stack")
				S.print();
			else if (b == "Queue")
				Q.Print();
			else
				cout << "Error, Retry!" << endl
		}
	}
}