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
	// Create a socket for the client 
	sockfd = socket(AF_INET , SOCK_STREAM, 0); 
	// Name the socket as agreed with the server 
	address.sin_family = AF_INET ; 
	address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	address.sin_port = htons(19201);
	len = sizeof(address); 

	// Connect the socket to the server's socket 
	result = connect(sockfd, (struct sockaddr *)&address, len); 
	if(result == -1 ) {
		perror(" \n CLIENT ERROR ") ; 
		exit(1) ; 
	}


	int number ;  
	printf( " \n ENTER number of elements in the array -> \t "); 
	scanf("%d",&number) ; 
	int array[number],buf[number] ;
	printf(" Enter the elements of the array -> \t"); 
	for(int i = 0 ; i < number ; i++)
		scanf("%d",&array[i]); 
	write(sockfd, &number, sizeof(number));
	write(sockfd,array,sizeof(array)) ;  
	printf(" SORTED ARRAY sent back from the sever is ... - ") ;
	read(sockfd, buf, sizeof(buf)) ; 
	for(int i = 0 ; i < number ; i++ )
		printf(" %d ", buf[i]) ;  
	close(sockfd) ; 
}