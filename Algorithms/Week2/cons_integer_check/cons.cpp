// Finding the GCD of 2 numbers using Consecutive Integer checking method 

#include<iostream>

using namespace std; 

int min( unsigned int m, unsigned int n ) {
	if ( m > n )
		return n; 
	else 
		return m ; 
}

int main() {
	unsigned int m, n , minm, result, opcount ; 
	cout<< " Enter No.s - " ; 
	cin>> m; cin >> n; 
	minm = min(m, n) ; 
	opcount = minm ; 
	while ( minm > 0 ) {
		if( m % minm == 0 && n % minm == 0 ) {
			result = minm ; 
			break; 
		}
		minm -- ; 
	}
	cout<< " NO. of operations - "<< opcount - minm << endl ; 
	cout<< " GCD - "<<result; 
	return 0 ; 
}
