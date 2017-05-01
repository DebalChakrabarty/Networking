#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define Server "127.0.0.1"
int main()
{
    int sockfd, newsockfd,  clilen,i,n;
    char buffer[256],msg[256],opr;
    struct sockaddr_in serv_addr, cli_addr;
    int a,b;
   	int sym;
    int ncount=0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(Server);;
    serv_addr.sin_port = htons(1550);
 
    bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr));

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    float rs=0;
    int tmp;
    int nol=0;
	while(1)
	{	
			bzero(buffer,256);
			
			n = read(newsockfd,buffer,255);
			
			printf("Here is the expression: %s\n",buffer);
			for(i=0;i<=strlen(buffer) -1 ;i++)
			{
				tmp = (int)buffer[i];
				if(tmp>=48 && tmp <=57)
				{
					tmp= tmp - 48;
					nol = nol * 10 + tmp;
				}
				if(buffer[i] == '+')
				{
					a = nol;
					nol=0;
					sym = 1;
				
				}
				if(buffer[i] == '-')
				{
					a = nol;
					nol=0;
					sym = 2;
				
				}
				if(buffer[i] == '*')
				{
					a = nol;
					nol=0;
					sym = 3;
				
				}
				if(buffer[i] == '/')
				{
					a = nol;
					nol=0;
					sym = 4;
				
				}
			}
			
			if(sym==1)
			{
				rs = a+nol;
			}
			if(sym==2)
			{
				rs = a-nol;
			}
			if(sym==3)
			{
				rs = a*nol;
			}
			if(sym==4)
			{
				rs = a/nol;
			}
				
			bzero(msg,256);
			snprintf (msg, sizeof(msg), "%f", rs);
			rs=0;
			nol=0;
			a=0;
			printf("%s",msg);
			n = write(newsockfd,msg, 255);
	}	
	
	close(newsockfd);
	
	close(sockfd);
    return 0; 
}
