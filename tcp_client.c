/*Socket programming*/
/*Client part for the TCP */

/*libraries needed*/
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

#define PORTNO 4000

/*method for error generation*/
void error(char *msg){
	perror(msg);
	exit(1);
}

int main(){
	
	/*defining the socket ids for server and client*/
	int sockfd;
	char read_buffer[1024],write_buffer[1024];
	int readbytes,writebytes;
	/*structures for binding the sockets*/
	struct sockaddr_in serv_addr;

	/*creation of the socket*/
	sockfd = socket(AF_INET,SOCK_STREAM,0);	//AF_INET -->IPV4
						//SOCK_STREAM -->TCP based
						//0 -->protocol selection default
	
	if(sockfd<0) error("socket cannot be created\n");	//check for error

	/*setting up the structures for the server to bind with the socket*/
	bzero((char*)&serv_addr,sizeof(serv_addr));	//clears the structure
	serv_addr.sin_family = AF_INET;	
	serv_addr.sin_addr.s_addr =inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(PORTNO);

	/*connecting the socket to the server*/
	int ret = connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret<0) error("could not connect to the server\n");
	else printf("connection established...\n");	
	
	/*writing the communication between client and server inside a while(1) loop*/
	while(1){
		bzero(read_buffer,sizeof(read_buffer));
		printf("enter the message:");
		
		readbytes=0;
		while((read_buffer[readbytes++]=getchar())!='\n');

		write(sockfd,read_buffer,sizeof(read_buffer));
		bzero(read_buffer,sizeof(read_buffer));
		read(sockfd,read_buffer,sizeof(read_buffer));
		printf("data from server: %s",read_buffer);

	}
	close(sockfd);
	return 0;
}
