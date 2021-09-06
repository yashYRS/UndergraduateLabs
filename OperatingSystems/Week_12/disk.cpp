#include<iostream>
#include<stdlib.h>
using namespace std ; 
int limit ; 

int* takeip( int n ) {
	int *a = (int*)malloc(sizeof(int)*n) ; 
	for (int i = 0 ; i < n ; i++) 
		cin>>a[i] ;
	return a ; 
}

int* copy(int *a , int n) {
	int *b = (int *)malloc(sizeof(int)*n) ; 
	for (int i = 0 ; i < n ; i++ )
		b[i] = a[i] ; 
	return b ; 
}

int mod (int a) {
	if (a > 0)
		return a ; 
	return -a ; 
}

int getmin(int h , int *a , int *d , int n ) {
	int mindist = 100000 , ind ;  
	for (int i = 0 ; i < n ; i++ ) {
		if (d[i] == 0 ) {
			if ( mindist > mod(h - a[i]) ) {
				mindist = mod(h-a[i]) ; 
				ind = i ; 
			}
		}
	}
	return ind ; 
}

void sort (int *a , int n ) {
	int temp ; 
	for (int i = 0 ; i < n - 1; i++ ) {
		for (int j = 0 ; j < n - i - 1 ; j ++ ) {
			if (a[j] > a[j+1] ) {
				temp = a[j] ; 
				a[j] = a[j+1] ; 
				a[j+1] = temp ; 
			}
		}
	}
}
void fifo (int *a , int n , int head ) {
	int moves = 0 ; 
	cout<<"\n FIFO :- " ; 
	for (int i = 0 ; i < n ; i++ ) {
		moves = moves + mod(head - a[i]) ; 
		cout<<" "<<a[i] ; 
		head = a[i] ; 
	}
	cout<<" \n Moves -> "<<moves ; 
	free(a) ; 
}

void sstf (int *a , int n , int head ) {
	int moves = 0 , temp_head ; 
	cout << " \n SSTF :- " ; 
	int *done = (int *)calloc(n, sizeof(int )) ;
	for (int i = 0 ; i < n ; i++ ) {
		temp_head = getmin(head, a , done , n ) ; 
		moves = moves + mod(head - a[temp_head]) ; 
		done[temp_head] = 1 ; 
		cout<<" "<<a[temp_head] ; 
		head = a[temp_head] ; 
	}
	cout<<" \n Moves -> "<<moves ; 
	free(done) ; 
	free(a) ; 
}

void scan (int *a , int n , int head ) {
	int moves = 0 , temp = head ; 
	cout<<"\n SCAN :- " ; 
	sort(a,n); 
	for (int i = 0 ; i < n ; i++ ) {
		if (a[i] < head) 
			continue ; 
		moves = moves + a[i] - head  ;
		cout<<" "<<a[i] ; 
		head = a[i] ;
	}
	moves = moves + limit - head ; 
	head = limit ; 
	for (int i = n - 1 ; i >= 0 ; i-- ) {
		if ( a[i] > temp )
			continue ; 
		moves = moves + head - a[i] ; 
		cout<<" "<<a[i] ; 
		head = a[i] ; 
	}
	cout<<" \n Moves -> "<<moves ; 
	free(a) ; 
}

void cscan (int *a , int n , int head ) {
	int moves = 0 , temp = head; 
	cout<<"\n C-SCAN :- " ; 
	sort(a,n); 
	for (int i = 0 ; i < n ; i++ ) {
		if (a[i] < head) 
			continue ; 
		moves = moves + a[i] - head  ;
		cout<<" "<<a[i] ; 
		head = a[i] ;
	}
	moves = moves + limit - head + 1 ; 
	head = 0 ; 
	for (int i = 0 ; i < n ; i++ ) {
		if ( a[i] > temp )
			break ; 
		moves = moves + a[i] - head  ; 
		cout<<" "<<a[i] ; 
		head = a[i] ; 
	}
	cout<<" \n Moves -> "<<moves ; 
	free(a) ;  
}

int prompt () {
	cout<<"\n\n Choose one -> 1. Fifo 2. SSTF 3. SCAN 4. C-SCAN 5. Exit \n" ; 
	int a; cin>>a ; cout<<endl ;
	return a ; 
}
int main() { 
	int req_n , head ; // number of partitions 
	int *req ; // list of holes 
	cout<<" Enter the limit " ; cin>>limit ; 
	cout<<"Enter the number of requests -";
	cin>>req_n ; 
	cout<<" Enter the requests " ; req = takeip (req_n) ; 
	cout<<" Enter head position " ; cin>> head ; 
	while (1) { 
		switch(prompt()) {
			case 1 : fifo(copy(req, req_n), req_n , head) ; break ; 
			case 2 : sstf(copy(req, req_n ), req_n, head) ; break ; 
			case 3 : scan(copy(req, req_n) , req_n , head) ; break ; 
			case 4 : cscan(copy(req, req_n) , req_n , head) ; break ; 
			case 5 : exit(0) ; 
		}
	}


}