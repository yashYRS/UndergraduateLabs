#include<iostream>
#include<stdlib.h>
using namespace std ;


int prompt (){
	cout<<"\n\n Choose one of the following - "<<endl;
	cout<<" 1. Insert an edge"<<endl;
	cout<<" 2. Display graph in Array format  "<<endl;
	cout<<" 3. Topological Sort using Source Removal  "<<endl ; 
	cout<<" 4. Exit"<<endl; 
	int a ; 
	cin>> a; 
	return a ; 
}
void disp(int *g,int n) {
	for(int i = 0 ; i < n ;i++) 
		cout<<" "<<g[i];
} 

int next_remove(int *g, int n, int *m) {
	int sum  ; 
	for(int col = 0 ; col < n ; col++ ){
		sum = 0 ; 	
		if(m[col]==0) {				// check only for nodes that haven't been removed..
			for(int i = 0 ; i < n ; i++ )
				sum = sum + g[i*n + col] ;  	// find all incoming nodes.. 
			if( sum == 0 )
				return col ; // if no incoming nodes return 
		}
	}
	return -1 ; // i.e no such column exists 
}

void topo_sort(int *g, int n ){
	int next, temp = n  ; 
	int *marked = (int *)calloc(n,sizeof(int)) ; 
	while(temp > 0) {
		next = next_remove(g,n,marked) ; 
		if ( next == -1)
			break ; 
		else {
			for(int i = 0 ; i < n ; i++) 
				g[next*n + i] = 0 ; // remove everything from the row containing next 
			cout<<" "<<next+1 ; 
			marked[next] = 1; 
			temp-- ; 
		}
	}
	if ( temp > 0) 
		cout<<" Can't be done " ; 
}


void display_matrix(int *g,int n){
	for ( int i = 0 ; i < n ; i++){
		for ( int j = 0 ; j < n ; j++)
			cout<<"  "<<g[i*n + j];
		cout<<endl ; 
	}
}

int main() {
	// for graph 
	int flag = 1 ; 
	int n,first,second ;  // n - #vertices 
	cout<<" Note - following algorithm works for only directed acyclic graph "<<endl ; 
	cout<< " Enter Number of vertices [DIRECTED GRAPH ASSUMED]-"; 
	cin>>n ; 
	int *graph_matrix = (int *)calloc(n*n,sizeof(int)) ; 	

	while(flag){ 
		switch(prompt()){
			case 1 :	cout<< " Enter the vertices on the edge - ";
						cin>>first ;
						cin>>second ; 
						graph_matrix[ (first-1)*n + second-1 ] = 1 ; // equivalent to a[first-1][second-1]
						break; 
			case 2 : display_matrix(graph_matrix,n); break; 
			case 3 : topo_sort(graph_matrix,n) ; break ; 
			case 4 : flag = 0 ; break ; 
		}
	}
	return 0 ; 
}