#include<iostream>
#include<stdlib.h>

using namespace std;

#define table_size 100

void insert(int *table, int num) {
	int index = num % 10 ;  // hash function 
	while ( table[index] > 0 ) 
		index = (index +  1) % table_size ;  // linear probing 
	table[index] = num ; 
}

int search (int *table , int num , int *succ, int *fail ) {
	int index = num % 10 , comparisons = 0 ; 
	while( table[index] != num && comparisons < 100 )  {
		index = (index +  1) % table_size ; 
		comparisons++ ; 
	}
	if (comparisons == 100)   {
		*fail = *fail + comparisons ; 
		return 0 ; 
	}
	*succ = *succ + comparisons ; 
	return 1 ; 

}

void print(int *table) {
	for(int i =0 ; i < table_size ; i++ ) 
		cout<<" "<<table[i] ; 
}

int main() {
	int *hash_table ; // h(x) == x%10
	int num, success, fail, s_cases, u_cases, elements = 25; 

	for (int i = 0 ; i < 3 ; i++ )  {
		s_cases = 0 ; u_cases = 0 ; success = 0 ; fail = 0 ; 
		hash_table = (int *)calloc(table_size, sizeof(int)) ; 
		for(int j = 0 ; j < elements ; j++) {  
			num = rand()%table_size ; 	// generates a number between 0 and 99 	
			insert(hash_table, num+1 ) ; 	// number converted to 1 and table_size 
		}
		for(int j = 0 ; j < 20 ;  j++ ) { // 20 searches per case 
			num = rand()%table_size ; 
			if ( search (hash_table ,num , &success , &fail )  == 1 ) 
				s_cases++ ; 
			else 
				u_cases++ ; 
		}
		cout<<elements<< "\% filled  1. Success -> "<< success/s_cases <<" 2. Failure -> "<< fail/u_cases<<endl ; 
/*		print(hash_table) ;
		cout<<endl ; */
		elements = elements + 25  ; 
		free(hash_table) ; 
	}

	return 0 ; 
}
