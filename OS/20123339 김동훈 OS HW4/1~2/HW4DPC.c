#include "HW4DP.h"

int main(){
	int i;
	int lock3, lock1, con3, con1;
	if((lock3 = initsem(L3_KEY,1)) < 0)
		exit(1);
	if((lock1 = initsem(L1_KEY,1)) < 0)
		exit(1);
	if((con3 = initsem(C3_KEY, 1)) < 0)
		exit(1);
	if((con1 = initsem(C1_KEY,1)) < 0)
		exit(1);
	for(i=0; i<100; i++)
		Phil_C(lock3, lock1, con3, con1);
	return 0;
}