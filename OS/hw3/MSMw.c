#include "RWp.h"

void main(int argc, char **argv){
	int lock;
	if ((lock = initsem(2012333900,1)) < 0)    // lock 세마포어, 초기값 - 1
		exit(1);
		
	int reader, writer;
   	if ((reader = initsem(2012333901,1)) < 0)    // lock 세마포어, 초기값 - 1
		exit(1);
   	if ((writer = initsem(2012333902,1)) < 0)    // lock 세마포어, 초기값 - 1
		exit(1);
	
	sleep(atoi(argv[1]));			//ready

	P(lock);
   	while( (RecordAW(0) + RecordAR(0)) > 0 ){
   		RecordWW(1);
   		wait(writer, lock);
   		RecordWW(-1);
   	}
   	RecordAW(1);
   	V(lock);

	sleep(atoi(argv[2]));			//running

   	P(lock);
   	if(RecordWW(0)>0)
   		signal(writer);
   	else if(RecordWR(0)>0) {
   		broadcast(reader, RecordWR(0));
   	}
 	RecordAW(-1);
   	V(lock);

}
