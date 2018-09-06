#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void disp(char *c,int n){
	for(;n>0;n--) 
		puts(c) ; 
}

int main() {
	pid_t pid; 
	char *msg ; 
	int n,status ; 
	printf(" Fork program starting \n") ; 
	pid = fork() ; 
	switch(pid) {
		case -1 : 
					perror(" Fork Failed "); 
					exit(1) ; 
		case 0 : 
					msg = "This is the child" ; 
					n = 20 ;
					disp(msg,n);
					break;
		default : 
					msg = "This is the parent" ; 
					n = 10 ; 
					disp(msg,n);
					wait(&status) ; 
					printf("\n Child terminates with %d status ",status);
					printf("\n Parent terminates ");
					break ; 
	}
	exit(0);
}