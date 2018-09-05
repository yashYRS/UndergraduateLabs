#include<iostream>
#include<stdlib.h>
using namespace std ;


int prompt (){
	cout<<"\n\n Choose one of the following - "<<endl;
	cout<<" 1. Insert an edge"<<endl;
	cout<<" 2. Display graph in Array format..  "<<endl;
	cout<<" 3. Depth First Traversal .. "<<endl ; 
	cout<<" 4. Exit"<<endl; 
	int a ; 
	cin>> a; 
	return a ; 
}
void disp(int *g,int n) {
	for(int i = 0 ; i < n ;i++) 
		cout<<" "<<g[i];
} 

void display_dfs(int *g,int n){
	int *dfsstack = (int *)calloc(n,sizeof(int)) ; 
	for(int i = 0 ; i < n ; i++) 
		dfsstack[i] = -1 ; 
	int *marked_graph = (int *)calloc(n,sizeof(int)) ; // shows whether a particular vertex has been accounted for.. 
	int *push_order = (int *)calloc(n,sizeof(int)) ;
	int *pop_order = (int *)calloc(n,sizeof(int)) ;
	int top = 0;
	int push = 1, pop = 1; 
	int i,temp = n ; dfsstack[top] = 0 ; marked_graph[0] = 1; push_order[0] = push; // initializations 
	cout<<" The Depth First Traversal :- \t " ; 
	cout<<" "<<1;
	int curr_node ; 
	for(int next_node = 0 ; next_node < n ; next_node++) {
		curr_node = next_node ;
		while ( temp > 1 ) {
			for( i = 0 ; i < n ; i++) {		// check for the adjacent vertices..
				if(g[curr_node*n +i] == 1 && marked_graph[i]==0 && curr_node!=i ){
					cout<<"  "<<i+1 ; // print out the node 
					dfsstack[++top] = i ; // node added to the stack ; 
					push_order[i] = ++push ; // store the push order ;
					marked_graph[i] = 1; // mark the node ;
					temp-- ; 
					curr_node = dfsstack[top] ;
					disp(dfsstack,n); cout<<endl; 
					break; // since only the adjacent node needs to added 
				}
				else if(i == n-1) { 	// no more children left.. 
					pop_order[ dfsstack[top] ] = pop++; 
					if(top > 0) { 
						dfsstack[top--] = -1 ; 
						curr_node = dfsstack[top]; break ; 
					}
					else { 		
						dfsstack[top] = -1 ; 
						curr_node = next_node + 1; break ; 
					}
				}
			}	
		}
		while( top >= 0 )
			pop_order[dfsstack[top--]] = pop++ ; 
		
	}
	cout<<"\n The push order ->   "; disp(push_order,n) ; 
	cout<<"\n The pop order ->   "; disp(pop_order,n) ; 
	free(dfsstack); free(marked_graph); free(pop_order) ; free(push_order) ; 

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