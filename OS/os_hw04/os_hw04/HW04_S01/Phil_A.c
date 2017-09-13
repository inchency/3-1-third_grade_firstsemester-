#include "head.h"

void Phil_A() {
	int lock1, lock2, c1, c2;

	//초기값이 1(FREE)인 semaphore들을 만듬
	if ((lock1 = initsem(L1, 1)) < 0)
		exit(1);
	if ((lock2 = initsem(L2, 1)) < 0)
		exit(1);
	if ((c1 = initsem(C1, 1)) < 0)
		exit(1);
	if ((c2 = initsem(C2, 1)) < 0)
		exit(1);

	Take_R1(lock1, c1);
	// getpid()가  생각을 시작함
	think();
	// getpid()가  생각을 멈춤
	Take_R2(lock2, c2);
	// getpid()가  먹기 시작함
	eating(); // sleep()으로 구현
			  // getpid()가  먹기를 멈춤
	Put_R1(lock1, c1);
	Put_R2(lock2, c2);

	FILE *fp = fopen("Count.txt", "a+");
	fprintf(fp, "%d : Finish Eating\n", getpid());
	fclose(fp);
}

void main()
{
	Phil_A();
}
// Phil_B~C는 숫자빼고 똑같기에 생략