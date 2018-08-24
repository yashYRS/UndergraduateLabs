#include<iostream>

using namespace std; 
int *n  ;
void fn(int *n){
	n[0] = 12 ; 
	n[1] = 10 ; 
}
int main() {
	n = (int *) malloc(sizeof(int)*2) ; 
	n[1] = 2; 
	n[0] = 4 ; 
	for(int i = 0 ; i < 2 ; i++) 
	cout<< " " << n[i] ; 
	fn(n) ; 
	for(int i = 0 ; i < 2 ; i++) 
		cout<< " " << n[i] ; 
}