#include<iostream>
#include<stdlib.h>
using namespace std ;

struct treenode {
	int data; 
	treenode *left ; 
	treenode *right ; 
};
typedef struct treenode* treeptr ; 

int prompt (){
	cout<<"\n Choose one of the following - "<<endl;
	cout<<" 1. Insert an element"<<endl;
	cout<<" 2. In order"<<endl;
	cout<<" 3. Diameter of the tree - "<<endl ; 
	cout<<" 4. Exit"<<endl; 
	int a ; 
	cin>> a; 
	return a ; 
}

int max(int a, int b) {
	if ( a > b ) 
		return a ; 
	else 
		return b ; 
}

int height(treeptr root) {
	if(!root) 
		return 0 ; 
	else 
		return max(height(root->left),height(root->right)) + 1; 
}

int diameter (treeptr root) {
	if(!root) 
		return 0 ; 
	int left_h = height(root->left) ;
	int right_h = height(root->right) ; 

	int left_d = diameter(root->left) ; 
	int right_d = diameter(root->right) ; 

	return max(left_h+right_h + 1 ,max(left_d,left_d))  ; 
}

treeptr create(int d){
	treeptr temp = (treeptr) malloc(sizeof(struct treenode));
	temp->data = d ;
	temp->right = NULL ; 
	temp->left = NULL ; 
	return temp ; 
}
treeptr insert(treeptr root,int sk){
	treeptr temp = root ; 
	if(!root){
		cout<< " Inserted "<< sk<<endl; 		
		return create(sk);
	}
	while( temp ){
		if(sk < temp->data && temp->left)
			temp = temp->left ; 
		else if (sk < temp->data){
			temp->left = create(sk);
			cout<< " Inserted "<< sk<<endl; 
			return root ; 
		}
		if ( sk > temp->data && temp->right)
			temp = temp->right ;
		else if ( sk > temp->data){
			temp->right = create(sk);
			cout<< " Inserted "<< sk<<endl; 			
			return root ;
		}
		else if ( sk == temp->data){
			cout<< " Already Present "; 
			return root ; 
		}
	}
}

void in(treeptr root){
	if (!root)
		return ; 
	in(root->left);
	cout<< " "<< root->data ;
	in(root->right); 
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
			case 2 : in(root);break; 
			case 3 : cout<<" The diameter of the tree -> "<<diameter(root); break; 
			case 4 : flag = 0 ; break ; 
		}
	}
	return 0 ; 
}