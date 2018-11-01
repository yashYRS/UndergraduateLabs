#include<iostream>
#include<stdlib.h>

using namespace std; 

void disp_matrix(int *g,int n) {
	for(int i = 0 ; i < n; i++){
		for(int j = 0;j <n ; j++)
			cout<<"  "<<g[i*n + j];
		cout<<endl ; 
	}
}

void copy(int *a , int *b , int n ) {
	for(int i = 0 ; i < n ; i++ ) 
		for(int j = 0 ; j < n ; j++) 
			a[i*n + j] = b[i*n + j] ;  // initially the nodes directly reachable reached.. 
}


void warshall(int *g, int n) {
	int *trans_clos  = (int *)calloc( n*n, sizeof(int)) ; 
	int *prev_val = (int*)calloc(n*n, sizeof(int)) ; 
	copy(prev_val , g, n);

 	for(int intermediate = 0 ; intermediate < n ; intermediate++ ) {
		for(int row = 0 ; row < n ; row++ )  {
			for(int col = 0 ; col < n ; col++ ) {
				trans_clos [row*n + col ] =  prev_val[row*n + col ] | ( prev_val[row*n + intermediate] & g[intermediate*n + col]) ; 
			}
		}
		copy(prev_val, trans_clos, n) ; 
	} 
	disp_matrix(trans_clos, n) ; 
}

int display_prompt (){
	cout<<endl ; 
	cout<< " 1. Insert a edge "<<endl ;
	cout<< " 2. Display Adjacency Matrix"<<endl ;
	cout<< " 3. Transitive closure of the Graph "<<endl ;
	cout<< " 4. Exit  "<<endl ; 
	cout<<endl ; 
	int a ;
	cin>> a; 
	return a ; 
}

int main() {
	int flag  = 1; 
	int n, te, f, s; 
	cout<< " (Directed) Enter number of vertices -> ";
	cin>>n; 
	te = n ; 
	int *g_mat = (int*)calloc(n*n , sizeof(int) ) ; 
	while(flag){
		switch(display_prompt()){
			case 1: cout<<"Enter vertices on the edge - ";
						cin >> f; cin >> s; 
						g_mat[ (f-1)*n  + s - 1 ] = 1;
						break; 
			case 2:  disp_matrix(g_mat,n); break;
			case 3: warshall(g_mat,n); break ;  
			case 4: flag = 0 ; break ; 
		}
	}
	return 0 ; 
}
