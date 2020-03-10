#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define total_minions 3 //use this to define total no. of receiving minions
int indicator =1;
int number=0;
int a[2048];
int arraylen=0;
char buffer[2048];
int factor;
int sum[200];
int final_sum=0;
int h=0;
int flag=0;
void * clientThread(void *arg)

{

  int newSocket = *((int *)arg);
  int i=0;
  printf("client has joined\n\n");
  int recvlen;
  recvlen=recv(newSocket,buffer,sizeof(buffer),0);
  buffer[recvlen]='\0';
  //printf("%d\n\n",recvlen);
  if(recvlen<0);
  {
  	perror("error in recieving");
  }
	int num=0;
  while(buffer[i]!='\0')
  {
  	if(buffer[i]==',')
  	{	i++;
	  	a[arraylen]=num;
		arraylen++;
		num=0;
	}
  	else
  	{	
		num=(num*10)+(buffer[i]-'0');
		i++;

	}

  }
  //printf("\n%d\n\n",arraylen);
  //printf("%d   %d    %d   %d  %d   %d\n\n",a[0],a[1],a[2],a[3],a[4],a[5]);
}
void * socketThread(void *arg)

{
  int newSocket = *((int *)arg);
  printf("Entered into a new thread\n");
  //printf("value of number is %d\n",number);
  int threadid;                                               //creating threadid to allow sending of data
  threadid=number-1;
  //printf("the value of threadid is %d \n",threadid);
  //sleep(30);
  factor=arraylen/total_minions;
  //printf("\n the value of factor is %d \n",factor);
  int m;
  m=send(newSocket,&factor,sizeof(int),0);                     //sending value of factor to determine the size of recieved array by minions
  if(m<0)
  {
  	perror("error in sending factor\n");
  }
  int p;
  //printf("now sending data\n");
  //printf("\n threadid %d and factor value is %d ",threadid,factor);
  for(p=threadid*factor;p<(threadid+1)*factor;p++)
  {
  	//printf("\n packet sent \n");
  	int s;
  	s=send(newSocket,&a[p],sizeof(int),0);                        //sending array elements one by one
  	if(s<0)
  	{
  		perror("error in sending");
  	}
  	
  }
  int f;
  f=recv(newSocket,&sum[threadid],sizeof(int),0);                   //receiving sum from the minions
  printf("\nthe sum recieved is %d\n",sum[threadid]);
  flag++;
}


int main(int argc,char *argv[])
{
	struct sockaddr_in serverAddr;
	int socketfd;//file descriptor for socket id
	if(argc<2)//if portno. is not provided as an argument then exit(-1)
	{
		fprintf(stderr,"use %s <port>\n",argv[0]);
		exit(-1);
	}

	int portno =atoi(argv[1]);                                //using atoi to read argument as an integer
	socketfd = socket(AF_INET,SOCK_STREAM,0);                 //using IPv4 connection and TCP protocol
	if(!socketfd)                                            //socketfd returns 0 if any error in creating socket
	{
		perror("Error in opening socket");
		exit(-1);
	}
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=htonl(INADDR_ANY);      //use this to specify IP of the server or use a local address for tranferring of data
	serverAddr.sin_port=htons(portno);


	if(bind(socketfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr))<0)      //binding of socketfd to the port
	{
		perror("failed to bind");
		exit(4);
	}
	if(listen(socketfd,50))                            //50 specifies the maximum no. of backlog connections
	{
		perror("error in listen ");
		exit(2);
	}
	int optval=1;
	setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,(const void *)&optval,sizeof(int));  // unknown function
	struct sockaddr_in clientAddr;
	int cliLen=sizeof(clientAddr);
	pthread_t minions[30];
	pthread_t client;
	cliLen= sizeof(clientAddr);
	int newSocket1=accept(socketfd,(struct sockaddr *)&clientAddr,&cliLen);          //accept call returns a newsocket file descriptor
	if(newSocket1<0)
	{
		perror("Error in accept");
		exit(6);
	}
	if( pthread_create(&client, NULL, clientThread, &newSocket1) != 0 )
		printf("Failed to create thread\n");
	pthread_join(client,NULL);
	printf("the array recieved is :\n");
	int k;
	for(k=0;k<arraylen;k++)
	{
		printf("%d ",a[k]);
	}
	printf("\n");
	//printf("%s \n",buffer);	





    int i = 0;
    while(1)
    {
    	cliLen= sizeof(clientAddr);
		int newSocket=accept(socketfd,(struct sockaddr *)&clientAddr,&cliLen);
		if(newSocket<0)
		{
			perror("Error in accept");
			continue;
		}
		number++;
		if( pthread_create(&minions[i++], NULL, socketThread, &newSocket) != 0 )            //thread creation for minions
			printf("Failed to create thread\n");
		//pthread_join(minions[i++],NULL);
		
		if(number==total_minions)
		{
			int v;
			for(v=0;v<number;v++)
			{
				pthread_join(minions[v],NULL);
			}
			
		}
		if(flag==total_minions)                                     //final sending of the sum of numbers
		{
			int u,p;
			for(p=0;p<total_minions;p++)
			{
				final_sum=final_sum+sum[p];
			}
			u=send(newSocket1,&final_sum,sizeof(int),0);
			//printf("package sent");
		}
		
	}
	

	
	return 0;
}
