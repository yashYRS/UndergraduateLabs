#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/stat.h>
#define FIFO_NAME "queue"

int main() {
	int pipe_fd ; 
	int res; 
	int open_mode = O_WRONLY ; 
	int data ; //data to be sent 
	if (access(FIFO_NAME, F_OK) == -1) {
		res = mkfifo(FIFO_NAME, 0777) ; 
		if (res != 0) {
			fprintf(stderr, "Could not create fifo %s \n",FIFO_NAME );
			exit(EXIT_FAILURE) ; 
		}
	}
	printf(" Process %d opening FIFO O_WRONLY \n" , getpid()) ; 
	pipe_fd = open(FIFO_NAME , open_mode) ; 
	printf(" Process %d result %d \n",getpid(), pipe_fd );
	if ( pipe_fd != -1) {
		for(int i = 0 ; i < 4 ; i++){
			printf(" Enter an integer -> ");
			scanf("%d",&data) ; 
			res = write(pipe_fd,&data, sizeof(int)) ; 
			if (res == -1){
				fprintf(stderr, "Write error on pipe \n" );
				exit(EXIT_FAILURE) ; 				
			}
		}
		(void)close(pipe_fd) ; 
	}
	else 
		exit(EXIT_FAILURE) ; 
	printf(" Process %d finished \n", getpid() );
	exit(EXIT_SUCCESS) ; 
}