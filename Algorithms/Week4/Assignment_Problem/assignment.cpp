#include<iostream>
#include<stdlib.h>

using namespace std ; 

int *result ;
int minm ; 

void next_perm(int *p,int *p2,int a,int b,int c) ; 
void swap(int *a,int *b) {
	int temp = *b ; 
	*b = *a ; 
	*a = temp ; 
}

int getcost(int *perm, int *per_job , int n ) {
	int add = 0 ;
	for(int i = 0 ; i < n ; i++)
		add = add + per_job[ i*n + perm[i] - 1 ] ;  // perm[i]  has the column name, i == row 
	return add ; 
}

void disp_array(int *arr,int n) {
	for(int i = 0 ; i < n ; i++)
		cout<<arr[i]<<" " ; 
}

void disp(int *mat, int n){
	for(int i = 0 ; i < n ; i ++ ){
		for(int j = 0 ; j < n ; j++ )
			cout<<mat[i*n + j]<<"  " ; 
		cout<<endl ; 
	}
}


int main() {
	

	cout<< " Enter the number of jobs -> " ; 
	int n,f,cost ; // can be changed later 
	cin>>n; 
	int *person_job = (int *)calloc(n*n , sizeof(int)) ; // job in column, person in row.. 
	int *perm_number = (int *)malloc(sizeof(int)*n) ; 
	result = (int *)malloc(sizeof(int)*n) ;

	

	for(int i = 0 ; i < n ; i ++) {
		cout<< "\n\n Enter the time taken by person "<< i+1;  
		perm_number[i] = i+1 ; // so initially perm_number = 1,2,3. .. n  
		for ( int j = 0 ; j < n ; j++) {
			cout<< "\n\t\t\t\t to complete job "<<j+1<<"  " ; 
			cin>>person_job[i*n + j] ; 
		}	
		cout<< endl ; 
	} 										// Taking input.. 
	minm = getcost(perm_number,person_job,n) ; 		// initialize minimum value 
	next_perm(perm_number,person_job,0,n-1,n) ; 	// get seq having minimum value 
	cout<< "\n\n The result :- [a] Min cost -- "<<minm <<"\n\t\t [b] Sequence -- " ; 
	disp_array(result,n) ; 
	return 0 ; 
}

void next_perm(int *perm,int *person, int l, int r,int n) {
   if (l == r){		// new permutation
   		int cost = getcost(perm,person,n);
   		if ( cost < minm ) {
   			for(int i = 0 ; i < n ; i++ )
   				result[i] = perm[i] ; 
   			minm = cost ; 
   		}
   }
   else {
	   for (int i = l; i <= r; i++)
	   {
	       swap((perm+l), (perm+i));
	       next_perm(perm,person, l+1,r,n);		// if we get better result, get it.. 
	       swap((perm+l), (perm+i)); //backtrack
	   }
	}
}
