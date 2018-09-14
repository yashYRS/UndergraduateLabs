#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main() {
	int sd ; 
	char buf[25] , msg[25] ;   
	struct sockaddr_in address; 
	// Create a UDP socket 
	sd = socket(AF_INET,SOCK_DGRAM,0) ; 
	/* Construct the address for use with sendto/recv from */
	address.sin_family = AF_INET ; 
	address.sin_addr.s_addr = inet_addr("127.0.0.1") ; 
	address.sin_port = htons(9704) ; 
	printf("\nEnter Buffer -  ");
	fgets(buf,25,stdin) ; 
	int len = sizeof(address) ; 
	int m = sendto(sd,buf,sizeof(buf),0,(struct sockaddr *)&address,len) ; 
	int n = recvfrom (sd,msg,sizeof(buf),0,(struct sockaddr *)&address, &len) ; 
	printf(" The server echo is - "); 
	puts(msg) ; 
	return 0 ; 
}