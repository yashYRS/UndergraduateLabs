#include<iostream>
#include<stdlib.h>
using namespace std ; 

int* get_inp (int n) {
	int *arr =  (int*)malloc(sizeof(int)*n); // allocate 
	for (int i = 0 ; i < n ; i++ )
		cin>>arr[i] ; 
	return arr ;
}

int firstpossible (int *a , int n) {
	while(1) {
		for (int i = 0 ; i < n ; i++) {
			if ( a[i] == 0 )
				return i ; 
			else 
				a[i] = 0 ; 
		}
	}
}

void print(int *a , int n) {
	for (int i = 0 ; i < n ; i++ )
		cout<<" "<<a[i] ; 
	cout<<endl ; 
}

int notin (int val , int *arr , int n) {
	for (int i = 0 ; i < n ; i++ ) 
		if (val == arr[i] )
			return 0 ; 
	return 1 ; // 1 if not in the array 
}

void second_chance (int *r , int *c ,  int rnum , int cnum ) {	
	int *used = (int *)calloc(cnum , sizeof(int)) ; 
	int fill = 0 , hit = 0 , index ; 
	for (int i = 0 ; i < rnum ; i++) {
		if ( notin(r[i], c , cnum) == 1 ) {
			if ( fill == cnum ) {
				index = firstpossible(used, cnum) ; 
				c[index] = r[i] ; 
				used[index] = 0 ; // reset 
			}
			else {
				c[fill] = r[i] ; // normal  
				used[fill++] = 0 ; // insert the value in used as well,
			}
		}
		else {
			hit++ ; 
			for (int j = 0 ; j < cnum ; j++ )
				if ( r[i] == c[j] ) 
					used[j] = 1 ; // increment 
		}
		print(c, cnum) ; 
	}
	cout<<" The hit ratio ->"<< (float)hit/rnum ; 
}

int main() {

	int cache_size , num_req ; // 
	cout<<" Enter cache size " ; cin>>cache_size ;
	int *cache = (int*)malloc(sizeof(int)*cache_size); // allocate 


	cout<<" Enter the number of requests " ; cin>>num_req ; 
	cout<<" Enter the requests " ; 
	int *requests = get_inp(num_req) ; 

	second_chance(requests ,cache , num_req, cache_size) ; 



	return 0 ; 
}
	