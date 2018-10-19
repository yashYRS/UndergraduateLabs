#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
using namespace std;

int* create_shift ( char *pat, int m ) {
        int* shift = (int*) malloc(sizeof(int)*128) ;
        for(int i = 0 ; i < 128 ; i++) 
                shift[i] = m ;
        for(int i = 0 ; i < m-1 ; i++ ) 
                shift[ (int)pat[i] ] = m - 1 - i ; 
        return shift ;
}
void horspool( char *text, char *pat, int *shift, int n , int m) {
        int jump ;  // i has the point where the strings are aligned 
	for ( int i = 0 ; i < n - m +1 ; i = i + jump ) {
       		jump = 1 ; 
	         for (int j = m - 1 ; j >= 0 ; j--) {
                        if( text[i + j] != pat[j] ) {
                                jump = shift[ (int) text[i+j] ] ; 
                                break ;
                        }
                        if ( j == 0 )  {
                                cout<<" Match found at "<<i<<" th index" ; 
                                return ;
                        }
                }
	}        
	cout<<" No match found ";
}



int main() {

        char *pat , *text ;
        int *shift ;
        int m, n ;
        pat = (char*)malloc(sizeof(char)*20) ;
        text = (char*)malloc(sizeof(char)*100) ;
        cout<<" Enter the text -> " ; cin.get(text,100) ; cin.get() ; 
        cout<<" Enter the pattern -> " ; cin.get(pat,20); cin.get() ;  
        shift = create_shift(pat,strlen(pat)) ;
        horspool(text, pat, shift, strlen(text) , strlen(pat) ) ;
        return 0 ;
}
