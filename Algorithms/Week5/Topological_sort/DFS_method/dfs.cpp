#include<iostream>
#include<stdlib.h>
using namespace std ;


int prompt (){
	cout<<"\n\n Choose one of the following - "<<endl;
	cout<<" 1. Insert an edge"<<endl;
	cout<<" 2. Display graph as Matrix  "<<endl;
	cout<<" 3. Topological Sort "<<endl ; 
	cout<<" 4. Exit"<<endl; 
	int a ; 
	cin>> a; 
	return a ; 
}
void disp(int *g,int n) {
	for(int i = n-1 ; i >=0 ;i--) 
		cout<<" "<<g[i];
} 
void reverse_index(int *p,int n) {
	int *t = (int *) malloc(sizeof(int)*n) ; 
	for(int i = 0 ; i < n ; i++)
		t[p[i] - 1 ] = i+1 ; 
	disp(t,n) ; 
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

void display_dfs(int *g,int n){
	int *dfsstack = (int *)calloc(n,sizeof(int)) ; 
	for(int i = 0 ; i < n ; i++) 
		dfsstack[i] = -1 ; 
	int *marked_graph = (int *)calloc(n,sizeof(int)) ; // shows whether a particular vertex has been accounted for.. 
	int *push_order = (int *)calloc(n,sizeof(int)) ;
	int *pop_order = (int *)calloc(n,sizeof(int)) ;
	int *top_sort = (int *) calloc(n,sizeof(int)) ; 
	int top = 0;
	int push = 0, pop = 1; 
	int i,temp = n ;  // initializations 
	int curr_node ;
		if(top == 0 ){
			curr_node = next_remove(g,n,marked_graph) ; 
			dfsstack[top] = curr_node ; 
			push_order[curr_node] = ++push ; 
			marked_graph[curr_node] = 1 ; 
			temp-- ;
		}
		while ( temp > 0 ) {
			for( i = 0 ; i < n ; i++) {		// check for the adjacent vertices..
				if(g[curr_node*n +i] == 1 && marked_graph[i]==0 && curr_node!=i ){
					dfsstack[++top] = i ; // node added to the stack ; 
					push_order[i] = ++push ; // store the push order ;
					marked_graph[i] = 1; // mark the node ;
					temp-- ; 
					curr_node = dfsstack[top] ;
					break; // since only the adjacent node needs to added 
				}
				else if(i == n-1) { 	// no more children left.. 
					pop_order[ dfsstack[top] ] = pop++; 
					if(top > 0) { 
						dfsstack[top--] = -1 ; 
						curr_node = dfsstack[top]; break ; 
					}
					else if(top == 0 ){
						curr_node = next_remove(g,n,marked_graph) ; 
						dfsstack[top] = curr_node ; 
						push_order[curr_node] = ++push ; 
						marked_graph[curr_node] = 1 ; 
						temp-- ;
						break ; 
					}
				}
			}	
		}
	while( top >= 0 )
		pop_order[dfsstack[top--]] = pop++ ; 
	 cout<<"\nTopological Sort : "; reverse_index(pop_order,n) ; 
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
	cout<< " Enter Number of vertices [DIRECTED GRAPH ASSUMED] -"; 
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
			case 3 : display_dfs(graph_matrix,n) ; break ; 
			case 4 : flag = 0 ; break ; 
		}
	}
	return 0 ; 
}