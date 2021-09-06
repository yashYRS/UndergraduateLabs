// Server returns the IP address, port no of the client as well the message back in upper case l

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORTNO 10200
int main(){
	int sockfd,newsockfd,portno, clilen, n = 1; 
	struct sockaddr_in seraddr, cliaddr; 
	int i, value ; 
	//Create a unnamed socket for the server 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// Name the socket 
	seraddr.sin_family = AF_INET; // setting the family of the server address 
	seraddr.sin_addr.s_addr = inet_addr("172.16.58.38");	// setting the server IP 
	seraddr.sin_port = htons(PORTNO);	// converting to apt format 
	bind(sockfd,(struct sockaddr*)&seraddr, sizeof(seraddr)) ;  // binding to the server 

	// Create a connection queue and wait for clients 
	listen ( sockfd, 5);
	printf(" server waiting ");
	clilen = sizeof(clilen);
	// Accept a connection 
	newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen) ; // accept the connection by client 
	while(1) {
		char buf[256] =""; 
		n = read(newsockfd, buf, sizeof(buf));		// Read the message of the client 	
		for(int i = 0 ; i < strlen(buf); i++) {
			if(buf[i] > 96 && buf[i] < 122)
				buf[i] = buf[i] - 32;
		}
		printf("\n Client msg--  %s IP address = %s  PortNo. -- %d \n",buf,inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
		n = write(newsockfd , buf, strlen(buf));		// write the message of the client, to the socket .. 
		if (strcmp(buf,"QUIT") == 0)
			break ; 
	}
	close(sockfd); 
}