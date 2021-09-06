 #include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/ipc.h>

void check_palindrome(int a) {
	int temp = a ; 
	int digits = 1 ; 
	while( temp > 10) {
		temp = temp/10 ; 
		digits = digits*10 ; 
	}
	while( a > 0) {
		if ( a/digits != a%10 ) { 	
			printf("NOT a PALINDROME \n");
			return ; 
		}
		a = a - (a/digits)*digits ; 
		a = a/10 ; 
		digits = digits / 100 ; 
	}
	printf(" PALINDROME \n");
}

struct msg_st {
	long int msg_type ; 
	int number ;
} ; 

int main() {
	int msgid ; 
	struct msg_st some_data ; 
	long int msg_to_receive ; 
	msgid = msgget((key_t)1234,0666 | IPC_CREAT) ; 
	if (msgid == -1) {
		fprintf(stderr, " msgget failed with error : %d \n", errno );
		exit(EXIT_FAILURE) ; 
	}
	if( msgrcv(msgid, (void*)&some_data , BUFSIZ, msg_to_receive,0) == -1) {
		fprintf(stderr, " msgrcv failed with error : %d \n", errno );
		exit(EXIT_FAILURE) ; 		
	}
	check_palindrome(some_data.number) ; 
	if(msgctl(msgid,IPC_RMID,0) == -1) {
		fprintf(stderr, "msgctl(IPC_RMID) failed  \n" );
		exit(EXIT_FAILURE) ; 
	}
	exit(EXIT_SUCCESS) ; 

}