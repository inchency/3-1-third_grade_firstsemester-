#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

#define SEMPERM 0600
typedef int bool;
#define true 1
#define false 0

typedef union _semun {
	int val;
	struct semid_ds *buf;
	ushort *array;
} semun;

key_t L1 = 2012341101;
key_t L2 = 2012341102;
key_t L3 = 2012341103;
key_t C1 = 2012341104;
key_t C2 = 2012341105;
key_t C3 = 2012341106;

int initsem(key_t key, int n)
{
	int status = 0, semid;
	if ((semid = semget(key, 1, SEMPERM | IPC_CREAT | IPC_EXCL)) == -1)
	{
		if (errno == EEXIST)
			semid = semget(key, 1, 0);
	}
	else
	{
		semun arg;
		arg.val = n;
		status = semctl(semid, 0, SETVAL, arg);
	}
	if (semid == -1 || status == -1)
	{
		perror("initsem failed");
		return (-1);
	}
	return (semid);
}

int p(int lock)
{
	struct sembuf p_buf;

	p_buf.sem_num = 0;
	p_buf.sem_op = -1;
	p_buf.sem_flg = SEM_UNDO;

	if (semop(lock, &p_buf, 1) == -1)
	{
		perror("p(lock) failed");
		exit(1);
	}

	return (0);
}
int v(int lock)
{
	struct sembuf v_buf;

	v_buf.sem_num = 0;
	v_buf.sem_op = 1;
	v_buf.sem_flg = SEM_UNDO;

	if (semop(lock, &v_buf, 1) == -1)
	{
		perror("v(lock) failed");
		exit(1);
	}

	return (0);
}

// 세마포로 구현한 Condirion Variable
void wait(int c1, int lock)
{
	v(lock);
	p(c1);
	p(lock);
}
void signal(int c1)
{
	v(c1);
}
void broadcast(int c1, int num)
{
	int i;
	for (i = 0; i < num; i++)
		v(c1);
}

void think() {
	// Count.txt에 생각하는인원과 생각중임을 표시
	FILE *fp = fopen("Count.txt", "a+");
	fprintf(fp, "%d : Thinking....\n", getpid());
	fclose(fp);
	sleep(3);
}
void eating() {
	// Count.txt에 먹는인원과 먹는중임을 표시
	FILE *fp = fopen("Count.txt", "a+");
	fprintf(fp, "%d : Eating!!!!\n", getpid());
	fclose(fp);
	sleep(3);
}

int Load(int r) {
	// num에따라 R1~3를 구분
	int i;
	if (r == 1)
	{
		FILE *fp1 = fopen("R1.txt", "a+");
		while (!feof(fp1))
			fscanf(fp1, "%d", &i);
		fclose(fp1);
	}
	else if (r == 2)
	{
		FILE *fp1 = fopen("R2.txt", "a+");
		while (!feof(fp1))
			fscanf(fp1, "%d", &i);
		fclose(fp1);
	}
	else
	{
		FILE *fp1 = fopen("R3.txt", "a+");
		while (!feof(fp1))
			fscanf(fp1, "%d", &i);
		fclose(fp1);
	}

	return i;
}
void Store(int r, int num) {
	// num에따라 R1~3를 구분
	if (r == 1)
	{
		FILE *fp2 = fopen("R1.txt", "w");
		fprintf(fp2, "%d\n", num);
		fclose(fp2);
	}
	else if (r == 2)
	{
		FILE *fp2 = fopen("R2.txt", "w");
		fprintf(fp2, "%d\n", num);
		fclose(fp2);
	}
	else
	{
		FILE *fp2 = fopen("R3.txt", "w");
		fprintf(fp2, "%d\n", num);
		fclose(fp2);
	}
}

void Take_R1(int lock1, int c1) {
	bool test = false;

	time_t t;

	p(lock1);

	// 젓가락이 없을경우 waiting....을 Count.txt에 입력후 while에서 wait를 실행
	time(&t);
	if (Load(1) == 0)
	{
		FILE *fp = fopen("Count.txt", "a+");
		fprintf(fp, "%d : R1_waiting...., Time : %s", getpid(), ctime(&t));
		fclose(fp);
	}
	while (Load(1) == 0) {
		wait(c1, lock1);
		test = true;
	}
	time(&t);

	// while문을 거쳤을경우 signal을 통해 깨워준것을 입력
	FILE *fp = fopen("Count.txt", "a+");
	if (test)
		fprintf(fp, "%d : wack up!!!, Time : %s", getpid(), ctime(&t));

	// R1.txt에 젓가락이 없음(0)을 입력후 Count.txt에 가져간 정보를 입력
	Store(1, 0);
	time(&t);
	fprintf(fp, "%d : Take_R1, Time : %s", getpid(), ctime(&t));
	fclose(fp);

	v(lock1);
}
void Put_R1(int lock1, int c1) {
	time_t t;

	p(lock1);

	// R1.txt에 젓가락이 있음(1)을 입력후 Count.txt에 내려놓은 정보를 입력
	// 그후 signal로 R1를 기다리는 인원을 깨워줌
	Store(1, 1);
	time(&t);
	FILE *fp = fopen("Count.txt", "a+");
	fprintf(fp, "%d : Put_R1, Time : %s", getpid(), ctime(&t));
	fclose(fp);
	signal(c1);

	v(lock1);
}
// R2~R3는 lock과 c의 숫자가 다른것빼고 똑같기에 생략

void Take_R2(int lock2, int c2) {
	bool test = false;
	time_t t;

	p(lock2);

	// 젓가락이 없을경우 waiting....을 Count.txt에 입력후 while에서 wait를 실행
	time(&t);
	if (Load(2) == 0)
	{
		FILE *fp = fopen("Count.txt", "a+");
		fprintf(fp, "%d : R2_waiting...., Time : %s", getpid(), ctime(&t));
		fclose(fp);
	}
	while (Load(2) == 0) {
		wait(c2, lock2);
		test = true;
	}
	time(&t);

	// while문을 거쳤을경우 signal을 통해 깨워준것을 입력
	FILE *fp = fopen("Count.txt", "a+");
	if (test)
		fprintf(fp, "%d : wack up!!!, Time : %s", getpid(), ctime(&t));

	// R2.txt에 젓가락이 없음(0)을 입력후 Count.txt에 가져간 정보를 입력
	Store(2, 0);
	time(&t);
	fprintf(fp, "%d : Take_R2, Time : %s", getpid(), ctime(&t));
	fclose(fp);

	v(lock2);
}
void Put_R2(int lock2, int c2) {
	time_t t;

	p(lock2);

	// R2.txt에 젓가락이 있음(1)을 입력후 Count.txt에 내려놓은 정보를 입력
	// 그후 signal로 R2를 기다리는 인원을 깨워줌
	Store(2, 1);
	time(&t);
	FILE *fp = fopen("Count.txt", "a+");
	fprintf(fp, "%d : Put_R2, Time : %s", getpid(), ctime(&t));
	fclose(fp);
	signal(c2);

	v(lock2);
}

void Take_R3(int lock3, int c3) {
	bool test = false;
	time_t t;

	p(lock3);

	// 젓가락이 없을경우 waiting....을 Count.txt에 입력후 while에서 wait를 실행
	time(&t);
	if (Load(3) == 0)
	{
		FILE *fp = fopen("Count.txt", "a+");
		fprintf(fp, "%d : R3_waiting...., Time : %s", getpid(), ctime(&t));
		fclose(fp);
	}
	while (Load(3) == 0) {
		wait(c3, lock3);
		test = true;
	}
	time(&t);

	// while문을 거쳤을경우 signal을 통해 깨워준것을 입력
	FILE *fp = fopen("Count.txt", "a+");
	if (test)
		fprintf(fp, "%d : wack up!!!, Time : %s", getpid(), ctime(&t));

	// R3.txt에 젓가락이 없음(0)을 입력후 Count.txt에 가져간 정보를 입력
	Store(3, 0);
	fprintf(fp, "%d : Take_R3, Time : %s", getpid(), ctime(&t));
	fclose(fp);

	v(lock3);
}
void Put_R3(int lock3, int c3) {
	time_t t;

	p(lock3);

	// R3.txt에 젓가락이 있음(1)을 입력후 Count.txt에 내려놓은 정보를 입력
	// 그후 signal로 R3를 기다리는 인원을 깨워줌
	Store(3, 1);
	time(&t);
	FILE *fp = fopen("Count.txt", "a+");
	fprintf(fp, "%d : Put_R3, Time : %s", getpid(), ctime(&t));
	fclose(fp);
	signal(c3);

	v(lock3);
}