#include "RW.h"

int main(int argc, char **argv){
	sleep(atoi(argv[1]));						//ready
       int lock;
       if ((lock = initsem(Order_key,1)) < 0)    // lock Null_set -1
         exit(1);
       int reader, writer;
       if ((reader = initsem(Reader_key,1)) < 0) // reader Null_set -1
         exit(1);
       if ((writer = initsem(Writer_key,1)) < 0)    // writer Null_set -1
         exit(1);

	P(lock);   
   	while((RecordAW(0)+ RecordAR(0)) > 0){
   		RecordWW(1);
   		Wait(writer, lock);
   		RecordWW(-1);
   	}
   	RecordAW(1);
   	V(lock);		

	sleep(atoi(argv[2]));						//running

   	P(lock);
   	RecordAW(-1);
   	if( RecordWW(0)>0 )
   		Signal(writer);
   	else if(RecordWR((0) > 0)) {
   		Broadcast(reader, RecordWR((0)));
   	}
   	else;
   	V(lock);		

	return 0;
}

