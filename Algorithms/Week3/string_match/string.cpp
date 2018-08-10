// Program for  string matching using [ Brute Force ]
#include<iostream>
#include<stdlib.h>
#include<string.h>

using namespace std; 
void disp(char *a, int n) {
	for(int i = 0 ; i < n ; i++)
		cout<<a[i]; 
	cout<<endl ; 
}
void string_mat(char *str, char *pat) {
	int op = 0, *found , n = 0 ;
	found = (int *)malloc(sizeof(int)*10) ; // assuming not more than 10 matches can take place 
	cout<< " String is : "; 
	disp(str, strlen(str)) ; 
	cout<< " Pattern is : "; 
	disp(pat, strlen(pat)) ;
	for(int i = 0 ;i < strlen(str) - strlen(pat) + 1; i++){
		for(int j = 0 ; j< strlen(pat); j++) {
			op++ ; 
			if ( str[i+j]!= pat[j] )
				break;
			else if (j == strlen(pat) - 1)
				found[n++] = i ; 
		}
	} 
	cout<< " Number of matches and locations [ if any ]\t" << n ; 
	while ( n > 0 )
		cout<< " "<<found[--n]; 
	cout<<"\n No. of operations -- "<< op<<"\n\n"; 
}
int main() {
	char pat[20] , str[60] ; 
	cout<<" Enter string " ; 
	cin.get(str,60); 
	cout<< " Enter pattern " ; 
	cin>>pat; 
	string_mat(str, pat) ; 
	return 0 ; 
}