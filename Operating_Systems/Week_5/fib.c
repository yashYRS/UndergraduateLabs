#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct fib{
	int n;
	int* fib_series ; 
} fib_struct ; 

void* fib_gen(void *param){
	fib_struct *fib_data = (fib_struct *) param ;// sending the parameter 
	int limit = fib_data->n; 
	int* fib_s = (int*)calloc(limit,sizeof(int));
	fib_s[1] = 1; 
	for(int i = 2 ; i < limit ; i++) 
		fib_s[i]= fib_s[i-1] + fib_s[i-2];
	fib_data->fib_series = fib_s ; 
	pthread_exit(NULL);  
}
int main() {
	int limit ; 
	pthread_t thread; 
	fib_struct fib_data; 
	printf(" Enter the limit - ");
	scanf("%d",&limit); fib_data.n = limit ; // setting the limit for the fib data 

	pthread_create(&thread,0,&fib_gen,(void*)&fib_data);
	pthread_join(thread,NULL);

	printf(" The fib series \t" ) ; 
	for(int i = 0 ; i < fib_data.n ; i++ ) 
		printf(" %d ",fib_data.fib_series[i]); 
	return 0;
}
