#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SEMPERM 0600

//semaphore
typedef union semun{
	int val;
	struct semid_ds *buf;
	ushort *array;
} semun;

key_t L1_KEY = 2012333901;
key_t L2_KEY = 2012333902;
key_t L3_KEY = 2012333903;
key_t C1_KEY = 2012333904;
key_t C2_KEY = 2012333905;
key_t C3_KEY = 2012333906;

int initsem (key_t semkey, int n) {
	int status = 0, semid;
	if ( (semid = semget (semkey, 1, SEMPERM | IPC_CREAT | IPC_EXCL)) == -1) { //semget : get a semaphore set identifier
		if (errno == EEXIST)
			semid = semget (semkey, 1, 0);
	}
	else{
		semun arg;
		arg.val = n;
		status = semctl(semid, 0, SETVAL, arg); 
	}
	if (semid == -1 || status == -1) {
		perror("initsem failed");
		return (-1);
	}
	return (semid);
}

int p (int semid) {					//acquire
	struct sembuf p_buf;
	p_buf.sem_num = 0;
	p_buf.sem_op = -1;
	p_buf.sem_flg = SEM_UNDO;
	if (semop(semid, &p_buf, 1) == -1) {
		perror ("p(semid) failed");
		exit(1);
	}
	return (0);
}

int v (int semid)						//release
{
	struct sembuf v_buf;
	v_buf.sem_num = 0;
	v_buf.sem_op = 1;
	v_buf.sem_flg = SEM_UNDO;
	if (semop(semid, &v_buf, 1) == -1)
	{
		perror ("v(semid) failed");
		exit(1);
	}
	return (0);
}
void  Acquire(int mutex){
	p(mutex);
}

void Release(int mutex){
	v(mutex);
}

void wait(int semkey, int lock){
	v(lock);
	p(semkey);
	p(lock);
}

void signal(int semkey){
	v(semkey);
}

void broadcast(int semkey, int num){
	int i;
	for(i=0; i<num; i++){
		v(semkey);
	}
}
// last homework Hw3

int load(int member){
	int cnt;
	FILE *inf;
	switch (member){
		case 1: 
		inf = fopen("R1.txt", "a+");
		fscanf(inf, "%d", &cnt);
		fclose(inf);
		break;

		case 2:
		inf = fopen("R2.txt", "a+");
		fscanf(inf, "%d", &cnt);
		fclose(inf);
		break;

		case 3:
		inf= fopen("R3.txt", "a+");
		fscanf(inf, "%d", &cnt);
		fclose(inf);
		break;
	}
	return cnt;
}

void Store(int member, int num){
	FILE *inf;
	switch (member){
		case 1:
		 inf = fopen("R1.txt", "w");
		fprintf(inf, "%d\n", num);
		fclose(inf);
		break;

		case 2:
		inf = fopen("R2.txt", "w");
		fprintf(inf, "%d\n", num);
		fclose(inf);
		break;

		case 3:
		inf = fopen("R3.txt", "w");
		fprintf(inf, "%d\n", num);
		fclose(inf);
		break;
	}
}

void waitingprint(int num){
	time_t t;
	FILE *inf = fopen("data.txt", "a+");
	time(&t);

	switch (num){
		case 1:
		fprintf(inf, " %d //  waiting~~ chopstick 'R1' // time is %s", getpid(), ctime(&t));
		break;

		case 2:
		fprintf(inf, " %d // waiting~~ chopstick 'R2 // time is %s", getpid(), ctime(&t));
		break;

		case 3:
		fprintf(inf, " %d //  waiting~~ chopstick 'R3' // time is %s", getpid(), ctime(&t));
		break;
	}
	
	fclose(inf);
}

void signalprint(){
	time_t  t;
	FILE *inf = fopen("data.txt", "a+");
	time(&t);
	fprintf(inf, "%d //  Wake up!! // time is %s", getpid(), ctime(&t));
	fclose(inf);
}

void think(){
	FILE *inf = fopen("data.txt", "a+");
	fprintf(inf, "ThinkING??\n");
	fclose(inf);
	sleep(1);
}

void eating(){
	FILE *inf = fopen("data.txt", "a+");
	fprintf(inf, "Eating!!\n");
	fclose(inf);
	sleep(1);
}

void Take_R1(int L1, int c1){
	Acquire(L1);
	FILE *inf2;
	FILE *inf = fopen("data.txt", "a+");
	time_t  t;
	time(&t);
	fprintf(inf, "trying take chopstick 'R1'// %d // %s", getpid(), ctime(&t));
	fclose(inf);
	while(load (1) == 0){  //while ~  no chopstick
		waitingprint(1);
		wait(c1, L1);
		signalprint();
	}
	Store(1, 0);
	time(&t);
	inf = fopen("data.txt", "a+");
	fprintf(inf, "%d // takes chopstick  // time is %s", getpid(), ctime(&t));
	fclose(inf);
	Release(L1);
}

void Put_R1(int L1, int c1){
	Acquire(L1);
	time_t t;
	Store(1, 1); // data.txt 0 -> 1    (put chopstick)
	FILE *inf = fopen("data.txt", "a+");
	time(&t);
	fprintf(inf, "%d //  Puts chopstick 'R1' // time is %s", getpid(), ctime(&t));
	fclose(inf);
	signal(c1);
	Release(L1);
}

void Take_R2(int L2, int c2){
	Acquire(L2);
	FILE *inf = fopen("data.txt", "a+");
	time_t  t;
	time(&t);
	fprintf(inf, "trying take chopstick 'R2'// %d // %s", getpid(), ctime(&t));
	fclose(inf);
	while(load (2) == 0){  //while ~  no chopstick
		waitingprint(2);
		wait(c2, L2);
		signalprint();
	}
	Store(2, 0);
	time(&t);
	inf = fopen("data.txt", "a+");
	fprintf(inf, "%d // takes chopstick  // time is %s", getpid(), ctime(&t));
	fclose(inf);
	Release(L2);
}

void Put_R2(int L2, int c2){
	Acquire(L2);
	time_t t;
	Store(2, 1); // data.txt 0 -> 1    (put chopstick)
	FILE *inf = fopen("data.txt", "a+");
	time(&t);
	fprintf(inf, "%d // Puts chopstick 'R2' // time is %s", getpid(), ctime(&t));
	fclose(inf);
	signal(c2);
	Release(L2);
}

void Take_R3(int L3, int c3){
	Acquire(L3);
	FILE *inf = fopen("data.txt", "a+");
	time_t  t;
	time(&t);
	fprintf(inf, "trying take chopstick 'R2'// %d // %s", getpid(), ctime(&t));
	fclose(inf);
	while(load (3) == 0){  //while ~  no chopstick
		waitingprint(2);
		wait(c3, L3);
		signalprint();
	}
	Store(3, 0);
	time(&t);
	inf = fopen("data.txt", "a+");
	fprintf(inf, "%d // takes chopstick  // time is %s", getpid(), ctime(&t));
	fclose(inf);
	Release(L3);
}

void Put_R3(int L3, int c3){
	Acquire(L3);
	time_t t;
	Store(3, 1); // data.txt 0 -> 1    (put chopstick)
	FILE *inf = fopen("data.txt", "a+");
	time(&t);
	fprintf(inf, "%d // Puts chopstick 'R2' // time is %s", getpid(), ctime(&t));
	fclose(inf);
	signal(c3);
	Release(L3);
}

void Phil_A(int L1, int L2, int C1, int C2){
	Take_R1(L1, C1); 
	 // getpid() is start thinking
	think(); // sleep();
	// getpid() is stop thinking
	Take_R2(L2, C2);  
	// getpid() is start eating
	eating();  // sleep();
	// getpid() stop eating
	Put_R1(L1, C1);
	Put_R2(L2, C2);
}

void Phil_B(int L2, int L3, int C2, int C3){
	Take_R2(L2, C2); 
	 // getpid() is start thinking
	think(); // sleep();
	// getpid() is stop thinking
	Take_R3(L3, C3);  
	// getpid() is start eating
	eating();  // sleep();
	// getpid() stop eating
	Put_R2(L2, C2);
	Put_R3(L3, C3);
}

void Phil_C(int L3, int L1, int C3, int C1){
	Take_R3(L3, C3); 
	 // getpid() is start thinking
	think(); // sleep();
	// getpid() is stop thinking
	Take_R1(L1, C1);  
	// getpid() is start eating
	eating();  // sleep();
	// getpid() stop eating
	Put_R3(L3, C3);
	Put_R1(L1, C1);
}