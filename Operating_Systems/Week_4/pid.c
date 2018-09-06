#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main() {
	pid_t pid; 
	int n,status ; 
	printf(" Fork program starting \n") ; 
	pid = fork() ; 
	switch(pid) {
		case -1 : 
					perror(" Fork Failed "); 
					exit(1) ; 
		case 0 : 
					printf("FOR THE forked Process \n Process :- %d \n Parent :- %d \n Child :- %d \n",getpid(),getppid(),pid );
					break;
		default : 
					printf("FOR THE calling Process ITSELF \n Process :- %d \n Parent :- %d \n Child :- %d \n",getpid(),getppid(),pid );
					wait(NULL);
					break ; 
	}
	exit(0);
}