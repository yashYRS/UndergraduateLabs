#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std ; 


void disp(int* tree, int nodes) {
	for(int i = 0 ; i < nodes ; i++) 
		cout<<" "<<tree[i] ; 
	cout<<endl ; 
}
int prompt() {
	cout<<" \n\n\n Choose one - \n";
	cout<<" 1. Insert  \n" ; 
	cout<<" 2. Sort \n" ; 
	cout<<" 3. Exit  \n\n\n";
	int a; cin >> a ; return a ; 
}

int check(int *tree, int n, int key) {
	for(int i=0 ; i < n ; i++)
		if (key == tree[i]) 
			return 1 ; 
	return 0 ; 
}

int getmax(int* tree, int i ){ 
	if (tree[2*i + 2] > tree[2*i + 1]) // right child >  left
		return 2*i+2 ;
	return 2*i + 1; // index of the greater child 
}

int* heapify(int *tree, int nodes, int *opcount) {
	int temp, child, par ; 
	int parent = nodes/2 - 1; // last parent.. 
	for(int i = parent ; i >= 0 ; i--) {		// do it from the last parent to the root ... 
		par = i ; child = getmax(tree,par) ; 
		while(tree[child] > tree[par]) {
			temp = tree[child] ; 
			tree[child] = tree[par] ; 
			tree[par] = temp ; 
			par = child ; 
			child = getmax(tree,par) ; 
			(*opcount)++ ; 
		}	// correct till the end .. 
	}
	return tree ; 

}

int main() {

	int* tree = (int*)calloc(50,sizeof(int)) ; 
	int* sorted = (int*)calloc(50,sizeof(int)) ;
	int var , nodes = 0 , temp , opcount = 0 ; 
	while(1){
		switch(prompt()){
			case 1 : cout<< " Enter number to be inserted "; cin>>var;
					if(!check(tree,nodes,var))		// check whether already present
					 	tree[nodes++] = var ; 
					else 
						cout<<" Already present" ; 
					 break ; 
			case 2 : 
					for(int i = 0 ; i < nodes ; i++) {
						tree = heapify(tree,nodes - i,&opcount) ;
						temp = tree[0] ; 
						tree[0] = tree[nodes -1 - i] ; 
						tree[nodes -1 - i] = 0; 
						sorted[nodes - i - 1] = temp ; 
					}
					disp(sorted,nodes) ; 
					cout<<"\nThe operations ->  "<<opcount ; 
					break ; 
			case 3 : exit(0)  ; 
		}
	}
	return 0 ; 
}