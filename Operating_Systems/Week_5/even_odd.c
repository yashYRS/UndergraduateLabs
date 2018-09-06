#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct arr{
	int n;
	int* series ; 
	int sum_odd; 
	int sum_even; 
}array ; 

void* add_odd(void *param){
	array *a = (array *) param ;// sending the parameter 
	int limit = a->n; 
	int *temp = a->series ;
	int sum = 0 ; 
	for(int i = 0 ; i < limit ; i++){ 
		if(temp[i]%2!=0)
			sum = sum + temp[i] ; 
	}
	a->sum_odd = sum ; 
	pthread_exit(NULL);  
}
void* add_even(void *param) {
	array *a = (array *) param ; 
	int limit = a->n ; 
	int *temp = a->series; 
	int sum = 0 ; 
	for(int i = 0 ; i < limit ; i++) {
		if(temp[i]%2==0)
			sum = sum + temp[i];
	}
	a->sum_even = sum; 
	pthread_exit(NULL); 
}
int main() {
	int limit ; 
	pthread_t thread; 
	array a; 
	printf(" Enter the limit - ");
	scanf("%d",&limit); a.n = limit ; // setting the limit for the fib data 
	a.series = (int*) calloc(limit,sizeof(int)); 
	a.sum_even = 0 ; a.sum_odd = 0 ; 	
	for(int i = 0 ; i < limit ; i ++ ) {
		printf(" Enter number ") ;
		scanf( " %d",&(a.series[i]) ); 
	}
	pthread_create(&thread,0,&add_odd,(void*)&a);
	pthread_join(thread,NULL);
	pthread_create(&thread,0,&add_even,(void*)&a);
	pthread_join(thread,NULL); 
	printf(" The sum of even  %d",a.sum_even) ;
	printf(" The sum of odd %d", a.sum_odd) ; 
	return 0 ; 
}
