#include<iostream>
#include<stdlib.h>
using namespace std ;


int prompt (){
	cout<<"\n\n Choose one of the following - "<<endl;
	cout<<" 1. Insert an edge"<<endl;
	cout<<" 2. Display graph in Array format..  "<<endl;
	cout<<" 3. Breadth First Traversal .. "<<endl ; 
	cout<<" 4. Exit"<<endl; 
	int a ; 
	cin>> a; 
	return a ; 
}

void display_bfs(int *g,int n){
	int *bfsqueue = (int *)calloc(n,sizeof(int)) ; // the bfs queue.. 
	int *marked_graph = (int *)calloc(n,sizeof(int)) ; // shows whether a particular vertex has been accounted for.. 
	int start_index = 0 ; 
	int temp = n ; bfsqueue[start_index] = 0 ; marked_graph[0] = 1;  // initializations 
	cout<<" The Breadth First Traversal :- \t " ; 
	for(int curr_node = 0 ; curr_node < n ; curr_node++) {
		while ( temp-- > 0 ) {
			for(int i = curr_node+1 ; i < n ; i++) {
				if(g[curr_node*n +i] == 1 && marked_graph[i]==0 && curr_node!=i){
					marked_graph[i] = 1; 	
					bfsqueue[end_index] = i ; // add children to the queue ; 
					end_index++ ; 
				}
			}	
			cout<<" "<<bfsqueue[start_index++] + 1 ; 
			curr_node =	bfsqueue[start_index] ; // the head of the queue removed.. 
		}
	}
	free(bfsqueue); 
	free(marked_graph);

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
			case 3 : display_bfs(graph_matrix,n) ; break ; 
			case 4 : flag = 0 ; break ; 
		}
	}
	return 0 ; 
}