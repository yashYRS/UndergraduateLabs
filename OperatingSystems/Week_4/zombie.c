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
					printf("\n Hey there!, child here"); 
					exit(0);
		default : 
					sleep(4);
					printf("\n Hey there!, parent here");
					exit(0);
	}
}