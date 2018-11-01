#include<iostream>
#include<stdlib.h>

using namespace std; 

void disp_matrix(int *g,int n) {
	for(int i = 0 ; i < n; i++) {
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

int min(int a, int b) {
	if ( a < b ) 
		return a ; 
	else 
		return b ; 
}

int display_prompt (){
	cout<<endl ; 
	cout<< " 1. Insert a edge "<<endl ;
	cout<< " 2. Display Adjacency Matrix"<<endl ;
	cout<< " 3. All pairs shortest path "<<endl ;
	cout<< " 4. Exit  "<<endl ; 
	cout<<endl ; 
	int a ;
	cin>> a; 
	return a ; 
}


void floyd(int *g, int n) {
	int *short_pair  = (int *)calloc( n*n, sizeof(int)) ; 
	int *prev_val = (int*)calloc(n*n, sizeof(int)) ; 
	copy(prev_val , g, n);
 	for(int intermediate = 0 ; intermediate < n ; intermediate++ ) {
		for(int row = 0 ; row < n ; row++ )  {
			for(int col = 0 ; col < n ; col++ ) 
				short_pair [row*n + col ] = min( prev_val[row*n + col ] , ( prev_val[row*n + intermediate] + g[intermediate*n + col]) ) ;
		}
		copy(prev_val, short_pair, n) ; 
	} 
	disp_matrix(short_pair, n) ; 
}


int main() {
	int flag  = 1; 
	int n, te, f, s , weight; 
	cout<< " (Directed) Enter number of vertices -> "; cin>>n; 
	te = n ; 
	int *g_mat = (int*)calloc(n*n , sizeof(int) ) ; 
	for(int i = 0 ; i < n ; i++) 
		for(int j = 0 ; j < n ; j++) 
			if (i!=j)
				g_mat[i*n + j] = 1000 ; 
	while(flag){
		switch(display_prompt()){
			case 1: cout<<"Enter vertices on the edge - "; cin >> f; cin >> s; 
					cout<<" Enter weight " ; cin>> weight ; 
					g_mat[ (f-1)*n  + s - 1 ] = weight;
					break; 
			case 2: disp_matrix(g_mat,n); break;
			case 3: floyd(g_mat,n); break ;  
			case 4: flag = 0 ; break ; 
		}
	}
	return 0 ; 
}

