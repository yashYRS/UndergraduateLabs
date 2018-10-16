#include<iostream>
#include<stdlib.h>
using namespace std ; 


int* take_input(int n, int m) {
	int* a = (int*)malloc(sizeof(int)*n*m) ; // n*m 
	for(int i = 0 ; i < n ; i++) {
		cout<<"\n Enter row -> " ; 
		for(int j = 0 ; j < m ; j++)
			cin>>a[i*m + j];  
	}
	return a ; 
}

void copy(int *a , int * b, int n) {
	for(int i = 0 ; i < n ; i++) 
		a[i] = b[i] ; 
}

void print(int *a , int n, int m ) {
	for(int i = 0 ; i < n ;i++ ) {
		for(int j = 0 ; j < m ; j++) 
			cout<<a[i*m + j]<<" " ; 
		cout<<endl ; 
	}
}

int detect(int *allocate, int *request , int *work, int n, int m) {
	int *finish = (int*)malloc(n*sizeof(int)) ; 
	for(int i = 0 ; i < n ; i++ ) {
		finish[i] = 1 ; 
		for(int j = 0 ; j < m ; j++) 
			if(allocate[i*m + j] > 0)  {
				finish[i] = 0 ; 
				break ;
			}
	}		// set up finish ... 
	
	int flag , found = 1 , break_flag = 1 ; 
	while(found) { // thus, nothing was found in one run, the loop breaks ... 
		found = 0 ; 
		for( int i = 0 ; i < n ; i++ ) {
			break_flag = 1 ; 
			if (finish[i] == 0 ) {				
				for(int j = 0 ; j < m ; j++) {
					if ( request[i*m + j] > work[j] ){
						break_flag = 0 ;  // don't execute step->3 
						break ; 
					}
				}
				if (break_flag) { // that i found, so step-> 3 
					found = 1 ; 
					for(int j = 0 ; j < m ; j++) 
						work[j] = work[j] + allocate[i*m + j] ; 
					finish[i] = 1; 
				}
			}
		}
	} 
	for(int i = 0 ; i < n ; i++)  {
		if (finish[i] == 0)
			return 0 ; // deadlock 
	}
	return 1 ; // no deadlock  
}

int prompt() {
	int a ; 
	cout<<"\n\n Enter choice - 1. Detect Deadlock  2. exit \n" ; 
	cin>> a; 
	return a ;  
}

int main() {
	int n , m ; // n -> no of processors, m -> no of resource types 
	int *available, *avail_copy , *request , *request_copy, *allocation , *alloc_copy ; 
	
	available = (int*)malloc(sizeof(int)*m*n) ; 
	request = (int*)malloc(sizeof(int)*m*n) ;  
	allocation = (int*)malloc(sizeof(int)*m*n) ; 
	cout<<" Enter the number of resources " ;  cin >> m ; 
	cout<<" Enter the number of processes " ; cin>> n ; 
	cout<<" Enter the available resources "<<endl ;  available = take_input(1,m) ;  print(available,1,m) ; 
	cout<<" Enter the request/process [row wise]"<<endl ; request = take_input(n,m) ; print(request,n,m) ;
	cout<<" Enter the allocation/process [row wise]"<<endl ; allocation = take_input(n,m) ; print(allocation,n,m) ;
	
	avail_copy = (int*)malloc(sizeof(int)*m) ; 
	request_copy = (int*)malloc(sizeof(int)*m*n) ;  
	alloc_copy = (int*)malloc(sizeof(int)*m*n) ; 

	while(1) {
		switch(prompt()) {
			case 1 : 
						copy(avail_copy,available , m) ; 
						copy(alloc_copy, allocation, n*m) ; 
						copy(request_copy, request, n*m) ; 
						if (detect(alloc_copy,request_copy,avail_copy,n,m) == 0 )
							cout<<" Deadlock "<<endl ; 
						else 
							cout<<" No Deadlock "<<endl ; 
						break ; 
			case 2 : exit(0) ;  
		}
	}
}