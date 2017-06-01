#include<stdio.h>
#include<string.h>
#include<strings.h>
#include<stdlib.h>
#include<sys/types.h> 
#include<netinet/in.h> 
#include<unistd.h>
int main(int argc,char *argv[])
{
	int sockfd,newsockfd,clilen,port,i,j,k,l,flag;
	float ans;
	float number1,number2;
	struct sockaddr_in serv_addr,cli_addr;
	char msg[100];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	if(sockfd<0)
	{
		printf("Error in socket creation\n");
		exit(0);
	}
	bzero((char *)&serv_addr,sizeof(serv_addr));
	port=atoi(argv[1]);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(port);
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	{
		printf("error on binding");
		exit(0);
	}
	clilen=sizeof(cli_addr);
	listen(sockfd,5);
	newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
	if(newsockfd<0)
	{
		printf("error on accept\n");
		exit(0);
	}
	int tmp;
	while(1)
	{
		i=0;
		number1=0;
		number2=0;
		ans=0;
		l=0;
		flag=0;
		memset(msg,0,100);
		read(newsockfd,msg,100);
		while(flag==0)
		{
			tmp=(int)msg[i];
			if(tmp>=48 && tmp<=57)
			{
				tmp-=48;
				number1=number1*10+(float)tmp;
			}
			else
			{
				for(k=i+1;k<strlen(msg)-1;k++)
				{
					tmp=(int)msg[k];
					tmp-=48;
					number2=number2*10+(float)tmp;
				}
				switch(msg[i])
				{
					case '+':
						ans=number1+number2;
						break;
					case '/':
						ans=number1/number2;
						break;
					case '-':
						ans=number1-number2;
						break;
					case '*':
						ans=number1*number2;
				}
				flag=1;
			}
			i++;
		}
		memset(msg,0,100);
		sprintf(msg,"The Answer is :%f",ans);
		printf("The numbers are : %f %f\n",number1,number2);
		printf("%s\n",msg);
		write(newsockfd,msg,100);
	}
	close(sockfd);
}
					
					
			
			
			
	
