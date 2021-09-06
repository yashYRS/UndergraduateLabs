#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/ioctl.h>
#include<time.h> // use of these 2, still not known.. 

int main() {
	int server_socket, client_socket ; 
	int server_len, client_len ; 
	struct sockaddr_in server_address, client_address ; 
	int result ; 
	fd_set readfds, testfds ; 

	// Creating a socket 
	server_socket = socket(AF_INET,SOCK_STREAM, 0) ; 
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1") ; 
	server_address.sin_port = htons(10201);
	server_address.sin_family = AF_INET ; 
	server_len = sizeof(server_address) ; 

	bind(server_socket,(struct sockaddr *)&server_address,server_len) ; 
	listen(server_socket,5) ; 

	FD_ZERO(&readfds) ; 
	FD_SET(server_socket,&readfds) ; // add readfds to the set 

	while(1) {
		char ch; 
		int fd,nread ; 
		time_t rawtime; 
		struct tm * timeinfo;
		testfds = readfds ; // since we don't want the original readfds to change 
		result = select(FD_SETSIZE, &testfds, (fd_set *)0,(fd_set *)0,(struct timeval *)0);//writing and error not checked 
		if ( result < 1 ){
			perror(" SERVER ERROR ") ; 
			exit(1) ; 
		}
		for(fd = 0; fd < FD_SETSIZE ; fd=fd+1) {
			if (FD_ISSET(fd,&testfds)) {	// if fd present in the set 
				if ( fd == server_socket ) {	// if fd is the server socket, must be a request for a new connection
					client_len = sizeof(client_address);
					client_socket = accept(server_socket,(struct sockaddr*)&client_address,&client_len);
					FD_SET(client_socket,&readfds) ; 
					printf("\n Adding client on the fd %d \n",client_socket );
				}
				// if not the server must be the client
				else {
					ioctl(fd,FIONREAD,&nread);//FIONREAD signifies thatX no. of bytes to be read returned in nread by fd(client)
					if(nread == 0){
						close(fd);
						FD_CLR(fd,&readfds) ; 
					}
					else {
						read(fd,&ch,1);
						time(&rawtime);
					  	timeinfo = localtime(&rawtime);
					  	char time_current[80] = "";
					  	strcpy(time_current,asctime(timeinfo));
						time_current[strlen(time_current)] = '\0';
						write(fd, time_current,sizeof(time_current));
						sleep(3);
					}
				}
			}
		}
	}

	return 0 ; 
}