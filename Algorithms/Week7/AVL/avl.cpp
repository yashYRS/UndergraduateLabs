#include<iostream>
#include<stdlib.h>
using namespace std ;

struct treenode {
	int data; 
	int bal ; 
	treenode *left ; 
	treenode *right ; 
};
typedef struct treenode* treeptr ; 

int prompt (){
	cout<<"\n Choose one of the following - "<<endl;
	cout<<" 1. Insert an element"<<endl;
	cout<<" 2. Pre order"<<endl;
	cout<<" 3. Show - bal"<<endl ; 
	cout<<" 4. Exit"<<endl; 
	int a ; cin>> a; return a ; 
}

int height(treeptr root) {
	if(!root)
		return 0 ; 
	return max(height(root->right),height(root->left)) + 1 ; 
}

void pre(treeptr root,int b) {
	if (!root)
		return ; 
	if (b == 0){
		root->bal = height(root->right) - height(root->left) ; 
		cout<< " "<< root->bal ;
	}
	else 
		cout<< " "<< root->data ;
	pre(root->left,b);
	pre(root->right,b); 
}

int max(int a, int b) {
	if(a > b) 
		return a; 
	return b ; 
}

treeptr left(treeptr root){
	treeptr temp1 = root->left; 
    treeptr temp2 = temp1->right; 
    temp1->right = root;     // Perform rotation 
	root->left = temp2; 
	return temp1 ; 
}

treeptr right(treeptr root) {
	treeptr temp1 = root->right; 
	treeptr temp2 = temp1->left; 
	temp1->left = root;     // Perform rotation 
	root->right = temp2; 
	return temp1 ; 
}


treeptr create(int d){
	treeptr temp = (treeptr) malloc(sizeof(struct treenode));
	temp->data = d ;
	temp->right = NULL ; 
	temp->left = NULL ; 
	return temp ; 
}

treeptr insert(treeptr temp,int sk){ 
	if(!temp)
		return create(sk);
	if(sk < temp->data )
		temp->left = insert(temp->left,sk) ; 
	if ( sk > temp->data)		
		temp->right = insert(temp->right,sk);		// insertion over 
	temp->bal = height(temp->right) - height(temp->left) ; // get the balance in every node 
	if(temp->bal > 1 ) {
		if(sk > temp->right->data)
			return right(temp) ; 		// right case 
		temp->right = right(temp)  ; 		// right-left case 
		return left(temp) ; 			
	} 
	else if (temp->bal < -1) {
		if (sk < temp->left->data)	
			return left(temp) ; 			// left case 
		temp->left = left(temp) ; 	
		return right(temp) ; 			//left-right case 
	}
	return temp;	// if no correction required ...
}


int main() {
	treeptr root = NULL ;
	int flag = 1 ; 
	int retvar,var ; 
	while(flag){
		retvar = prompt() ; 
		switch(retvar){

			case 1 :	cout<<" Enter number to be inserted "<<endl;
						cin>>var ;
						root = insert(root,var);
						break; 
			case 2 : pre(root,1);break; 
			case 3 : pre(root,0) ; break ; 
			case 4 : flag = 0 ; break ; 
		}
	}
	return 0 ; 
}