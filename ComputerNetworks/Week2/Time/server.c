// Server Program returns the current time details, when asked by a client 

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>

#define PORTNO 10200
int main(){
	int sockfd,newsockfd,portno, clilen, n = 1; 
	struct sockaddr_in seraddr, cliaddr; 
	int i, value,id ;  
	id = getpid(); 

	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );

  	char temp[20],time_current[80];
  	strcpy(time_current,asctime(timeinfo)); 

  	sprintf(temp,"%d",id);
  	strcat(time_current,temp);
  	//Create a unnamed socket for the server 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// Name the socket 

	seraddr.sin_family = AF_INET; // setting the family of the server address 
	seraddr.sin_addr.s_addr = inet_addr("172.16.58.38");	// setting the server IP 
	seraddr.sin_port = htons(PORTNO);	// converting to apt format 
	bind(sockfd,(struct sockaddr*)&seraddr, sizeof(seraddr)) ;  // binding to the server 
	// Create a connection queue and wait for clients 
	listen ( sockfd, 5);
	while(1) { 
		char buf[256];
		printf(" server waiting ");
		// Accept a connection 
		clilen = sizeof(clilen);
		newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen) ; // accept the connection by client 
		n = read(newsockfd, buf, sizeof(buf));		// Read the message of the client 
		printf("\n  Message from Client %s \n",buf);
		// find the time and send it.. 
		n = write(newsockfd , time_current, sizeof(time_current));		// write the message of the client, to the socket .. 
		break ; 
	}
	close(sockfd);
}