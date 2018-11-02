// -- Branch and bound approach for the problem -- // 
#include<iostream>
#include<stdlib.h>

using namespace std; 

int num_elements , maximum ; 
float curr_ub , final_profit = 0 ;
float *weights = (float*) malloc(sizeof(float)*num_elements) ; 
float *profits = (float*) malloc(sizeof(float)*num_elements) ;
float *unit =  (float*) malloc(sizeof(float)*num_elements) ;
int *final = (int*) malloc(sizeof(int)*num_elements) ; 
int *chosen = (int*) malloc(sizeof(int)*num_elements) ; 

void copy(int *a , int *b , int n ) {
    for (int i = 0 ; i < n ; i++ ) 
        a[i] = b[i] ; 
}

void sort () { // based on highest profit per unit 
    float temp1 , temp; float temp2 ; 
    for (int i = 0 ; i < num_elements ; i++ )
        unit[i] = (float) profits[i] / (float) weights[i] ; 
    for (int i = 0 ; i < num_elements ; i++ ) {
        for (int j = i+1 ; j < num_elements ; j++ )
            if ( unit[i] < unit[j] ) {
                temp2 = unit[i] ; temp = weights[i] ; temp1 = profits[i] ; 
                unit[i] = unit[j] ; weights[i] = weights[j] ; profits[i] = profits[j] ;
                unit[j] = temp2 ; weights[j] = temp ; profits[j] = temp1 ; 
            }
    }
}

float bound ( float curr_wt , float curr_profit , int elements ) {
    return curr_profit + (maximum - curr_wt)*( profits[elements]/weights[elements] ) ; 
}

void knapsack (float curr_wt , float curr_profit , int elements ) {
    curr_ub = bound(curr_wt , curr_profit , elements+1) ;

    // the branch with the element chosen 
    if ( elements <= num_elements && (curr_wt + weights[elements]) <= maximum  && curr_ub > final_profit) {  // weight allowed
        chosen[elements] = 1 ; 
        knapsack(curr_wt + weights[elements], curr_profit + profits[elements] , elements + 1 ) ;  
    }   
    if ( curr_profit > final_profit ) {
            final_profit = curr_profit ;
            copy(final , chosen , num_elements ) ; // update the selected list 
    }
    // the branch with the element not chosen 
    if ( elements <= num_elements && curr_ub > final_profit) {     
        chosen[elements] = 0 ; 
        knapsack(curr_wt, curr_profit, elements + 1 ) ;  
    }
    if ( curr_profit > final_profit ) {
            final_profit = curr_profit ; 
            copy(final , chosen , num_elements ) ; // update the selected list 
    }
}
 
int main() {
    float current_weight = 0 , current_profit = 0 , sum = 0 ; 
    int elements = 0 ; 

    cout<<"Total Capacity ? " ; cin>> maximum ; 
    cout<<" Enter the number of elements in contention " ;  cin>> num_elements  ;  

    cout<<" Now enter the weights of each " ; 
    for(int i = 0 ; i < num_elements ; i++ ) 
        cin>>weights[i] ; 

    cout<<" Now enter the profits of each " ; 
    for(int i = 0 ; i < num_elements ; i++ ) 
        cin>>profits[i] ; 

    sort() ; 
    knapsack(current_weight , current_profit , elements ) ; 
    cout<<" Selected items -> " ; 
    for (int i=0 ; i < num_elements ; i++ ) {
        cout<<" weight : "<<weights[i]<<" selected :  "<<final[i]<<endl  ; 
    }
    cout<<"\n The profit earned "<<final_profit ; 

    return 0 ; 
}