#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std ; 


int prompt() {
	cout<<" \n\n\n Choose one - \n";
	cout<<" 1. Insert  \n" ; 
	cout<<" 2. Display \n" ; 
	cout<<" 3. Exit  \n\n\n";
	int a; cin >> a ; return a ; 
}

int check(int *tree, int n, int key) {
	for(int i=0 ; i < n ; i++)
		if (key == tree[i]) 
			return 1 ; 
	return 0 ; 
}

int* heapify(int *tree, int nodes, int *opcount) {
	int temp ; 
	while(tree[nodes] > tree[nodes/2]) {
		temp = tree[nodes/2] ;  
		tree[nodes/2] = tree[nodes] ; 
		tree[nodes] = temp ; 
		nodes = nodes / 2  ; 
		(*opcount)++ ; 
	}
	return tree ; 

}

int main() {

	int tree[100] ;  // say maximum capacity of a tree can be 100 ; 
	int var , nodes = 0 , level , opcount = 0 ; 
	while(1){
		switch(prompt()){
			case 1 : cout<< " Enter number to be inserted "; cin>>var;
					if(!check(tree,nodes,var)) {		// check whether already present
					 	tree[nodes] = var ; 
					 	heapify(tree,nodes++,&opcount) ; 
					}
					else 
						cout<<" Already present" ; 
					 break ; 
			case 2 : cout<< " level wise : " ; 
					level = 0 ; 
					for(int i = 0 ; i < nodes ; i++) {
						if (i+1 == pow(2,level)) {
							cout<<endl ; 
							level++ ; 
						}
						cout<< tree[i] <<"\t" ; 
					}
					cout<<" The operations ->  "<<opcount ; 
					break ; 
			case 3 : exit(0)  ; 
		}
	}
	return 0 ; 
}