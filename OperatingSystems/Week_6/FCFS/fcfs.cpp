#include<iostream>
#include<stdlib.h>

using namespace std; 


struct process{
	int pid ; 
	int time_remaining ;
	int arrival_time ; 
	int burst_time; 
	int start_time ; 
	int finished ; 
};
typedef process* p_ptr ; 

p_ptr set_Values(int at, int bt ,int id) {
	p_ptr temp = (p_ptr)malloc(sizeof(int)*6) ; 
	temp->time_remaining = bt ; 
	temp->arrival_time = at ;
	temp->burst_time = bt ; 
	temp->finished = 0 ;
	temp->start_time = -1 ; 
	temp->pid = id ; 
	return temp;  
}

int execute(p_ptr p,int time_given, int clock) {
	if (p->start_time < 0) {
		p->start_time = clock - time_given ;// since clock already incremented before passed to the system...
	}
	if (time_given <= p->time_remaining) {
		p->time_remaining = p->time_remaining - time_given ; 
		time_given = 0 ; 
	}
	else {
		time_given = time_given - p->time_remaining ; 
		p->time_remaining = 0 ; 
	}
	if (p->time_remaining == 0) 
		p->finished = clock ; 
	return time_given ; 		// so that if time left next process can utilize...
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

int main(){
	p_ptr* queue = (p_ptr*)malloc(sizeof(p_ptr)); // plist stores all the processes
	int num = 0 ; // number of processes in the array 
	int clock = 0 ; int time_given ; 
	p_ptr* gannt_chart= (p_ptr*)malloc(sizeof(p_ptr)) ; 
	int next = 0 ;int id = 1 ; /* ENTER ID OF EACH PROCESS */ 
	while(1) {
		switch(prompt(clock)) {
			case 1 :	queue = enqueue(queue,&num,clock,id++) ;
						queue = (p_ptr*)realloc(queue,sizeof(p_ptr)*(num+1)) ; 
						break ;  
			case 2 : 	clock++ ;
						time_given = 1 ; 
						if (num > 0) {
							time_given = execute(queue[0],time_given,clock) ; 
							if (queue[0]->finished != 0) {
								gannt_chart[next] = queue[0] ; 
								gannt_chart = (p_ptr*)realloc(gannt_chart,sizeof(p_ptr)*(num+1)) ; 
								next++ ; 
								queue = dequeue(queue,&num) ; 
							}
						}
						else 
							cout<<"\n No process for execution " ; 
						// execute the process at the top as well.. 
						break ; 
			case 3 :	int curr = 0 ; 
						while(num > 0)  {
							time_given = queue[curr]->time_remaining ; 
							clock = clock + time_given ; 
							time_given = execute(queue[0],time_given,clock) ; 
							gannt_chart[next] = queue[0] ; 
							next++ ;							
							queue = dequeue(queue,&num) ;	// since processes have to get over, entire time slices given
						}
						curr = 0 ; 
						float ave_waiting = 0, ave_turn = 0  ; 
						while ( curr < next) {
							cout<<"\nStart process id : "<<gannt_chart[curr]->pid<<" at - "<<gannt_chart[curr]->start_time<<" End -"<<gannt_chart[curr]->finished ; 
							ave_waiting = ave_waiting + gannt_chart[curr]->start_time - gannt_chart[curr]->arrival_time ; 
							ave_turn  = ave_turn + gannt_chart[curr]->finished - gannt_chart[curr]->arrival_time ; 
							curr++ ; 
						}
						ave_turn = ave_turn/next ; 
						ave_waiting = ave_waiting/next ; 
						cout<<"\n Average Waiting Time - "<<ave_waiting ; 
						cout<<"\n Average Turnaround Time - "<<ave_turn<<endl ; 
						exit(0); 

		}
	}
	return 0 ;	
}