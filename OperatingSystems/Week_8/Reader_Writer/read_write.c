#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t mutex , wrt ; 
int read_count = 0 ; 
char word[15]; 

void* datawrite(void* arg) {
	sem_wait(&wrt) ;  // wrt provides protection for word 
	printf("\n Enter word -> ") ; 
	scanf("%s",word) ; 
	sem_post(&wrt) ; 
}

void* dataread(void* arg) {
	sem_wait(&mutex) ; // mutex provides protection for read_count 
	read_count++ ; 
	if (read_count == 1) 
		sem_wait(&wrt) ; // first reader
	sem_post(&mutex) ; 
	sem_wait(&mutex) ; 		
	printf("%s READ \n",word);	
	read_count-- ; // reading over 
	if ( read_count == 0) // last reader 
		sem_post(&wrt) ; 
	sem_post(&mutex) ; 

}

int main() {
	pthread_t writer, reader[10] ; // assuming there are 10 readers 
	sem_init(&mutex,0,1) ; 	// initially open	 
	sem_init(&wrt,0,1) ; // initially open for writing 
	pthread_create(&writer, NULL, datawrite , NULL) ; 
	for(int i = 0 ; i < 10 ; i++) {
		pthread_create(&reader[i], NULL, dataread, NULL) ; 
		pthread_join(reader[i],NULL) ; 
	}
	pthread_join(writer,NULL) ; 
	return 0 ; 
}