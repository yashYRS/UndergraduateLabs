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
	char ch[256], buf[256] ; 

	// Create a socket for the client 
	sockfd = socket(AF_INET , SOCK_STREAM, 0); 
	// Name the socket as agreed with the server 
	address.sin_family = AF_INET ; 
	address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	address.sin_port = htons(10201);
	len = sizeof(address); 

	// Connect the socket to the server's socket 
	result = connect(sockfd, (struct sockaddr *)&address, len); 
	if(result == -1 ) {
		perror(" \n CLIENT ERROR ") ; 
		exit(1) ; 
	}
	printf( " \n ENTER STRING \t "); 
	scanf("%s",ch);
	ch[strlen(ch)] = '\0';
	n = write(sockfd, ch, strlen(ch)); 
	printf(" STRING sent back from the sever is ... - ") ;
	while(n){
		n = read(sockfd, buf, sizeof(buf)) ; 
		printf("\n %s",buf);
	}
	close(sockfd) ; 
	exit(0);
}