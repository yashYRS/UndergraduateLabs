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

int safety(int *need, int *allocate, int *max , int *work, int n, int m) {
	int *finish = (int*)calloc(n,sizeof(int)) ; // 0 initially for all of the processes....  
	int flag , found = 1 ; 
	while(found) { // thus, nothing was found in one run, the loop breaks ... 
		found = 0 ; 
		for( int i = 0 ; i < n ; i++ ) {
			if (finish[i] == 0 ) {
				flag = 1 ;  // initially 1 
				for(int j = 0 ; j < m ; j++) {
					if(need[i*m + j] > work[j]) // if need_i <= work 
						flag = 0 ; 
				}
				if (flag == 1) {
					for(int j = 0 ; j < m ; j++)
						work[j] = work[j] + allocate[i*m + j] ; 
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
	
	cout<<" Enter the number of resources " ;  cin >> m ; 
	cout<<" Enter the number of processes " ; cin>> n ; 
	cout<<" Enter the available resources "<<endl ;  available = take_input(1,m) ;  print(available,1,m) ; 
	cout<<" Enter the maximum #resources/process [row wise]"<<endl ; maximum = take_input(n,m) ; print(maximum,n,m) ;
	cout<<" Enter the #resources allocated/process [row wise]"<<endl ; allocation = take_input(n,m) ; print(allocation,n,m) ;
	
	int process ; // process which requests it. 
	int *request ; 
	
	need = (int*)malloc(sizeof(int)*m*n) ; 
	avail_copy = (int*)malloc(sizeof(int)*m) ; 
	need_copy = (int*)malloc(sizeof(int)*m*n) ;
	max_copy = (int*)malloc(sizeof(int)*m*n) ;  
	alloc_copy = (int*)malloc(sizeof(int)*m*n) ; 

	for(int i = 0 ; i < n ; i++) {
		for(int j = 0 ; j < m ; j++) {
			need[i*m + j] = maximum[i*m + j] - allocation[i*m + j] ; 
		}
	}  		// compute need 
	int flag = 1 , break_flag = 1 ; 
	while(1) {
		switch(prompt()) {
			case 1 : 
						copy(avail_copy,available , m) ; 
						copy(need_copy,need , n*m) ; 
						copy(alloc_copy, allocation, n*m) ; 
						copy(max_copy, maximum, n*m) ; 
						if (safety(need_copy,alloc_copy,max_copy,avail_copy,n,m) == 0 )
							cout<<"unsafe"<<endl ; 
						else 
							cout<<"safe"<<endl ; 
						break ; 
			case 2 :	
						copy(avail_copy,available , m) ; 
						copy(need_copy,need , n*m) ; 
						copy(alloc_copy, allocation, n*m) ; 
						copy(max_copy, maximum, n*m) ; 
						break_flag = 1;
						cout<<" Enter the process -> " ;
						cin>> process ; 
						cout<<" Enter the request -> " ; 
						request = take_input(1,m); // request for resources  
						for(int i = 0 ; i < m ; i++)  {
							if( request[i] > need[(process - 1)*m + i] ) {
								cout<<"Invalid" ; 
								break_flag = 0 ; 
								break ; 
							}
							if ( request[i] > avail_copy[i] ){
								cout<<" Can't be done right now " ; 
								break_flag = 0 ; 
								break ; // needs to break off from the case .... 
							}
						} 			// request < need 
						if (break_flag) {
							for ( int i = 0 ; i < m ; i++ ) {
								avail_copy[i] = avail_copy[i] - request[i] ; 
								alloc_copy[(process-1)*m + i] = alloc_copy[(process-1)*m + i] + request[i] ; 
								need_copy[(process-1)*m + i] = need_copy[(process-1)*m + i] - request[i] ; 
							}
							if (safety(need_copy,alloc_copy,max_copy,avail_copy,n,m) == 0 )
								cout<<" Not right now "<<endl ; 
							else 
								cout<<" CAN BE ALLOCATED "<<endl ; 
						}
						break ; 	
			case 3 : exit(0) ;  
		}
	}
}