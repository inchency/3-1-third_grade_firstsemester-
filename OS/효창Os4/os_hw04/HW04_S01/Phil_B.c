#include "head.h"

void Phil_B() {
	int lock2, lock3, c2, c3;

	//초기값이 1(FREE)인 semaphore들을 만듬
	if ((lock2 = initsem(L2, 1)) < 0)
		exit(1);
	if ((lock3 = initsem(L3, 1)) < 0)
		exit(1);
	if ((c2 = initsem(C2, 1)) < 0)
		exit(1);
	if ((c3 = initsem(C3, 1)) < 0)
		exit(1);

	Take_R2(lock2, c2);
	// getpid()가  생각을 시작함
	think();
	// getpid()가  생각을 멈춤
	Take_R3(lock3, c3);
	// getpid()가  먹기 시작함
	eating(); // sleep()으로 구현
			  // getpid()가  먹기를 멈춤
	Put_R2(lock2, c2);
	Put_R3(lock3, c3);

	FILE *fp = fopen("Count.txt", "a+");
	fprintf(fp, "%d : Finish Eating\n", getpid());
	fclose(fp);
}

void main()
{
	Phil_B();
}
