#include "HW4DP.h"

int main(){
	int i;
	int lock2, lock3, con2, con3;
	if((lock2 = initsem(L2_KEY,1)) < 0)
		exit(1);
	if((lock3 = initsem(L3_KEY,1)) < 0)
		exit(1);
	if((con2 = initsem(C2_KEY, 1)) < 0)
		exit(1);
	if((con3 = initsem(C3_KEY,1)) < 0)
		exit(1);
	for(i=0; i<100; i++)
		Phil_B(lock2, lock3, con2, con3);
	return 0;
}