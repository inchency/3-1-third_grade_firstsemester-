#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define SEMPERM 0600
#define Order_key 2012333900		 // 서버에서 작업할 때는 자기 학번 등을 이용하여 다른 사람의 키와 중복되지 않게 해야 함
#define Reader_key 2012333901
#define Writer_key 2012333902

typedef union semun{
	int val;
	struct semid_ds *buf;	
	ushort *array;
} semun;

int initsem (key_t semkey, int n) {
	int status = 0, semid;
	if ( (semid = semget (semkey, 1, SEMPERM | IPC_CREAT | IPC_EXCL)) == -1) {
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

int P (int semid) {
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

int V (int semid)
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


void Wait(int semkey, int lock){
	V(lock);
	P(semkey);
	P(lock);
}

void Signal(int semkey){			
	V(semkey);
}

void Broadcast(int semkey, int num){		
	int i;
	for(i=0; i<num; i++){
		V(semkey);
	}
}

//AW, WW, AR, WR
int RecordAR(int n)
{
	FILE *iofile = fopen("AR.txt", "a+");
	time_t t;
	int cnt;
	char getval[100];
	if(iofile == NULL)
		exit(1);
	while(!feof(iofile))
		fgets(getval, 100, iofile);

	cnt=atoi(getval);

	if(n==0)
	{
		return cnt;
		fclose(iofile);
	}
	else
	{
		time(&t);
		fprintf(iofile, "%d %d %s", cnt+n, getpid(), ctime(&t));
		fclose(iofile);
		return 0;
	}
}

int  RecordAW(int n)
{
	FILE *iofile = fopen("AW.txt", "a+");
	time_t t;
	int cnt;
	char getval[100];
	if(iofile == NULL)
		exit(1);
	while(!feof(iofile))
		fgets(getval, 100, iofile);

	cnt=atoi(getval);

	if(n==0)
	{
		fclose(iofile);
		return cnt;
	}
	else
	{
		time(&t);
		fprintf(iofile, "%d %d %s", cnt+n, getpid(), ctime(&t));
		fclose(iofile);
		return 0;
	}
}

int RecordWR(int n)
{
	FILE *iofile = fopen("WR.txt", "a+");
	time_t t;
	int cnt;
	char getval[100];
	if(iofile == NULL)
		exit(1);
	while(!feof(iofile))
		fgets(getval, 100, iofile);

	cnt=atoi(getval);

	if(n==0)
	{
		return cnt;
		fclose(iofile);
	}
	else
	{
		time(&t);
		fprintf(iofile, "%d %d %s", cnt+n, getpid(), ctime(&t));
		fclose(iofile);
		return 0;
	}
}

int RecordWW(int n)
{
	FILE *iofile = fopen("WW.txt", "a+");
	time_t t;
	int cnt;
	char getval[100];
	if(iofile == NULL)
		exit(1);
	while(!feof(iofile))
		fgets(getval, 100, iofile);

	cnt=atoi(getval);

	if(n==0)
	{
		return cnt;
		fclose(iofile);
	}
	else
	{
		time(&t);
		fprintf(iofile, "%d %d %s", cnt+n, getpid(), ctime(&t));
		fclose(iofile);
		return 0;
	}
}