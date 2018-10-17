#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std; 


int main(){
	int p , n , logical , address_len ;
	cout<<" Enter the size of the page -> " ; cin>> p ; 
	cout<<" Enter number of pages -> " ; cin>>n; 
	cout<<" Therefore the total memory is -> "<<n*p<<endl ; 
	cout<<" Number of bits reqd for representing -> "<< (int) ( log(n*p)/log(2) ) + 1 <<endl; 
	cout<<" Enter a logical address to read -> ";  cin>>logical ; 
	cout<<"\n Page number -> "<<logical/p ; 
	cout<<"\n Offset -> "<<logical%p ; 
}