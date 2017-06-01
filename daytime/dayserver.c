#include<stdio.h>
#include<string.h>
#include<strings.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main(int argc,char *argv[])
{
	int sockfd,newsockfd,clilen,i,j,k,l,port;
	struct sockaddr_in serv_addr,cli_addr;
	char times[100];
	time_t time1;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("Error on socket creation");
		exit(0);
	}
	bzero((char *)&serv_addr,sizeof(serv_addr));
	port=atoi(argv[1]);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(port);
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	{
		printf("error on binding\n");
		exit(0);
	}
	clilen=sizeof(cli_addr);
	listen(sockfd,5);
	newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
	if(newsockfd<0)
	{
		printf("error on accept\n");
	}
	else
	{
		memset(times,0,100);
		time1=time(NULL);
		sprintf(times,"%s",ctime(&time1));
		write(newsockfd,times,100);
	}
	close(newsockfd);
	close(sockfd);
}
		
	
