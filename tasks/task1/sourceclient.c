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
    char buffer[2048];
    printf("Enter numbers with (,) between them\n");
    scanf("%s",buffer);
    int bufferlen=strlen(buffer);
    /*int a[6];
    for(int q=0;q<6;q++)
    {
        printf("Enter the element %d of array\n",q+1);
        scanf("%d",&a[q]);
    }*/
    
    
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
    
    int serLen= sizeof(serverAddr);
    int recvLen=0;
    if(send(socketfd,buffer,bufferlen,0)<0)//data being sent to client side
    {
        perror("error in sending");
        exit(5);
    }
    int final_sum;
    recvLen=recv(socketfd,&final_sum,sizeof(int),0);
    printf("Final sum recieved is %d \n",final_sum);
    close(socketfd);
    return 0;
}

