#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<strings.h>
#include<sys/types.h> 
#include<netinet/in.h> 
int main(int argc,char *argv[])
{
	int sockfd,newsockfd,i,j,k,clilen,portno;
	struct sockaddr_in serv_addr,cli_addr;
	char msg[100];
	bzero((char *)&serv_addr,sizeof(serv_addr));
	memset(msg,0,100);
	portno=atoi(argv[1]);
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		error("error opening socket\n");
		exit(0);
	}
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(portno);
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	{
		error("error on binding socket\n");
		exit(0);
	}
	listen(sockfd,5);
	clilen=sizeof(cli_addr);
	newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
	if(newsockfd<0)
		printf("error on accept\n");
	while(1)
	{
		memset(msg,0,100);
		read(newsockfd,msg,100);
		printf("from client: %s\n");
		memset(msg,0,100);
		printf("Enter the message to send to client:\n");
		fgets(msg,100,stdin);
		write(newsockfd,msg,100);
	}
	close(sockfd);
}
	
	
