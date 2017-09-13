#include <iostream>
#include <string>
#include "Stack.h"
#define MAX_SIZE 100

int main(int argc, char* argv[]) {
	int value;
	int sizeStack;
	string command;
	Stack Stack(MAX_SIZE);

	while (1) {
		cout << "Enter the command(push, pop, traverse, exit) : ";
		cin >> command;
		if (!command.compare("push")) {
			cout << "Enter the value: ";
			cin >> value;
			Stack.push(value);
		}
		else if (!command.compare("pop"))
			cout << Stack.pop() << endl;
		else if (!command.compare("traverse"))
			Stack.print();
		else if (!command.compare("exit"))
			exit(1);
		else
			cout << "Bad Command!" << endl;
	}
}