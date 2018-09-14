#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

void disp(int *g, int n) {
	for(int i = 0 ; i < n ; i++) 
		printf(" %d ",g[i]) ; 
}
int main() {
	int sd ; 
	struct sockaddr_in address; 
	// Create a UDP socket 
	sd = socket(AF_INET,SOCK_DGRAM,0) ; 
	/* Construct the address for use with sendto/recv from */
	address.sin_family = AF_INET ; 
	address.sin_addr.s_addr = inet_addr("127.0.0.1") ; 
	address.sin_port = htons(9704) ; 
	int len = sizeof(address) ; 
	int row_size, col_size ; 
	printf(" Enter the number of elements in each row - ");
	scanf("%d",&row_size) ; 
	int m = sendto(sd,&row_size,sizeof(row_size),0,(struct sockaddr *)&address,len) ; 
	printf("\n Enter the number of columns present - " );
	scanf("%d",&col_size) ;
	m = sendto(sd,&col_size,sizeof(col_size),0,(struct sockaddr *)&address,len) ; 
	int *temp = (int *)malloc(row_size*sizeof(int)) ;
	while(col_size-- > 0 ) { 
		printf("\nEnter Row -  "); 
		for(int i = 0 ; i < row_size ; i++)
			scanf("%d",&temp[i]); 
		disp(temp,row_size) ; 
		m = sendto(sd,temp,sizeof(temp),0,(struct sockaddr *)&address,len) ;
	}
	return 0 ; 
}