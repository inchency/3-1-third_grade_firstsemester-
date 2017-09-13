#include "head.h"

void Phil_A() {
	// 모든자원을 가져와야하기에 모든락을 불러옴
	int lock1, lock2, lock3, c1, c2, c3, global_lock;

	if ((lock1 = initsem(L1, 1)) < 0)
		exit(1);
	if ((lock2 = initsem(L2, 1)) < 0)
		exit(1);
	if ((lock3 = initsem(L3, 1)) < 0)
		exit(1);
	if ((c1 = initsem(C1, 1)) < 0)
		exit(1);
	if ((c2 = initsem(C2, 1)) < 0)
		exit(1);
	if ((c3 = initsem(C3, 1)) < 0)
		exit(1);
	if ((global_lock = initsem(GL, 1)) < 0)
		exit(1);

	// 모든자원을 가져오는 단계는 Mutual Exclusion 해야하기 때문에
	// global_lock이라는 3명모두 사용하는 lock을 만들어 사용
	p(global_lock);

	Take_R1(lock1, c1);
	Take_R2(lock2, c2);
	Take_R3(lock3, c3);

	v(global_lock);

	// getpid()가  생각을 시작함
	think();
	// getpid()가  생각을 멈춤
	// getpid()가  먹기 시작함
	eating(); // sleep()으로 구현
			  // getpid()가  먹기를 멈춤

	Put_R1(lock1, c1);
	Put_R2(lock2, c2);
	Put_R3(lock3, c3);

	FILE *fp = fopen("Count.txt", "a+");
	fprintf(fp, "%d : Finish Eating\n", getpid());
	fclose(fp);
}

void main()
{
	Phil_A();
}
// 나머지 Phil_B~C 또한 동일 & head.h에 GL의 키값을 설정