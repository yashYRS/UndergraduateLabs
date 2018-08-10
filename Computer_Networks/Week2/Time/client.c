#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {
	int len, result, sockfd, n =1 ; 
	struct sockaddr_in address; 
	char ch[256] = " Tell me the time ";
	char buf[256] ; 

	// Create a socket for the client 
	sockfd = socket(AF_INET , SOCK_STREAM, 0); 
	// Name the socket as agreed with the server 
	address.sin_family = AF_INET ; 
	address.sin_addr.s_addr = inet_addr("172.16.58.38"); 
	address.sin_port = htons(10200);
	len = sizeof(address); 

	// Connect the socket to the server's socket 
	result = connect(sockfd, (struct sockaddr *)&address, len); 
	if(result == -1 ) {
		perror(" \n CLIENT ERROR ") ; 
		exit(1) ; 
	}
	write(sockfd, ch, strlen(ch)); 
	printf(" STRING sent back from the sever is ... - ") ;
	read(sockfd, buf, sizeof(buf)) ; 
	puts(buf) ; 
	close(sockfd) ; 
}