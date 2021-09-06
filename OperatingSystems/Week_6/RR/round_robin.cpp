#include<iostream>
#include<stdlib.h>

using namespace std; 


struct process{
	int pid ; 
	int time_remaining ;
	int arrival_time ; 
	int burst_time; 
	int* start_time ; 
	int starts ; 
	int finished ; 
	//int arriving_order ; 
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
	cout<<"################     MENU Ends      ###############"<<endl;
	return i ; 
}

p_ptr* enqueue(p_ptr* plist, int *n,int clock,int id) {
	p_ptr temp = take_input(clock,id) ;
	plist[*n] = temp ; 			// temp added at the end of the queue... 
	*n = *n + 1; 
	return plist ; 				

}

p_ptr* dequeue(p_ptr* plist,int* n,int curr) {
	*n = *n - 1;  
	for(int i = curr; i < *n ; i++) 
		plist[i] = plist[i+1] ; 
	return plist ; // remove element, and shift the rest .. 
}

int main(){
	p_ptr* queue = (p_ptr*)malloc(sizeof(p_ptr)*30); // plist stores all the processes
	int num = 0 ; 
	int clock = 0 ;
	chart gc[100] ;
	int quantum = 10 ; 
	int next = 0 ;int id = 1 ; /* ENTER ID OF EACH PROCESS */ 
	int curr = -1 ; 
	int temp_change = 0 ; 
	float ave_waiting = 0, ave_turn = 0  ;
	while(1) {
		switch(prompt(clock)) {
			case 1 :	queue = enqueue(queue,&num,clock,id++) ;
						break ;  
			case 2 : 	clock++ ;
						if (num > 0) {
							if (temp_change%10 == 0) {	// check whether need to change ; 
								curr = (curr + 1)%num ; 		// if ends go the next process in the queue
								gc[next].name = queue[curr]->pid ; 
								gc[next].start = clock-1;
								next++ ; 
							}
							queue[curr]->time_remaining = queue[curr]->time_remaining - 1 ; 
							temp_change++ ;
							if (queue[curr]->time_remaining == 0) {
								temp_change = 0 ; 		// to adjust the clock varying ; 
								ave_waiting = ave_waiting + clock - queue[curr]->arrival_time - queue[curr]->burst_time ; 
								ave_turn = ave_turn + clock - queue[curr]->arrival_time ;
								queue = dequeue(queue,&num,curr) ; // curr doesnt change, although it will 
								curr = (curr - 1 )%num ; // decrease one, since it will increment in the next iteration.. 
							}
						}
						else 
							cout<<"\n No process for execution " ; 
						break ; 
			case 3 :	while(num > 0)  {
							if(temp_change == 0) {
								curr = (curr + 1)%num ; // control to the next process 
								gc[next].name = queue[curr]->pid ; 
								gc[next].start = clock;			// add new 
								next++ ; 
							}
							else {
								queue[curr]->time_remaining = queue[curr]->time_remaining - 10 + temp_change ;  
								clock = clock + 10 - temp_change ; 
								temp_change = 0 ; 
								continue ; 
							}
							if (queue[curr]->time_remaining > 10 )  {
								queue[curr]->time_remaining = queue[curr]->time_remaining - 10 ; 
								clock = clock + 10 ; 
								temp_change = 0 ; 
							}
							else {
								clock = clock + queue[curr]->time_remaining ; // execute till finish 
								ave_waiting = ave_waiting + clock - queue[curr]->arrival_time - queue[curr]->burst_time ; 
								ave_turn = ave_turn + clock - queue[curr]->arrival_time ;
								queue = dequeue(queue,&num,curr) ; 
								if (num > 0)
									curr = (curr - 1)%num ; // since we dont want curr to change ; 
								temp_change = 0 ; 
							}
						}
						for(int c = 0 ; c < next ; c++) 
							cout<<"\nStart process - : "<<gc[c].name<<" at - "<<gc[c].start ; 
						ave_turn = ave_turn/(id-1) ; 
						ave_waiting = ave_waiting/(id-1) ; 
						cout<<"\n Average Waiting Time - "<<ave_waiting ; 
						cout<<"\n Average Turnaround Time - "<<ave_turn<<endl ; 
						exit(0); 

		}
	}
	return 0 ;	
}

// Round Robin --> gannt chart needs to be changed // 