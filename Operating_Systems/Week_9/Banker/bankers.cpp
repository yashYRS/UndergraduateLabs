#include<iostream>
#include<stdlib.h>
using namespace std ; 


int* take_input(int n, int m) {
	int* a = (int*)malloc(sizeof(int)*n*m) ; // n*m 
	for(int i = 0 ; i < n ; i++) {
		cout<<"\n Enter row -> " ; 
		for(int j = 0 ; j < m ; j++)
			cin>>a[i*n + j];  
	}
	return a ; 
}

void copy(int *a , int * b, int n) {
	for(int i = 0 ; i < n ; i++) 
		a[i] = b[i] ; 
}

void print(int *a , int n, int m ) {
	cout<<" New -> " ; 
	for(int i = 0 ; i < n ;i++ ) {
		for(int j = 0 ; j < m ; j++) 
			cout<<a[i*n + j]<<" " ; 
		cout<<endl ; 
	}
}

int safety(int *need, int *allocate, int *max , int *work, int n, int m) {
	int *finish = (int*)calloc(n,sizeof(int)) ; // 0 initially for all of the processes....  
	int flag , found = 1 ; 
	while(found) { // thus, nothing was found in one run, the loop breaks ... 
		found = 0 ; 
		for( int i = 0 ; i < n ; i++ ) {
			if (finish[i] == 0 ) {
				flag = 1 ;  // initially 1 
				for(int j = 0 ; j < m ; j++) {
					if(need[i*n + j] > work[j]) // if need_i <= work 
						flag = 0 ; 
				}
				if (flag == 1) {
					for(int j = 0 ; j < m ; j++)
						work[j] = work[j] + allocate[i*n + j] ; 
					finish[i] = 1 ;
					found = 1 ; // something was found  
				}
			} 
		}
	} 
	for(int i = 0 ; i < n ; i++)  {
		if (finish[i] == 0)
			return 0 ; // unsafe 
	}
	return 1 ; // safe 
}

int prompt() {
	int a ; 
	cout<<"\n\n Enter choice - 1. safety check 2. resource-request 3. exit \n" ; 
	cin>> a; 
	return a ;  
}
int main() {
	int n , m ; // n -> no of processors, m -> no of resource types 
	int *available, *avail_copy , *maximum , *max_copy, *allocation , *alloc_copy , *need , *need_copy; 
	
	cout<<" Enter the number of resources " ; 
	cin >> m ; 
	cout<<" Enter the number of processes " ;
	cin>> n ; 
	cout<<" Enter the available resources "<<endl ;  
	available = take_input(1,m) ; 
	cout<<" Enter the maximum #resources for each process [row wise]"<<endl ; 
	maximum = take_input(n,m) ; 
	cout<<" Enter the #resources allocated to each process [row wise]"<<endl ; 
	allocation = take_input(n,m) ; 
	
	int process ; // process which requests it. 
	int *request ; 
	
	need = (int*)malloc(sizeof(int)*m*n) ; 
	avail_copy = (int*)malloc(sizeof(int)*m*n) ; 
	need_copy = (int*)malloc(sizeof(int)*m*n) ;
	max_copy = (int*)malloc(sizeof(int)*m*n) ;  
	alloc_copy = (int*)malloc(sizeof(int)*m*n) ; 

	for(int i = 0 ; i < n ; i++) {
		for(int j = 0 ; j < m ; j++) {
			need[i*n + j] = maximum[i*n + j] - allocation[i*n + j] ; 
		}
	}  		// compute need 
	int flag = 1 ; 
	while(1) {
		switch(prompt()) {
			case 1 : 
						copy(avail_copy,available, m) ; 
						if (safety(need,allocation,maximum,avail_copy,n,m) == 0 )
							cout<<"unsafe"<<endl ; 
						else 
							cout<<"safe"<<endl ; 
						break ; 
			case 2 :
						copy(avail_copy,available , m) ; 
						copy(need_copy,need , n*m) ; 
						copy(alloc_copy, allocation, n*m) ; 
						copy(max_copy, maximum, n*m) ; 
						cout<<" Enter the process" ;
						cin>> process ; 
						cout<<" Enter the request " ; 
						request = take_input(1,m); // request for resources  
						for(int i = 0 ; i < m ; i++)  {
							if( request[i] > need[(process - 1)*n + i] ) {
								cout<<"Invalid" ; 
								break ; 
							}
							if ( request[i] > available[(process - 1)*n + i] ){
								cout<<" Wait " ; 
								break ; // needs to break off from the case .... 
							}
						} 			// request < need 
						for ( int i = 0 ; i < m ; i++ ) {
							avail_copy[i] = avail_copy[i] - request[i] ; 
							alloc_copy[(process-1)*n + i] = alloc_copy[(process-1)*n + i] + request[i] ; 
							need_copy[(process-1)*n + i] = need_copy[(process-1)*n + i] - request[i] ; 
						}
						if (safety(need_copy,alloc_copy,max_copy,avail_copy,n,m) == 0 )
							cout<<" Wait "<<endl ; 
						else 
							cout<<"can be allocated"<<endl ; 
						cout<<"\n Max -> \n" ; 
						print(max_copy,n,m) ;
						cout<<"\n Allocated -> \n" ; 
						print(alloc_copy,n,m) ;
						cout<<"\n Needs -> \n" ; 
						print(need_copy,n,m) ;
						cout<<"\n available -> \n" ; 
						print(avail_copy, 1,m) ; 
						break ; 	
			case 3 : exit(0) ;  
		}
	}
}