#include<iostream>
#include<stdlib.h>
using namespace std ; 


int get_min (int *dist , int n , int *vertices ) {
	int ind, min = 100000;
	for (int i = 0 ; i < n ; i++ ) {
		if ( min > dist[i] && vertices[i] == 0 ) {
			min = dist[i] ; 
			ind = i ; 
		}
	}
	return ind ; 
}

int ret_min (int a , int b ) {
	if ( a < b ) 
		return a ; 
	return b ; 
}

int main() {
	int num,next,source ; 
	cout<<" Enter the number of vertices " ; cin>> num ;
	
	int *graph = (int*)malloc(sizeof(int)*num*num) ;  // adjacency matrix
	int* dist_vector = (int*)malloc(sizeof(int)*num) ; 
	int* vertices = (int*)calloc(num, sizeof(int)) ; 
	
	cout<< "Enter source [index starts from 0]-> " ; cin>>source ;  
	vertices[source] = 1 ; // initially only source added, 

	cout<<" Enter the adjacency matrix (Enter large value, if not reachable )" ; 
	for (int i = 0 ; i < num ; i++)  {
		cout<<"\n Row " <<i+1<< " - "; 
		for(int j = 0 ; j < num ; j++) {
			cin>>graph[ i*num+ j ] ; 
			if (i == source ) 
				dist_vector[j] = graph[i*num + j] ; // initial distance vector 
		}
	}	// input phase 

	for (int done = 1 ; done < num ; done++) { 	// till all the vertices haven't been added, 
		next = get_min(dist_vector, num , vertices ) ; // get the next minimum distance 
		vertices[next] = 1 ; // add it to the vertices list 
		for (int i = 0 ; i < num ; i++ ) {
			if (graph[next*num + i] > 0 ) 
				dist_vector [i] = ret_min( dist_vector[i] , dist_vector[next] + graph[next*num + i] ) ; // update 
		}
	}
		
	cout<<"\n The distance vector -> " ; 
	for (int i = 0 ; i < num ; i++ ) 
		cout<<" "<<dist_vector[i] ; 	// display 
	return 0 ; 
}