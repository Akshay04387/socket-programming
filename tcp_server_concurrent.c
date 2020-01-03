/*Tcp server for concurrent communicatio*/

/*libraries*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

/*macros*/
#define PORTNO 4000

/*private data members*/
char rd_buf[1024],wr_buf[1024];

/*error handling*/
void error(char *msg){
	perror(msg);
	exit(1);
}

int main(){
	/*file descriptors*/
	int sockfd,connfd;
	struct sockaddr_in serv_addr,cli_addr;
	
	/*creating socket*/
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0) error("error while Socket creation\n");
	else printf("socket creation successful...\n");
	/*setting up system object*/
	bzero((char*)&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORTNO);

	/*binding the socket to the object*/
	int ret = bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	if(ret<0) error("error while binding\n");
	else printf("socket binding successful...\n");

	/*setting no of listeners*/
	int backlog = 5;
	ret = listen(sockfd,backlog);
	if(ret<0) error("error while listening requests\n");
	else printf("client to socket connection successful...\n");

	int clilen = sizeof(cli_addr);
	/*accept requests from client*/
	connfd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
	if(connfd <0) error("error while accepting requests\n");
	else printf("requests has been accepted\n Starting communication...\n");

	ret = fork();

	if(ret==0){
		while(1){
			bzero(&rd_buf,sizeof(rd_buf));
			recv(connfd,rd_buf,sizeof(rd_buf),0);			
			printf("Client message: %s\n",rd_buf);
		}
	}
	else{
		while(1){
			bzero(&wr_buf,sizeof(wr_buf));
			printf("Enter the messsage:\n");
			fgets(wr_buf,1024,stdin);			
			send(connfd,wr_buf,strlen(wr_buf)+1,0);
			printf("message send successfully\n");
		}
	}
	close(sockfd);

}
