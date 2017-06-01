#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<strings.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
	int sockfd,newsockfd,port,clilen,i,j,k;
	struct sockaddr_in serv_addr,cli_addr;
	char msg[100],cmd[100],path[100];
	memset(cmd,0,100);
	memset(path,0,100);
	FILE *fp,*fp1;
	port=atoi(argv[1]);
	bzero(&serv_addr,sizeof(serv_addr));
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("error creating socket\n");
		exit(0);
	}
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(port);
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	{
		printf("error on binding\n");
		exit(0);
	}
	listen(sockfd,5);
	clilen=sizeof(cli_addr);
	newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
	if(newsockfd<0)
	{
		printf("Error on accept\n");
		exit(0);
	}
	else
	{
		
		memset(msg,0,100);
		read(newsockfd,msg,100);
		strcpy(cmd,"find -name ");
		strcat(cmd,msg);
		strcat(cmd," >> 15.txt");
		system(cmd);
		fp1=fopen("15.txt","r");
		fgets(path,100,fp1);
		path[strlen(path)-1]='\0';
		fp=fopen(path,"r");
		if(fp==NULL)
		{
			write(newsockfd,"error",5);
			exit(0);
		}
		else
		{
			memset(msg,0,100);
			while(fgets(msg,100,fp))
			{
				if(write(newsockfd,msg,100)<0)
				{
					printf("Can't Send\n");
				}
			}
			if(!fgets(msg,100,fp))
			{
				write(newsockfd,"done",4);
			}
		}
		close(newsockfd);
	}
	close(sockfd);
	remove("15.txt");
}
		
	
