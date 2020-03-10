#include <arpa/inet.h>
#include<netinet/in.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include<string.h>
#include <netdb.h>
int main(int argc,char *argv[])
{
    struct sockaddr_in serverAddr;
    struct hostent *server;
    char *hostname;
    int socketfd;
    if(argc <3)
    {
        fprintf(stderr,"use %s <hostname> <port>\n",argv[0]);
        exit(-1);
    }
    hostname=argv[1];
    int portno =atoi(argv[2]);
    socketfd=socket(AF_INET,SOCK_STREAM,0);
    if(!socketfd)
    {
        perror("Error in opening socket");
        exit(-1);
    }
    server = gethostbyname(hostname);
    if(server==NULL)
    {
        fprintf(stderr,"can't resolve hostname \n");
        exit(2);
    }
    bzero((char *)&serverAddr,sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    bcopy((char *)server->h_addr,(char *)&serverAddr.sin_addr.s_addr,server->h_length);
    serverAddr.sin_port=htons(portno);
    if(connect(socketfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr))<0)
    {
        perror("connect");
        exit(3);
    }
    char buf[] ="Hello there server";
    int bufLen=strlen(buf);
    int arraylen=0;
    int packet=0;
    packet=recv(socketfd,&arraylen,4,0);
    if(arraylen<0)
    {
        perror("error in revieving arraylen\n");
    }
    printf("\nThe arraylen is %d\n",arraylen);
    int a[arraylen];
    int serLen= sizeof(serverAddr);
    int recvLen=0;
    for(int z=0;z<arraylen;z++)
    {
        recvLen=0;
        recvLen=recv(socketfd,&a[z],4,0);
        if(recvLen<0)
        {
            perror("error in recieving");
            exit(5);
        }

    }
    for(int p=0;p<arraylen;p++)
        printf("%d, ",a[p]);
    int sum=0;
    for(int z=0;z<arraylen;z++)
    {
        sum=sum+a[z];
    }
    printf("The sum of array is %d \n",sum);
    int m;
    m=send(socketfd,&sum,sizeof(int),0);
    if(m<0)
    {
        perror("error in sending sum\n");
    }
    close(socketfd);
    return 0;
}

