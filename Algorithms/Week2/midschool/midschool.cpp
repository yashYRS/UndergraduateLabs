// Finding the GCD of 2 numbers using Middle School method 

#include<iostream>

using namespace std; 

int min( unsigned int m, unsigned int n ) {
	if ( m > n )
		return n; 
	else 
		return m ; 
}

int main() {
	unsigned int m, n, opcount = 0,result = 1 ;
	cout<< " Enter nos. "; 
	cin>>m ; cin>> n; 
	for( int i =2 ;i <= min(m,n); i++) {
		opcount++ ; 
		if( m%i==0 && n%i==0 ) {
			m = m/i; n = n/i ; 
			result = result*i ; 
			i-- ; 
		}
	}
	cout<< " NO. of operations - "<< opcount<< endl ; 
	cout<< " GCD "<< result ; 
	return 0 ; 
}
