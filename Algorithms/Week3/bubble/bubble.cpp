// Program to sort using bubble sort method, uses 5 best cases and 5 worst cases to analyze efficiency 
#include<iostream>
#include<stdlib.h>

using namespace std; 
void disp(int *a, int n) {
	cout<< "Array - \t";
	for(int i = 0 ; i < n ; i++)
		cout<<a[i]<<" "; 
	cout<<endl ; 
}

void bubble(int *a, int n) {
	int temp, op1 = 0, op2 = 0 , flag; 
	disp(a,n); 
	for(int i = 0 ; i < n -1 ; i++) {
		flag =1  ;
		for(int j = 0 ; j < n - i +1 ; j++) {
			op1++; 		// op1 keeps count of no. of comparisons 
			if ( a[j] > a[j+1]) {
				temp  = a[j]; 
				a[j] = a[j+1];
				a[j+1] = temp; 
				op2++; 
				flag = 0; 
			}
		}
		if(flag)
			break; 	// No swaps made, so list sorted.. 
	}
	cout<< " 1. Operations - "<< op1 <<"  2. Swaps - "<< op2<<endl;
	cout<<"AFTER SORTING ";
	disp(a,n);
}

int main() {
	int b[20], w[20] ; // b - best case and w - worst case 
	int n = 5; 
	for ( int i = 0 ; i < 20 ; i++) {
		b[i] = i+1 ; w[i] = 20 - i; // best case : already sorted, worst case : reverse order
	}
	for ( int i = 1 ; i < 5 ; i++) {
		cout<< "\n \n Cases with "<< n*i <<" elements "<<endl ; 
		cout<< " 1. BEST "<<endl;
		bubble(b,n*i);  
		cout<< " 2. WORST "<<endl; 
		bubble(w,n*i);
	}
	return 0 ; 
}