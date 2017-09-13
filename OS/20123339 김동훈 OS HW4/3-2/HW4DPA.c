#include "HW4DP.h"

void Phil_A(){
	int lock1, lock2, lock3, con1, con2, con3;
	int NewLock; // all lock
	if((lock1 = initsem(L1_KEY,1)) < 0)
		exit(1);
	if((lock2 = initsem(L2_KEY,1)) < 0)
		exit(1);
	if((lock3 = initsem(L3_KEY,1)) < 0)
		exit(1);
	if((con1 = initsem(C1_KEY, 1)) < 0)
		exit(1);
	if((con2 = initsem(C2_KEY,1)) < 0)
		exit(1);
	if((con3 = initsem(C3_KEY,1)) < 0)
		exit(1);
	if((NewLock = initsem(NL_KEY,1)) < 0)
		exit(1);

	Acquire(NewLock);
	Take_R1(lock1,con1);
	Take_R2(lock2,con2);
	Take_R3(lock3,con3);  //  Have all chopsticks.
	Release(NewLock);

	think(); // getpid() starting thingking. (sleep();)
	eating(); // getpid() starting eating (sleep());
	//getpid() stop eating

	Put_R1(lock1, con1);
	Put_R2(lock2, con2);
	Put_R3(lock3, con3);
	//put all chopsticks
}

int main(){
	int i;
	for(i=0; i<100; i++)
		Phil_A();
	return 0;
}