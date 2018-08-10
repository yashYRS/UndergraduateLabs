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
	cout<<" 2. Search for something"<<endl;
	cout<<" 3. Pre order"<<endl;
	cout<<" 4. Post order"<<endl;
	cout<<" 5. In order"<<endl;
	cout<<" 6. Exit"<<endl; 
	int a ; 
	cin>> a; 
	return a ; 
}


treeptr create(int d){
	treeptr temp = (treeptr) malloc(sizeof(struct treenode));
	temp->data = d ;
	temp->right = NULL ; 
	temp->left = NULL ; 
	return temp ; 
}
treeptr search(treeptr root,int sk){
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
			cout<< " Key found "; 
			return root ; 
		}
	}
}
void pre(treeptr root) {
	if (!root)
		return ; 
	cout<< " "<< root->data ;
	pre(root->left);
	pre(root->right); 
}
void post(treeptr root){
	if (!root)
		return ; 
	pre(root->left);
	pre(root->right); 
	cout<< " "<< root->data ;	
}
void in(treeptr root){
	if (!root)
		return ; 
	pre(root->left);
	cout<< " "<< root->data ;
	pre(root->right); 
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
						root = search(root,var);
						break; 
			case 2 : cout<<" Enter number to be searched "<<endl;
						cin>>var ;
						root = search(root,var);
						break; 
			case 3 : pre(root);break; 
			case 4 : post(root);break; 
			case 5 : in(root);break; 
			case 6 : flag = 0 ; break ; 
		}
	}
	return 0 ; 
}