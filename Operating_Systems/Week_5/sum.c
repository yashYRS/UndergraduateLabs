#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
struct s{
	int sum_till_now;
	int current_passed ; 
} ;
typedef struct s sum_data ;  

void* sum_current(void *param){
	sum_data *temp = (sum_data *) param ;// sending the structure 
	temp->sum_till_now = temp->sum_till_now + temp->current_passed ; 
	pthread_exit(NULL);  
}
int main() {
	int limit ; 
	printf(" Enter the number of numbers - ");
	scanf("%d",&limit);
	pthread_t threads[limit];  
	int sum[limit]; 
	sum_data temp ; // declare the structure 
	temp.sum_till_now = 0; // initially sum = 0 
	for(int i = 0 ; i < limit ; i++) {
		printf(" \n Enter number - "); 
		scanf("%d",&sum[i]);  		// take input 
		temp.current_passed = sum[i]; 	// set that to be the current element
		pthread_create(&threads[i],0,&sum_current,(void*)&temp); // ask child to add the same
		pthread_join(threads[i],NULL);	// wait for child to finish 
	}
	printf(" The summation - %d ",temp.sum_till_now ) ; 
	return 0;
}
