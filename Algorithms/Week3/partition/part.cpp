// Program for partitioning a set into 2 disjoint sets, such that the sum of both these sets are equal.. 
#include<iostream>
#include<string.h>
#include<math.h>

using namespace std; 
void disp(int *a, int n) {
	cout<<" SET - " ; 
	for(int i = 0 ; i < n ; i++)
		cout<<a[i]<<" "; 
	cout<<endl ; 
}
int common ( int *a, int *b, int n1,int n2) {
	for(int i = 0 ; i < n1 ; i++) {
		for(int j = 0 ; j < n2 ; j++) {
			if(a[i]==b[j])
				return 1 ; 
		}
	}
	return 0 ; 
}
int main() {
	int N ; 
	cout<< " Enter the number of elements in the set :- "; 
	cin>>N ;
	int set[N] , sum = 0 ; 
	cout<<" Enter the element of the set :- " ; 
	for ( int i = 0 ; i < N ; i++ ){
		cin>>set[i] ; 					// Taking input 
		sum = sum + set[i] ; 
	}

	int power[(int)pow(2,N)][N+2] ; 	// two extra rows, for length and the sum 
	for ( int i = 0 ; i < pow(2,N); i++ ){
		for(int j = 0 ; j < N+2 ; j++) 
			power[i][j] = 0 ; 				// initializing to zero 
	}

	int ins_index = 0 ; 
	if ( sum%2 != 0) {
		cout<<" NOT POSSIBLE " ; 
		exit(0);  						// since sum = odd, then disjoint sets with equal sums not possible 
	}

	int index[20] ; // assuming maximum 10 solutions can exist
	for(int i=0 ; i<10 ; i++ )
		index[i] = 0 ;  		// Holding index for the sets that apply to the given case 

	for (int i = 0 ; i < pow(2,N) ; i++ ){
		int temp = i , iter = 0 , ins = 0 ; 
		while ( iter < N ){
			if (temp%2 == 1) 
				power[i][ins++] = set[iter] ; // no. of elements inserted stored in ins 
			temp = temp/2 ; 
			iter++ ; 						
		}
		power[i][N+1] = ins ; 
		for(int k=0 ; k < N ; k++) 
			power[i][N] = power[i][N] + power[i][k] ; 
		if(power[i][N] == sum/2 )
			index[ins_index++] = i ; 					
	}														// Power set created.. 

	for( int i =0 ; i < ins_index - 1 ; i++ ){
		for(int j = i+1 ; j < ins_index; j++){
			if( power[ index[i] ][N+1] + power[ index[j] ][N+1] == N){		// checking if union = whole set 
				if(common( power[index[i]],power[index[j]], power[index[i]][N+1],power[index[j]][N+1]) == 0) { 	// checks for no common element 
					cout<<endl; 
					disp(power[index[i]],power[index[i]][N+1]) ; 
					cout<< " AND "<<endl; 
					disp(power[index[j]],power[index[j]][N+1]) ; 
					cout<<endl; 
					break; 
				}
			}
		}
	}

	return 0 ; 
} 