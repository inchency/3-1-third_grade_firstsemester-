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

int P (int semid) {					//acquire
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

int V (int semid)						//release
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

int count(){
	FILE *iofile = fopen("cnt.txt", "a+");
	int cnt;
	while(!feof(iofile))
		fscanf(iofile, "%d", &cnt);
	fprintf(iofile, "%d\n", ++cnt);
	fclose(iofile);
	return cnt;
}

//condition variable
void wait(int semkey, int lock){
	V(lock);
	P(semkey);
	P(lock);
}

void signal(int semkey){
	V(semkey);
}

void broadcast(int semkey, int num){
	int i;
	for(i=0; i<num; i++){
		V(semkey);
	}
}

//AW,AR,WW,WR
int RecordAW(int num)
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

	if(num!=0)
	{
		time(&t);
		fprintf(iofile, "%s %d %d %d", ctime(&t), getpid(), cnt+num, count());
		fclose(iofile);
		return 0;
	}
	else
	{
		fclose(iofile);
		return cnt;
	}
}

int RecordAR(int num)
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

	if(num!=0)
	{
		time(&t);
		fprintf(iofile, "%s %d %d %d", ctime(&t), getpid(), cnt+num, count());
		fclose(iofile);
		return 0;
	}
	else
	{
		return cnt;
		fclose(iofile);
	}
}

int RecordWW(int num)
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

	if(num!=0)
	{
		time(&t);
		fprintf(iofile, "%s %d %d %d", ctime(&t), getpid(), cnt+num, count());
		fclose(iofile);
		return 0;
	}
	else
	{
		return cnt;
		fclose(iofile);
	}
}

int RecordWR(int num)
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

	if(num!=0)
	{
		time(&t);
		fprintf(iofile, "%s %d %d %d", ctime(&t), getpid(), cnt+num, count());
		fclose(iofile);
		return 0;
	}
	else
	{
		return cnt;
		fclose(iofile);
	}
}

