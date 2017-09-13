#include "head.h"

void Phil_C() {
	int lock1, lock3, c1, c3;

	//초기값이 1(FREE)인 semaphore들을 만듬
	if ((lock1 = initsem(L1, 1)) < 0)
		exit(1);
	if ((lock3 = initsem(L3, 1)) < 0)
		exit(1);
	if ((c1 = initsem(C1, 1)) < 0)
		exit(1);
	if ((c3 = initsem(C3, 1)) < 0)
		exit(1);

	Take_R3(lock3, c3);
	// getpid()가  생각을 시작함
	think();
	// getpid()가  생각을 멈춤
	Take_R1(lock1, c1);
	// getpid()가  먹기 시작함
	eating(); // sleep()으로 구현
	// getpid()가  먹기를 멈춤
	Put_R3(lock3, c3);
	Put_R1(lock1, c1);

	FILE *fp = fopen("Count.txt", "a+");
	fprintf(fp, "%d : Finish Eating\n", getpid());
	fclose(fp);
}

void main()
{
	Phil_C();
}
