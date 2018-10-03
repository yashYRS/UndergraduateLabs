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
	int open_mode = O_RDONLY ; 
	int data ; 
	int bytes_read = 0 ; 
	printf(" Process %d opening FIFO O_RDONLY \n", getpid());
	pipe_fd = open(FIFO_NAME , open_mode) ; 
	printf(" Process %d result %d \n", getpid(), pipe_fd);
	printf(" The data received ---> ") ; 
	if ( pipe_fd != -1) {
		for(int i = 0 ; i < 4 ; i++) {
			res = read(pipe_fd, &data, sizeof(int)) ; 
			printf("%d ", data);
		}
		(void) close(pipe_fd) ; 
	}
	else 
		exit(EXIT_FAILURE) ; 
	printf(" Process %d finished \n", getpid());
	exit(EXIT_SUCCESS) ; 
}