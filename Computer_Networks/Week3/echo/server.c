/* ---- 		A CONCURRENT ECHO-SERVER [echos back whatever is sent by any client] ---- */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORTNO 10200 
int main() {
	int sockfd,newsockfd,portno,clilen,n=1 ; 
	char buf[256] ; 
	struct sockaddr_in seraddr,cliaddr; 
	int i,value; 
	sockfd = socket(AF_INET,SOCK_STREAM,0) ; 
	seraddr.sin_family = AF_INET ; 
	seraddr.sin_addr.s_addr = inet_addr("172.16.58.98") ; 
	seraddr.sin_port = htons(PORTNO) ; 
	bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr)) ; 
	// Create a connection queue ; ignore child exit details and wait for the clients 
	listen(sockfd,5) ; 
	while(1) {
		// Accept a connection 
		clilen = sizeof( clilen ) ; 
		newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr,&clilen ) ; 
		// Fork to create a process for this client and perform a test to see whether you're the parent or the child 
		if ( fork() == 0 ) {
			// If you're the child, you can now read/write to the client on newsockfd 
			n = read(newsockfd,buf,sizeof(buf)) ; 
			printf("\n Message from the client %s \n",buf) ; 
			n = write(newsockfd,buf,sizeof(buf)) ; 
			close(newsockfd) ;
			exit(0) ; 
		}
		else 
			close(newsockfd) ;
	}
}