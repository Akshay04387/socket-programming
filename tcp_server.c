/*Socket programming*/
/* Server part for the TCP */

/*libraries needed*/
#include <stdio.h>
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
	int sockfd,connfd;
	char read_buffer[1024],write_buffer[1024];
	int clilen,readbytes,writebytes;
	/*structures for binding the sockets*/
	struct sockaddr_in serv_addr,cli_addr;
	clilen = sizeof(cli_addr);

	/*creation of the socket*/
	sockfd = socket(AF_INET,SOCK_STREAM,0);	//AF_INET -->IPV4
						//SOCK_STREAM -->TCP based
						//0 -->protocol selection default
	
	if(sockfd<0) error("socket cannot be created\n");	//check for error

	/*setting up the structures for the server to bind with the socket*/
	bzero((char*)&serv_addr,sizeof(serv_addr));	//clears the structure
	serv_addr.sin_family = AF_INET;	
	serv_addr.sin_addr.s_addr =INADDR_ANY;
	serv_addr.sin_port = htons(PORTNO);

	/*binding the socket to the structure*/
	int ret = bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret<0) error("Error in Binding\n");

	/*maximum calls that are allowed or can be listened*/
	int backlog = 5;
	ret = listen(sockfd,backlog);
	if(ret<0) error("listen failed to accept requests\n");

	/*used to establish connection between client and server*/
	connfd = accept(sockfd,(struct sockaddr*)&cli_addr,&clilen);
	if(connfd<0) error("error in accepting requests\n");

	/*writing the communication between client and server inside a while(1) loop*/
	while(1){
				
		bzero(read_buffer,sizeof(read_buffer));
		readbytes = read(connfd,read_buffer,sizeof(read_buffer));
		read_buffer[readbytes]='\0';
		printf("the message from the client: \n%s",read_buffer);
		printf("enter the message:");
		bzero(write_buffer,sizeof(write_buffer));
		readbytes = 0;
		while((write_buffer[readbytes++]=getchar())!='\n');

		write(connfd,write_buffer,sizeof(write_buffer));
	}
	return 0;
}
