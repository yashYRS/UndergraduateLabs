#include<iostream>
#include<stdlib.h>
using namespace std ;

struct Node {
	int data; 
	Node* left;
	Node* right ; 
};

typedef struct Node* Tree_ptr ; 

Tree_ptr new_node(int d) {
	
	Tree_ptr temp  = (Tree_ptr) malloc( sizeof(struct Node) ) ; 
	temp->data = d ; 
	temp->right = NULL ; 
	temp->left = NULL ; 
	return temp ; 

}

void display_in(Tree_ptr root){
	if (!root)
		return ; 
	display_in(root->left);
	cout<<root->data<<" " ; 
	display_in(root->right);
}
void display_post(Tree_ptr root){
	if ( !root )
		return ; 
	display_post(root->left);
	display_post(root->right);
	cout<<root->data<<" " ;
}
void display_pre(Tree_ptr root){
	if ( !root )
		return ; 
	cout<<root->data<< " ";
	display_pre(root->left);
	display_pre(root->right);
}

int search(Tree_ptr root , int key ) {
	if (!root)
		return 0; 
	if ( key < root->data )
		search(root->left,key);
	else if ( key > root->data )
		search(root->right, key );
	else if ( key == root->data )
		return 1 ; 
}

Tree_ptr insert(Tree_ptr root , int key ){
	
	Tree_ptr temp = root ; 
	Tree_ptr node_add = new_node(key);
	if (!temp)
		return node_add ; 
	while(temp){
		if ( key < temp->data ) {
			if ( temp->left )
				temp = temp->left ; 
			else {
				temp->left = node_add; 
				return root ; 
			}
		}
		else if ( key > temp->data ){
			if (temp->right) 
				temp = temp->right; 
			else {
				temp->right = node_add; 
				return root ; 
			}
		}
	}

}

int total_nodes(Tree_ptr root,int *op) {
	*op = *op + 1 ; 
	if(!root)
		return 0; // root == NULL then return 
	return total_nodes(root->right,op) + total_nodes(root->left,op) + 1;
}

int prompt() {
	cout<<" \n\n\n Choose one - \n";
	cout<<" 1. Insert  \n";
	cout<<" 2. Search  \n";
	cout<<" 3. Pre-Order \n";
	cout<<" 4. Post-Order \n";
	cout<<" 5. In-Order \n";
	cout<<" 6. Total Nodes \n";
	cout<<" 7. Exit  \n\n\n";
	int a; cin >> a ; return a ; 
}


int main() {
	Tree_ptr root = NULL ; 
	int var,flag = 1; 
	while(flag){
		int opcount = 0 ;
		switch(prompt()){
			case 1 : cout<< " Enter number to be inserted "; cin>>var;
					 root = insert(root,var); 
					 break ; 
			case 2 : cout<<" Enter number to be searched "; cin>>var; 
						if(search(root,var)) 
							cout<<" FOUND ";
						else {
							root = insert(root,var);
							cout<< " NOT FOUND, hence value inserted ";
						}
					break; 
			case 3 : cout<< " PRE-ORDER : "  ; display_pre(root) ; break; 
			case 4 : cout<< " POST-ORDER : "  ;display_post(root) ; break; 
			case 5 : cout<< " IN-ORDER : "  ;display_in(root) ; break; 
			case 6 : cout<<" Total Nodes : "<<total_nodes(root,&opcount)<<endl; 
					cout<<" Steps taken - "<<opcount; break ; 
			case 7 : flag  =0 ; break ; 
		}
	}
	return 0 ; 
}