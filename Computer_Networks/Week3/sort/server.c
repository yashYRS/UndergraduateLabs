/* ---- 		A CONCURRENT SERVER SORTING input sent by client and returning it back ---- */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORTNO 19201

int main() {
	int sockfd,newsockfd,portno,clilen,n=1 ; 
	int buf[256] ; 
	struct sockaddr_in seraddr,cliaddr; 
	int i,value; 
	sockfd = socket(AF_INET,SOCK_STREAM,0) ; 
	seraddr.sin_family = AF_INET ; 
	seraddr.sin_addr.s_addr = inet_addr("127.0.0.1") ; 
	seraddr.sin_port = htons(PORTNO) ; 
	bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr)) ; 
	// Create a connection queue ; ignore child exit details and wait for the clients 
	listen(sockfd,5) ; 

	int number ; 
	while(1) {
		// Accept a connection 
		clilen = sizeof( clilen ) ; 
		newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr,&clilen ) ; 
		// Fork to create a process for this client and perform a test to see whether you're the parent or the child 
		if ( fork() == 0 ) {
			// If you're the child, you can now read/write to the client on newsockfd 
			n = read(newsockfd,&number,sizeof(number)) ; 
			int a[number] ,temp ; 

			n = read(newsockfd,a,sizeof(a)) ; 
			for(int i = 0 ; i < number - 1 ; i++) {
				for(int j = 0 ; j < number - i - 1; j++) {
					if( a[j] > a[j+1]) {
						temp  = a[j]; 
						a[j] = a[j+1];
						a[j+1] = temp; 
					}
				}
			}
			for(int i = 0 ; i < number ; i ++) 
				printf(" %d ",a[i]);
			n = write(newsockfd,a,sizeof(a)) ; 
			close(newsockfd) ;
			exit(0) ; 
		}
		else 
			close(newsockfd) ;
	}
}