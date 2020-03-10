#include <iostream>
#include <time.h>
#include <math.h>
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
#define MAX 20
#define CALC 40
char buffer[50];

using namespace std;

int enter_floor,exit_floor;
char state;
void input(int *arg)
{
  int newsocket=*arg;
  int recvlen;
  recvlen=recv(newsocket,buffer,sizeof(buffer),0);
  cout<<"recvlen = "<<recvlen<<endl;
  buffer[recvlen]='\0';
  //printf("%d\n\n",recvlen);
  if(recvlen<0);
  {
  	perror("error in receiving");
  }
  enter_floor=buffer[0]-'0';
  state=buffer[1];
  exit_floor=buffer[2]-'0';
}

int nearest(int enter,int pos_lift1,int pos_lift2)
{
	if(abs(pos_lift1-enter)<abs(pos_lift2-enter))
		return 1;
	else
		return 2;
}

class Lift {
public:
	char state;
	int current_pos, initial_pos, next_stop;
	int in[MAX], out[MAX];
	char tr[MAX];
};

class System {
public:
	Lift lift1, lift2;

	//System Properties:
	int max_floor, min_floor;

	//Transition functions:-
	void transition1(int* curpos, int enter, int exit)
	{
		int* p = curpos;
		int i;
		if (*curpos != enter)
		{
			cout << *curpos << " ---> "<<enter<<"--->"<<exit<<endl;

		}
		else
		{
			cout<<*curpos<<"--->"<<exit<<endl;
		}	

		*p = exit;

	}

	void transition2(int* curpos, int enter, int exit)
	{
		int* p = curpos;
		int i;
		if (*curpos != enter)
		{
			cout << *curpos << " ---> "<<enter<<"--->"<<exit<<endl;

		}
		else
		{
			cout<<*curpos<<"--->"<<exit<<endl;
		}	

		*p = exit;
		
	}


};


int main(int argc,char *argv[])
{
	/*********************Socket Creation ****************/
	struct sockaddr_in serverAddr;
	int socketfd;                      //file descriptor for socket id
	if(argc<2)                         //if portno. is not provided as an argument then exit(-1)
	{
		fprintf(stderr,"use %s <port>\n",argv[0]);
		exit(-1);
	}

	int portno =atoi(argv[1]);                                                    //using atoi to read argument as an integer
	socketfd = socket(AF_INET,SOCK_STREAM,0);                                    //using IPv4 connection and TCP protocol
	if(!socketfd)                                                               //socketfd returns 0 if any error in creating socket
	{
		perror("Error in opening socket");
		exit(-1);
	}
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=htonl(INADDR_ANY);                                //use this to specify IP of the server or use a local address for tranferring of data
	serverAddr.sin_port=htons(portno);


	if(bind(socketfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr))<0)       //binding of socketfd to the port
	{
		perror("failed to bind");
		exit(4);
	}
	if(listen(socketfd,50))//50 specifies the maximum no. of backlog connections
	{
		perror("error in listen ");
		exit(2);
	}
	int optval=1;
	setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,(const void *)&optval,sizeof(int));  // unknown function
	struct sockaddr_in clientAddr;
	socklen_t cliLen=sizeof(clientAddr);
    
    
	System sys;
	cout<<"Enter the uppermost floor of the hotel: "<<endl;
	cin>>sys.max_floor;
	cout<<"Enter the minimum floor of the hotel(can be negative)"<<endl;
	cin>>sys.min_floor;
	cout<<"current floor of the lift 1"<<endl;
	cin>>sys.lift1.current_pos;
	cout<<"current floor of the lift 2"<<endl;
	cin>>sys.lift2.current_pos;
	int newSocket1=accept(socketfd,(struct sockaddr *)&clientAddr,&cliLen);
	if(newSocket1<0)
	{
		perror("Error in accept");
		exit(6);
	}
	while(1)
	{
		input(&newSocket1);
		cout<<enter_floor<<"  "<<exit_floor<<endl;
		if(nearest(enter_floor,sys.lift1.current_pos,sys.lift2.current_pos)==1)
		{
			cout<<"lift1 movement"<<endl;
			sys.transition1(&sys.lift1.current_pos,enter_floor,exit_floor);

		}
		else
		{
			cout<<"lift2 movement"<<endl;
			sys.transition2(&sys.lift2.current_pos,enter_floor,exit_floor);
		}
	}
	

	
}
