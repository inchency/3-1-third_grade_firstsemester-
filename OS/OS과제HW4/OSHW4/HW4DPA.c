#include "HW4DP.h"

int main(){
	int lock1, lock2, con1, con2;
	if((lock1 = initsem(L1_KEY,1)) < 0)
		exit(1);
	if((lock2 = initsem(L2_KEY,1)) < 0)
		exit(1);
	if((con1 = initsem(C1_KEY, 1)) < 0)
		exit(1);
	if((con2 = initsem(C2_KEY,1)) < 0)
		exit(1);
	Phil_A(lock1, lock2, con1, con2);

	return 0;
}