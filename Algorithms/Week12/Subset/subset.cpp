// -- Branch and bound approach for the problem -- // 
#include<iostream>
#include<stdlib.h>

using namespace std; 

int num_elements , maximum , num_results = 0; 
float *numbers = (float*) malloc(sizeof(float)*num_elements) ; 
int *chosen = (int*) malloc(sizeof(int)*num_elements) ; 
int *results = (int*) calloc (num_elements*10 , sizeof(int)) ; 

void print() {
    cout<<" Selected items -> " ; 
    for (int i=0 ; i < num_elements ; i++ )
        if ( chosen[i] == 1 ) 
            cout<<" "<<numbers[i] ; 
    cout<<endl ; 
}

int present () {
    int check ; 
    for (int i = 0 ; i < num_results ; i++ ) {
        check = 0 ; 
        for (int j = 0 ; j < num_elements ; j++)
            if ( chosen[j] ==  results[i*num_elements + j] )
                check++ ; 
        if (check == num_elements) 
            return 1 ; 
    }
    return 0 ; 
}
int add () {
    for (int i = 0 ; i < num_elements ; i++ )
        results[ num_results*num_elements + i ] = chosen[i] ; 
    num_results++ ; 
}

void subset (float curr_val, int elements ) {

    if ( elements <= num_elements && (curr_val + numbers[elements]) <= maximum) {  // weight allowed
        chosen[elements] = 1 ; 
        subset(curr_val + numbers[elements] , elements + 1 ) ;  
    }    // the branch with the element chosen 
    if ( curr_val ==  maximum && present() == 0) { 
            print() ; 
            add() ;
            return ; 
    }

    if ( elements <= num_elements ) {     
        chosen[elements] = 0 ; 
        subset(curr_val, elements + 1 ) ;  
    }   // the branch with the element not chosen 
    if ( curr_val == maximum && present() == 0 ) {
        print() ; 
        add() ; 
        return ; 
    }
}
 
int main() {
    float  curr_val = 0  ; 
    int elements = 0 ; 

    cout<<" Enter value needed ? " ; cin>> maximum ; 
    cout<<" Enter the number of elements in the set " ;  cin>> num_elements  ;  

    cout<<" Now enter the weights of each " ; 
    for(int i = 0 ; i < num_elements ; i++ ) 
        cin>>numbers[i] ; 
    subset( curr_val , elements ) ; 
    return 0 ; 
}