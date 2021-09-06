#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>

struct shared_use_st {
	int flag ; 
	char alphabet ; 
};

void check_error2(void* c) {
	if( c == (void*)-1)  {
		fprintf(stderr, " shmat failed \n");
		exit(EXIT_FAILURE) ; 
	}
}
void check_error(int check,char *temp) {
	if(check == -1 ) {
		fprintf(stderr, "%s failed",temp );
		exit(EXIT_FAILURE) ; 
	}
}

int main() {
	void* shared_memoryp = (void*)0 ; 
	void* shared_memoryc = (void*)0 ; 
	char *dt = "shmdt" , *at = "shmat", *id = "shmget" , *ctl = "shmctl"; 
	struct shared_use_st *shared_stuffp , *shared_stuffc ; 
	int shmidp, shmidc ; 
	int cpid = fork() ; 
	if ( cpid == 0 ) {
		shmidc = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT ) ; 
		check_error(shmidc, id) ; 
		shared_memoryc = shmat( shmidc , (void *)0 , 0) ; 
		check_error2(shared_memoryc) ; 
		shared_stuffc = (struct shared_use_st *) shared_memoryc ; 
		while(1) {
			if (shared_stuffc->flag == 1 ) {
				shared_stuffc->alphabet = shared_stuffc->alphabet + 1 ; 
				break ; 
			}
		}
		check_error(shmdt(shared_memoryc) , dt) ; 
		check_error(shmctl(shmidc, IPC_RMID, 0) , ctl) ; 
		exit(EXIT_SUCCESS) ; 
	}
	else {
		shmidp = shmget((key_t)1234, sizeof(struct shared_use_st), 0666| IPC_CREAT) ; // get the shared memory 
		check_error(shmidp, id) ; 
		shared_memoryp = shmat (shmidp , (void*)0 , 0) ; // attach 
		check_error2(shared_memoryp) ; 
		shared_stuffp = (struct shared_use_st*) shared_memoryp ; 
		printf("Enter a character -> ");	
		scanf("%c",&shared_stuffp->alphabet) ; 					// directly write to the shared memory 					
		shared_stuffp->flag = 1 ; 
		wait(NULL) ; 
		printf("As written by the child -> %c \n", shared_stuffp->alphabet );
		check_error(shmdt(shared_memoryp) , dt) ; 		
		exit(EXIT_SUCCESS) ;		
	}	

}