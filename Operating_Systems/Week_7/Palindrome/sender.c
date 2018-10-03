#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/ipc.h>

#define MAX_TEXT 512 

struct msg_st {
	long int msg_type ; 
	int number ; 
} ; 

int main(int argc, char const *argv[]) {
	struct msg_st some_data ; 
	int msgid , num ; 
	msgid = msgget((key_t)1234, 0666| IPC_CREAT) ; 
	if(msgid == -1) {
		fprintf(stderr, "msgget failed with error - %d\n",errno );
		exit(EXIT_FAILURE) ; 
	}
	printf(" Enter number -> ");
	scanf("%d",&num) ; 
	some_data.msg_type = 1 ; 
	some_data.number = num ; 
	if( msgsnd(msgid, (void*)&some_data , MAX_TEXT , 0) == -1 ) {
		fprintf(stderr, " Msgsend failed ...\n" );
		exit(EXIT_FAILURE) ; 
	}
	exit(EXIT_SUCCESS) ; 
	return 0;
}
