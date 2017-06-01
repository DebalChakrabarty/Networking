#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<strings.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
int main(int argc,char *argv[])
{
	int sockfd,clilen,port;
	char msg[100],fname[100],text[100];
	memset(msg,0,100);
	memset(fname,0,100);
	FILE *fp;
	struct sockaddr_in serv_addr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("error opening socket\n");
		exit(0);
	}
	bzero(&serv_addr,sizeof(serv_addr));
	port=atoi(argv[1]);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serv_addr.sin_port=htons(port);
	if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	{
		printf("error connecting\n");
	}
	else
	{
		
			printf("Enter the filename to search");
			scanf("%s",fname);
			printf("Enter the filename to be written to:\n");
			scanf("%s",msg);
			fp=fopen(msg,"w");
			write(sockfd,fname,100);
			while(1)
			{
				memset(text,0,100);
				read(sockfd,text,100);
				if(strcmp(text,"error")==0)
				{
					printf("file not available\n");
					exit(0);
				}
				else if(strcmp(text,"done")==0)
				{
					printf("file is transferred\n");
					close(sockfd);
					close(fp);
					break;
				}
				else
				{
					fprintf(fp,"%s",text);
					fputs(text,stdout);
				}
			}
			close(sockfd);
			return 0;
	}
}
	
