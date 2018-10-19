#include<iostream>
#include<stdlib.h>

using namespace std;

struct number_list {
	int number  ; 
	number_list* next ; 
} ; 

typedef struct number_list *list; 

struct bucket {
	list store; 
};

typedef struct bucket *table ; 

list initialize(int num ) {
	list new_node = (list)malloc(sizeof(struct number_list)) ; 
	new_node->next = NULL ; 
	new_node->number = num ; 
	return new_node ; 
}

list insert(int num, list head) {
	list temp = head ;
	list new_node = initialize(num) ; 
	if(!temp) 
		return new_node ; 
	while(temp->next) 
		temp = temp->next ; 

	temp->next = new_node ; 
	return head; 
}

int search (int num , list head, int *success , int *fail ) {
	int comparisons = 0 ; 
	do {
		comparisons++ ; 
		if (head->number == num) {
			*success = *success + comparisons ;
			return 1 ; 
		}
		head = head->next ; 
	} while(head->next) ; 
	*fail = *fail + comparisons ; 
	return 0 ; 
}

void print(list temp ) {
	while(temp->next) {
		cout<<" "<<temp->number ;  
		temp = temp->next ;  
	}
	cout<<" "<<temp->number ; 
}

int main() {
	table t[10] ; // h(x) == x%10
	int num_search,num_enter,index,success,fail,s_cases,u_cases ,iterations = 10  ; 
	for ( int i = 0 ; i < 10 ; i++ )
		t[i] = (table) malloc(sizeof(struct bucket)) ; 


	for (int i = 0 ; i < 100 ; i++)  {
		num_enter = rand()%100 ; // create a random number 
		index = num_enter%10  ; // the hashing function 
		//cout<<n<< " " ; 
		t[index]->store = insert(num_enter, t[index]->store ) ; 
	}
	cout<< " The HASH tabel is as follows "<<endl ; 
	for(int i = 0 ; i < 10 ; i++ ) {
		print(t[i]->store) ; 
		cout<<endl ; 
	}

	for(int i = 0 ; i < 5 ; i++ ) {
		s_cases = 0 ; u_cases = 0 ; success = 0 ; fail = 0 ; 
		for(int j = 0 ; j < iterations ; j++ ) {
			num_search = rand()%100 ;  
			index = num_search%10 ; 
			if ( search(num_search , t[index]->store , &success , & fail) == 1 )
				s_cases++ ; 
			else 
				u_cases++ ; 
		}
		cout<<" Comparisons : 1. Success -> "<< success/s_cases <<" 2. Failure -> "<< fail/u_cases<<endl ; 
		iterations = iterations + 5 ; 
	}
	return 0 ; 
}
