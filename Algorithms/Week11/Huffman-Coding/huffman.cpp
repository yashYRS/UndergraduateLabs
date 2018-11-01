#include<iostream>
#include<stdlib.h>

using namespace std; 

struct tree_node {
	float freq_val ;
	int is_leaf ; 
	char symbol ; 
	struct tree_node *right ; 
	struct tree_node *left ; 
} ; 

typedef struct tree_node *tree ; 

int findmin (tree *leaves , int *marked , int *index ) {
	float min = 10000.0 ; 
	int min_index ; 
	for (int i = 0 ; i < *index ; i++) {
		if ( min > leaves[i]->freq_val && marked[i] == 0 ) {
			min = leaves[i]->freq_val ; 
			min_index = i ; 
		}
	}
	return min_index ; 
}


void one_iteration ( tree *leaves , int *marked, int *index ) {
	
	int node1_index , node2_index ; 
	tree new_node ;  							// temp variables needed 

	node1_index = findmin (leaves , marked , index ) ;  
	marked[node1_index] = 1 ; 
	node2_index = findmin (leaves , marked , index ) ; 
	marked[node2_index] = 1 ; 	
	(*index)++ ; 											// find 2 minimum valued nodes 


	leaves[*index - 1]->freq_val = leaves[node2_index]->freq_val + leaves[node1_index]->freq_val ; 
	leaves[*index - 1]->right = leaves[node2_index] ; 
	leaves[*index - 1]->left = leaves[node1_index] ; 				// add the new node 
	
}


tree initialize (float val , char c, int leaf) {
	tree new_tree = (tree) malloc( sizeof(struct tree_node ) ) ; 
	if (leaf == 1) {
		new_tree->right = NULL ; 
		new_tree->left = NULL ; 
		new_tree->is_leaf = 1 ; 
		new_tree->symbol = c ; 
	}
	else 
		new_tree->is_leaf = 0 ; 
	new_tree->freq_val = val ; 
	return new_tree ; 
}		

void traverse(tree root, char *code , int len ) {
	if (root->is_leaf == 1)  {
		for(int i = 0 ; i <= len ; i++)
			cout<<code[i] ; 
		cout<<" "<<root->symbol<<endl ; 
		return ; 
	}
	if (root->left) {
		code[len] = '0' ; 
		traverse(root->left, code ,len + 1) ; 
	}
	if (root->right) {
		code[len] = '1' ; 
		traverse(root->right, code ,len + 1 ) ; 		
	}
}

int main() {
	int n , i , done ; 
	char *code ; 
	cout<<" Enter number of unique symbols " ; cin>> n ; 
	float *frequency = (float*) malloc(sizeof(float)*n ) ; 
	char *symbols = (char*) malloc(sizeof(char)*n ) ; 
	int *marked = (int*)calloc( n*(n+1)/2 , sizeof(int) ) ; 
	tree *leaves = (tree*) malloc( sizeof(tree) * ( ( n*(n+1) )/2 ) )  ; 
	tree root , temp ; 
	for(int i = 0 ; i < n ; i++ ) {
		cout<<"\n Enter the symbol " ; cin>>symbols[i] ; 
		cout<<"\n Enter the frequency " ; cin>>frequency[i] ; 
		leaves[i] = initialize ( frequency[i] , symbols[i] , 1 ) ;  // all leaves initially 
	}
	i = n ; 
	while (1) {
		done = 0 ; 
		leaves[i] = initialize ( 0 , 'a' , 0 ) ;  // add a new node 
		one_iteration( leaves , marked , &i) ; 
		for (int k = 0 ; k < i ; k++ ) {
			if (marked[k] == 1 )
				done++ ; 
		}
		if (done == i - 1 ) {
			root = leaves[i-1] ; 
			break ; 
		}
	}  
	code = (char*)malloc(sizeof(char)*n) ;
	cout<<"\n\n The codes are -> "<<endl ; 
	traverse (root, code , 0) ; 
	return 1; 
}
 