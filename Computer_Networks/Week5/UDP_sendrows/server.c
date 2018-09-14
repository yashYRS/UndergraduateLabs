#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

void disp(int *g, int n,int r) {
	printf("\n MATRIX ---> \n");
	for(int i = 0 ; i < r ; i++) {
		for(int j = 0 ; j < n ; ++j) 
			printf(" %d ",g[i*n + j]) ; 
		printf("\n");
	}

}
int main() {
	int sd ; 
	char buf[25] ;  
	struct sockaddr_in sadd, cadd; 
	// Create a UDP socket 
	sd = socket(AF_INET,SOCK_DGRAM,0) ; 
	/* Construct the address for use with sendto/recv from */
	sadd.sin_family = AF_INET ; 
	sadd.sin_addr.s_addr = inet_addr("127.0.0.1") ; 
	sadd.sin_port = htons(9704) ; 
	int result = bind(sd, (struct sockaddr *)&sadd, sizeof(sadd)) ; 
	int len = sizeof(cadd) ; 
	int row_size ; int rows_added = 0 ; 
	int col_size ; 
	int m = recvfrom (sd,&row_size,sizeof(row_size),0,(struct sockaddr *)&cadd, &len) ; 
	//printf(" The server send is - %d",row_size);   
	m = recvfrom (sd,&col_size,sizeof(col_size),0,(struct sockaddr *)&cadd, &len) ; 
	int *temp = (int *)malloc(sizeof(int)*row_size); 
	int *matrix = (int*)calloc(row_size*col_size,sizeof(int)); 
	while(rows_added < col_size) {
		m = recvfrom (sd,temp,sizeof(int)*row_size,0,(struct sockaddr *)&cadd, &len) ;
		for(int i = 0 ; i < row_size ; i++)
			matrix[rows_added*row_size + i] = temp[i] ;  
		rows_added++ ; 
	}
	disp(matrix,row_size,rows_added) ; 
	return 0 ; 
}