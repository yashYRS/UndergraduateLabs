#include<iostream>
#include<stdlib.h>
using namespace std ; 

int* get_inp (int n) {
	int *arr =  (int*)malloc(sizeof(int)*n); // allocate 
	for (int i = 0 ; i < n ; i++ )
		cin>>arr[i] ; 
	return arr ;
}

int prompt() {
	cout<<" Enter a choice  "<<endl  ; 
	cout<<" 1. FIFO "<<endl  ;  
	cout<<" 2. Optimal "<<endl  ; 
	cout<<" 3. LRU "<<endl  ; 
	cout<<" 4. Exit "<<endl  ; 
	int c ; cin >> c ; return c ; 
}

void print(int *a , int n) {
	for (int i = 0 ; i < n ; i++ )
		cout<<" "<<a[i] ; 
	cout<<endl ; 
}

int* copy(int *a , int n) {
	int* b = (int*)malloc(sizeof(int)*n) ; 
	for (int i = 0 ; i < n ; i++)
		b[i] = a[i] ; 
	return b ; 
}
int notin (int val , int *arr , int n) {
	for (int i = 0 ; i < n ; i++ ) 
		if (val == arr[i] )
			return 0 ; 
	return 1 ; // 1 if not in the array 
}

int computefind ( int *r , int ind, int n , int val ) {
	for (int i = ind+1 ; i < n ; i++  )
		if (r[i] == val ) 
			return i - ind ; 
	return n - ind ;  
}
int leastused (int *a , int n) {
	int ind , max = 0 ; 
	for (int i = 0 ; i < n ; i++) {
		if (max < a[i]) {
			ind = i ; 
			max = a[i] ; 
		}
	}
	return ind ; // index returned.. 
}

void fifo (int *r , int *c , int rnum , int cnum ) {
	int entry = 0 , hit = 0 ; 
	cout<<" For FIFO page replacement -> " ; 
	for ( int i = 0 ; i < rnum ; i++ ) { 		 
		if (notin(r[i] , c, cnum) == 1) {
			c[entry] = r[i] ;  
			entry = (entry + 1)%cnum ; 
		}
		else 
			hit++ ; 
		print(c,cnum) ; 
	}
	cout<<" The hit ratio ->"<< (float)hit/rnum ; 
}

void lru (int *r , int *c ,  int rnum , int cnum ) {
	int *used = (int *)calloc(cnum , sizeof(int)) ; 
	int fill = 0 , hit = 0 , index ; 
	for (int i = 0 ; i < rnum ; i++) {
		if ( notin(r[i], c , cnum) == 1 ) {
			if ( fill == cnum ) {
				index = leastused(used, cnum) ; 
				c[index] = r[i] ; 
				used[index] = 0 ; // reset 
			}
			else {
				c[fill] = r[i] ; // normal  
				used[fill++] = 0 ; // insert the value in used as well,
			}
		}
		else
			hit++ ; 
		for (int j = 0 ; j < cnum ; j++ )
			if ( r[i] != c[j] ) 
				used[j] = used[j] + 1 ; 
			else 
				used[j] = 0 ; 
		print(c, cnum) ; 
	}
	cout<<" The hit ratio ->"<< (float)hit/rnum ; 
}

void optimal (int *r , int *c , int rnum , int cnum ) {
	int *find = (int*)malloc(sizeof(int)) ; 
	int fill = 0 , hit = 0 , index ; 
	for (int i = 0 ; i < rnum ; i++) {
		if ( notin(r[i], c , cnum) == 1 ) {
			if ( fill == cnum ) {
				index = leastused(find,cnum ) ; // get the index which is going to be used last 
				c[index] = r[i] ;  
				find[index] = computefind(r, i , rnum , r[i]) ; 
				// get find array ready 
			}
			else {
				c[fill] = r[i] ; // normal  
				find[fill] = computefind(r, i , rnum , r[i]) ;
				fill++ ; 
			}
		}
		else 
			hit++ ; 
		for (int j = 0 ; j < cnum ; j++) 
			find[j]-- ; 
		print(c , cnum ) ; 
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

	while(1) {
		switch(prompt()) {
			case 1 :
					fifo (requests,copy(cache,cache_size) , num_req , cache_size) ;  
					break ;
			case 2 :
					optimal (requests,copy(cache,cache_size) , num_req , cache_size ) ;  
					break ; 
			case 3 : 
					lru (requests,copy(cache , cache_size) ,  num_req , cache_size ) ; 
					break ; 
			case 4 : 
					exit(0) ; 
		}
	}


	return 0 ; 
}
	