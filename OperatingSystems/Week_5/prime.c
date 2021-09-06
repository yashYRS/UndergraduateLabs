#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct prime_data{
	int start ; 
	int end ; 
	int* series ; 
	int num_primes ; 
}; 
typedef struct prime_data prime; 

int check_prime(int n) {
	for(int i = 2 ; i < sqrt(n) ;i++ ){
		if(n%i == 0 ) 
			return 0 ; 
	}
	return 1; 
}

int* copy(int* a, int n,int num){
	int* temp = (int*) malloc(n*sizeof(int)); 
	for(int i = 0 ; i < n-1 ; i++)
		temp[i] = a[i] ; 
	temp[n-1] = num ; 
	return temp ; 
}
void* get_prime(void *param) {
	prime* p = (prime*)param; // the structure passed, then variables inside manipulated 
	int s = p->start; 
	int e = p->end; 
	int *temp = (int*)malloc(sizeof(int)) ; // initially size of array = 1 
	int *temp_buffer ; 
	int number = 0 ; // number of primes added 
	for(int i = s ; i < e ; i++){
		if( check_prime(i)) {	// if prime, add to the array 
			temp_buffer = copy(temp,++number,i) ;
			free(temp); 
			temp = temp_buffer ; 
		}// copy function increases the size of the array by 1, whilst adding the new prime too.
	}
	p->series = temp ; 
	p->num_primes = number ; 
	pthread_exit(NULL) ; 
}

int main() {
	pthread_t t ; prime temp ; 
	printf(" Enter lower limit ") ; scanf("%d",&temp.start); 
	printf(" Enter upper limit ") ; scanf("%d",&temp.end); 
	pthread_create(&t,0,&get_prime,(void*)&temp); 
	pthread_join(t,NULL); 
	for(int i = 0 ; i < temp.num_primes ; i++) 
	       printf(" %d ",temp.series[i]); 	
	return 0 ; 
}
