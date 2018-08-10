#include<iostream>
#include<stdlib.h>
using namespace std ;

struct Node {
	int data; 
	Node *next ; 

};
typedef struct Node* Nodeptr ; 

int prompt (){
	cout<<"\n\n Choose one of the following - "<<endl;
	cout<<" 1. Insert an edge"<<endl;
	cout<<" 2. Display Matrix "<<endl;
	cout<<" 3. Display List "<<endl;
	cout<<" 4. Exit"<<endl; 
	int a ; 
	cin>> a; 
	return a ; 
}


Nodeptr create(int d){
	Nodeptr temp = (Nodeptr) malloc(sizeof(struct Node));
	temp->data = d ; 
	temp->next = NULL ; 
	return temp ; 
}

void display_matrix(int g[][10],int n){
	for ( int i = 0 ; i < n ; i++){
		for ( int j = 0 ; j < n ; j++)
			cout<<"  "<<g[i][j];
		cout<<endl ; 
	}
}

void display(Nodeptr gn){
	while(gn){
		cout<<gn->data<< " ---> ";
		gn = gn->next ; 
	}
	cout<< " NULL " << endl ; 
}
Nodeptr insert(Nodeptr head,int d){
	Nodeptr temp = head ; 
	while(temp->next)
		temp = temp->next ; 
	temp->next = create(d);
	return head; 
}
void display_list(Nodeptr g[],int n){
	cout<< "\n The list is as follows - \n"<<endl ; 
	for (int i = 0 ; i < n ; i++ )
		display(g[i]);
}
int main() {
	// for graph 
	int flag = 1 ; 
	int n,temp,first,second ;  // n - #vertices 
	cout<< " Enter Number of vertices [UNDIRECTED GRAPH ASSUMED] -"; 
	cin>>n ; 
	temp = n ;
	int graph_matrix[10][10]; 
	for (int i = 0 ; i < n ; i ++ ){
		for (int j = 0 ; j < n ; j ++ )
			graph_matrix[i][j] = 0 ;   // graph matrix initialization 
	}
	Nodeptr graph_nodes[n];
	while(n > 0)
		graph_nodes[--n] = create(n); // since to the user vertices should start from 1 .. 
	n = temp ; 
	while(flag){ 
		switch(prompt()){
			case 1 :	cout<< " Enter the vertices on the edge - ";
						cin>>first ;
						cin>>second ; 
						graph_matrix[first - 1][second - 1] = 1 ; 
						graph_matrix[second - 1][first - 1] = 1 ; // Insert in the matrix 
						graph_nodes[second - 1] = insert(graph_nodes[second - 1],first);
						graph_nodes[first - 1] = insert(graph_nodes[first - 1],second);  // Insert in the list(s)
						break; 
			case 2 : display_matrix(graph_matrix,n); break;
						break; 
			case 3 : display_list(graph_nodes,n); break; 
			case 4 : flag = 0 ; break ; 
		}
	}
	return 0 ; 
}