#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<strings.h>
#include<sys/types.h> 
#include<netinet/in.h> 
#include<sys/socket.h>
int main(int argc,char *argv[])
{
	int sockfd,newsockfd,i,j,k,l;
	char msg[100];
	struct sockaddr_in serv_addr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("socket creation failed\n");
		exit(0);
	}
	else
		printf("Socket successfully created\n");
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	{
		printf("error on connecting\n");
		exit(0);
	}
	else
		printf("connected to the server\n");
	while(1)
	{
		memset(msg,0,100);
		printf("Enter the string to be sent to the: \n");
		fgets(msg,100,stdin);
		write(sockfd,msg,100);
		memset(msg,0,100);
		read(sockfd,msg,100);
		printf("the message from server : %s \n");
	}
	close(sockfd);
}
		
	
	
