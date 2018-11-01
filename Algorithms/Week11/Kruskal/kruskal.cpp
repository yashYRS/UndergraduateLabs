#include<iostream>
#include<stdlib.h>
using namespace std ; 

struct graph_edge {
	int first ; 
	int second ; 
	int weight ; 
} ; 

typedef struct graph_edge *edge ; // graph edges 

void sort( edge *list , int index) {
	edge temp = (edge)malloc(sizeof(struct graph_edge)) ; 
	for ( int i = 0 ; i < index - 1 ; i++ ) {
		for( int j = 0 ; j < index - i - 1 ; j++ )  {
			if ( list[j]->weight > list[j+1]->weight ) {
				temp = list[j] ; 
				list[j] = list[j+1] ; 
				list[j+1] = temp ; 
			}
		}
	}
	free(temp) ; 
}

int main() {

	int flag = 1 , f , s , w , n , index = 0 , counter = 0 , cost = 0 ;

	cout<<" Enter the number of vertices " ; cin>> n ; 
	edge *list = (edge*)malloc(sizeof(edge)*(n*(n-1))/2 ) ; 
	edge *span_tree = (edge*)malloc(sizeof(edge)*(n*(n-1))/2 ) ; 
	int *belongsTo =  (int*)malloc(sizeof(int)*(n*(n-1))/2) ; 
	
	while (flag) {
		cout<<" Enter edge " ; cin>>f ; cin>> s ; 
		cout<<" Enter the weight " ; cin>>w ; 
		list[index] = (edge) malloc(sizeof(struct graph_edge)) ; 
		list[index]->first = f ; list[index]->second = s ; 	list[index]->weight = w ; 
		cout<< " more edges - 1, else - 0 " ; cin>>flag ; 
		cout<<list[index]->first << " "<<list[index]->second<<" "<<list[index]->weight<<" inserted "<<endl ; 
		index++ ; 
	}	// input the edges 


	sort(list, index) ;  // sort the edges 

	for (int i = 0 ; i < n ; i++) 
		belongsTo[i] = i ; 		// initially there are n subsets 

	for( int i = 0 ; i < index ; i++) { // for all the edges, 	
		f = belongsTo[ list[i]->first - 1] ; 
		s = belongsTo[ list[i]->second - 1] ; 
		if ( f!= s ) {	
			span_tree[counter] = (edge)malloc(sizeof(struct graph_edge)) ; 
			span_tree[counter]->first = list[i]->first ; 
			span_tree[counter]->second = list[i]->second ; 
			span_tree[counter]->weight = list[i]->weight ; 
			counter++ ; 
			for (int k = 0 ; k < index ; k++ ) // union of two subsets, f and s both belong to f
				if ( belongsTo[k]==s )
					belongsTo[k] = f ; 
		}// if both have the same subset, either the edge has been processed OR it will create a cycle, any case avoid 
	}	

	for (int i = 0 ; i < counter ; i++ ) {
		cout<<span_tree[i]->first<<"->"<<span_tree[i]->second<<" : "<<span_tree[i]->weight<<endl ; 
		cost = cost + span_tree[i]->weight ; 
	}

	cout<<" Cost of the spanning tree "<<cost ; 
	return 0 ; 
}