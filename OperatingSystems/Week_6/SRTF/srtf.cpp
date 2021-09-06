#include<iostream>
#include<stdlib.h>

using namespace std; 

struct process{
	int pid ; 
	int time_remaining ;
	int arrival_time ; 
	int burst_time; 
};
typedef process* p_ptr ; 
struct  chart {
	int name ; 
	int start; 
};
p_ptr set_Values(int at, int bt ,int id) {
	p_ptr temp = (p_ptr)malloc(sizeof(int)*4) ; 
	temp->time_remaining = bt ; 
	temp->arrival_time = at ;
	temp->burst_time = bt ; 
	temp->pid = id ; 
	return temp;  
}

p_ptr take_input(int clock,int id) {
	int bt; 
	cout<<"\n burst_time? -> ";
	cin>>bt; 
	p_ptr new_process = set_Values(clock,bt,id); 
	return new_process ; 
}
int prompt(int clock) {
	// write down the options 
	cout<<"################     MENU           ###############";
	cout<<"\n\n \t\t Time -> "<<clock<<"\n" ; 
	cout<<"\n 1. Enter process " ;
	cout<<"\n 2. Execute  " ; 
	cout<<"\n 3. No more processes, Make Gannt Chart, Exit. ";  
	cout<<"\n\t Enter your choice-> ";
	int i ; cin>>i; 
	cout<<"################     MENU Ends      ###############";
	return i ; 
}

p_ptr* enqueue(p_ptr* plist, int *n,int clock,int id) {
	p_ptr temp = take_input(clock,id) ;
	plist[*n] = temp ; 			// temp added at the end of the queue... 
	*n = *n + 1; 
	return plist ; 				

}

p_ptr* dequeue(p_ptr* plist,int* n) {
	*n = *n - 1; 
	return &(plist[1]) ; // remove the first element 
	//n -> no of processes present.... 
}

p_ptr* find_min(p_ptr* l , int n) {
	int min = 100 ; 
	int index = 0 ; 
	for(int i = 0 ; i < n ; i++) {
		if(min >= l[i]->time_remaining){
			min = l[i]->time_remaining ; 
			index = i ; 
		}
	}
	p_ptr temp = l[index] ; 
	for(int i = index ; i > 0 ; i--) 
		l[i] = l[i-1] ;	// shift elements to the right
	l[0] = temp ; 
	return l ; 
}

int main(){
	p_ptr* queue = (p_ptr*)malloc(sizeof(p_ptr)*30); // plist stores all the processes
	int num = 0 ; // number of processes in the array 
	int clock = 0 ;
	chart gc[100] ; // stores entries for the gannt chart 
	int next = 0 ;int id = 1 ; /* ENTER ID OF EACH PROCESS */ 
	float ave_waiting = 0, ave_turn = 0  ; 
	p_ptr temp = NULL ; 
	while(1) {
		switch(prompt(clock)) {
			case 1 :	queue = enqueue(queue,&num,clock,id++) ;
						queue = find_min(queue,num) ;
						break ;  
			case 2 : 	clock++ ;
						if (num > 0 ) {
							if (queue[0]!= temp){		// that implies there has been a change so add to the gannt chart 
								gc[next].name = queue[0]->pid ; 
								gc[next].start = clock - 1; 
								temp = queue[0] ; 
							}
							queue[0]->time_remaining = queue[0]->time_remaining - 1; 
							if(queue[0]->time_remaining == 0) {
								ave_waiting = ave_waiting - clock - queue[0]->arrival_time - queue[0]->burst_time ; 
								ave_turn = ave_turn - clock - queue[0]->arrival_time ; 
								queue = dequeue(queue,&num) ; 
								queue = find_min(queue,num) ; 
								break ; 
							}
						}
						else 
							cout<<"\n No process for execution " ; 
						// execute the process at the top as well.. 
						break ; 
			case 3 : 	while(num > 0)  {
							queue = find_min(queue,num) ; 
							gc[next].name = queue[0]->pid ; 
							gc[next].start = clock ; 
							next++ ; 
							clock = clock + queue[0]->time_remaining ; 
							ave_turn = ave_turn + clock - queue[0]->arrival_time ; 
							ave_waiting = ave_waiting + clock - queue[0]->arrival_time - queue[0]->burst_time ;
							queue = dequeue(queue,&num) ;
						}
						for(int curr = 0; curr < next ; curr++)
							cout<<"\nStart process - : "<<gc[curr].name<<" at - "<<gc[curr].start ; 
						ave_turn = ave_turn/(id-1) ; 
						ave_waiting = ave_waiting/(id-1) ; 
						cout<<"\n Average Waiting Time - "<<ave_waiting ; 
						cout<<"\n Average Turnaround Time - "<<ave_turn<<endl ; 
						exit(0); 

		}
	}
	return 0 ;	
}