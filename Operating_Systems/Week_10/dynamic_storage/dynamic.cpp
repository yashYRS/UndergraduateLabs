#include<iostream>
#include<stdlib.h>
using namespace std; 

int find_min(int *a , int n) {
	int min = a[0] ; 
	int index = 0 ; 
	for(int i =0 ;i < n ; i++) {
		if ( min > a[i] ) {
			min = a[i] ; 
			index = i ; 
		}
	}
	return index ; 
}

void first_fit(int *p , int n) {
	cout<<" Enter the allocation required " ;
	int block ; cin>> block ; int flag = 1 ; 
	for(int i = 0 ; i < n ; i++) {
		if ( block <= p[i] ) {
			p[i] = p[i] - block ; 
			flag = 0 ; 
			break ; 
		}
	}
	 
	if(flag) 
		cout<<" Allocation not possible " ; 
}

void worst_fit(int *p , int n) {
	cout<<" Enter the allocation required " ;
	int block ; cin>> block ; 
	int max = 0 , index = 0 ; 
	for( int i=0 ; i < n ; i++) {
		if (max < p[i]) {
			index = i ; 
			max = p[i] ; 
		}
	}
	if (max >= block) 
		p[index] = p[index] - block ; 
	else 
		cout<<" Can't be allocated " ; 

}

void best_fit(int *p , int n) {
	cout<<" Enter the allocation required " ;
	int block ; cin>> block ; 
	int *temp = (int*)malloc(sizeof(int)*n) ; 
	int *index = (int*)malloc(sizeof(int)*n) ; 
	int ind = 0 ; 
	for (int i = 0 ; i < n ; i++) {
		if (block <= p[i]) {
			temp[ind] = p[i] ; 
			index[ind] = i ; 
			ind++ ;
		}
	}
	if (ind > 0 ) {
		ind = find_min(temp,ind) ; 
		p[index[ind]] = p[index[ind]] - block; 
	}
	else 
		cout<<" Can't be allocated " ; 
}

int prompt() {
	int a ; 
	cout<<"\n\n 1. First-fit 2. Worst-fit 3. Best-fit 4. Exit\n" ; 
	cout<<"  Enter you choice -> "; 
	cin>> a ; 
	return a ; 
}

void print(int *a , int n) {
	cout<<"\n The partitions are -> " ; 
	for(int i = 0 ; i < n ;i++) 
		cout<<a[i]<<" " ; 
	return ; 
}

void stats(int *a, int n) {
	int sum = 0 ; 
	for(int i = 0 ; i < n ; i++) 
		sum = sum + a[i] ; 
	cout<<" Total memory left -> "<< sum ; 

}

int main() {
	int n ; // number of partitions 
	cout<<" Enter the number of partitions - " ; cin>> n; 
	int partitions[n] ; // list of holes 
	for(int i = 0 ; i < n ; i++ ) {
		cout<<" Enter the size of the partition " ; 
		cin>>partitions[i] ; 
	}
	while(1) {
		switch(prompt()) {
			case 1 :
					first_fit(partitions , n ) ;  print(partitions,n) ; stats(partitions, n) ; 
					break ; 
			case 2 : 
					worst_fit(partitions , n ) ; print(partitions,n) ; stats(partitions, n) ; 
					break ;
			case 3 : 
					best_fit(partitions , n ) ; print(partitions,n) ; stats(partitions, n) ; 
					break ; 
			case 4 : exit(0); 
		}
	}

}