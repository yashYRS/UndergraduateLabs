#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

int buf[10], f, r ; 
sem_t mutex, full, empty ; // all are semaphores 
void *produce(void* arg) {
	int i , value; 
	for(i = 0 ; i < 15; i++) {
		sem_wait(&empty) ; // we keep producing till empty = 0 , after which we wait  
		sem_wait(&mutex) ; 	
		printf("Produced items is %d \n",i );
		buf[(++r)%10] = i ;
		sleep(1) ; 
		sem_post(&mutex) ; 		 
		sem_post(&full) ; 			// full incremented . 
		sem_getvalue(&full, &value) ; 
		printf(" full %d \n",value ); 
	}
}

void* consume(void *ard) {
	int item, i , value; 
	for(i = 0 ; i < 15 ; i++) {
		sem_wait(&full) ; 			// keep consuming till full =0 
		sem_getvalue(&full, &value) ; 
		printf(" full %d \n",value );			
		sem_wait(&mutex);
		item = buf[(++f)%10] ; 
		printf(" consumed item is %d \n",item );
		sleep(1) ; 
		sem_post(&mutex);
		sem_post(&empty);   

	}
}

int main(int argc, char const *argv[])
{
	pthread_t tid1 , tid2 ; 
	sem_init(&mutex, 0 , 1) ; 
	sem_init(&full, 0, 1) ; 
	sem_init(&empty,0,10) ; 
	pthread_create(&tid1, NULL, produce, NULL) ; 
	pthread_create(&tid2, NULL, consume, NULL) ; 
	pthread_join(tid1, NULL) ; 
	pthread_join(tid2, NULL) ;
	return 0;
}