#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int main() {
	pid_t pid; 
	int n,status ; 
	pid = fork() ; 
	switch(pid) {
		case -1 : 
					perror(" Fork Failed "); 
					exit(1) ; 
		case 0 : 	
					execlp("/home/student/160905390/Week4/Program1/w","w",(char *)0);
					break;
		default : 
					wait(&status) ; 
					printf("\n Child of the calling process terminates with %d status ",status);
					printf("\n Calling Process terminates ");
					break ; 
	}
	exit(0);
}