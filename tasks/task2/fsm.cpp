#include<iostream>
#include<string.h>
#include<time.h>
#define MAX_ARRAY 20
#define CALC 40
using namespace std;

class Lift{
	public:
		char state;
		int current_pos,initial_pos,destination_pos;
		int up[MAX_ARRAY],down[MAX_ARRAY];
		int sortin[MAX_ARRAY],sortout[MAX_ARRAY];
		char sort_direction[MAX_ARRAY];
	
};
class system{
public:
	Lift lift1,lift2;
	int maximum_floor,minimum_floor;
	Lift liftup,liftdown;
	void transitionup(int* current_pos, int in, char direction, int out)
	{
		int* p = current_pos;
		int i;
		if (*current_pos != in)
			std :: cout << in << " ---> ";
		*p = out;

	}
	void transitiondown(int* current_pos, int in, char direction, int out)
		{
			int* p = current_pos;
			int i;
			if (*current_pos != in)
				cout << in << " ---> ";
			*p = out;
			
		}	
};


int main()
{
	system sys;
	cout<<"Enter the uppermost floor of the hotel"<<endl;
	cin>>sys.maximum_floor;
	cout<<"Enter the minimum floor of the hotel(can be negative)"<<endl;
	cin>>sys.minimum_floor;
	cout<<"current floor of the lift 1"<<endl;
	cin>>sys.lift1.current_pos;
	cout<<"current floor of the lift 2"<<endl;
	cin>>sys.lift2.current_pos;
	if (sys.lift1.current_pos>sys.lift2.current_pos)
	{
		sys.liftup.current_pos=sys.lift1.current_pos;
		sys.liftdown.current_pos=sys.lift2.current_pos;
	}
	else
	{
		sys.liftup.current_pos=sys.lift2.current_pos;
		sys.liftdown.current_pos=sys.lift1.current_pos;

	}
	int entry[MAX_ARRAY],exit[MAX_ARRAY];char direction[MAX_ARRAY];
	//enter 000 to stop
	int i=0;
	while(1)
	{
		cout<<"Enter data in the format example 1 U 6"<<endl;
		cin>>entry[i]>>direction[i]>>exit[i];
		if(direction[i]=='0')
		{
			break;
		}
		else
			i++;
	}
	int num_entries=i;
	//..............................dividing tasks between the two lifts (up and down)...........................................


	int fl1=0,fl2=0,j,fl3=0,fl4=0;
	for(j=0;j<num_entries;j++)
	{
		if((entry[j]>sys.liftup.current_pos&&direction[j]=='U'))
		{
			sys.liftup.up[fl1++]=entry[j];
			sys.liftup.up[fl1++]=exit[j];
		}
		else if(entry[j]>sys.liftdown.current_pos&&direction[j]=='D')
		{
			sys.liftup.down[fl2++]=entry[j];
			sys.liftup.down[fl2++]=exit[j];
		}
		else if(entry[j]<sys.liftdown.current_pos&&direction[j]=='D')
		{
			sys.liftdown.down[fl3++]=entry[j];
			sys.liftdown.down[fl3++]=exit[j];
		}
		else
		{
			sys.liftdown.up[fl4++]=entry[j];
			sys.liftdown.up[fl4++]=exit[j];
		}
	}
	//.........................now sorting each array so as to get the required path..................................

	int s=0,p=0;
	int temp;
	for(s=0;s<fl1-1;s++)
	{
		for(p=0;p<fl1-1;p++)
		{
			if(sys.liftup.up[p]>=sys.liftup.up[p+1])
			{
				temp=sys.liftup.up[p];
				sys.liftup.up[p]=sys.liftup.up[p+1];
				sys.liftup.up[p+1]=temp;
			}
		}
	}
	for(s=0;s<fl2-1;s++)
	{
		for(p=0;p<fl2-1;p++)
		{
			if(sys.liftup.down[p]<=sys.liftup.down[p+1])
			{
				temp=sys.liftup.down[p];
				sys.liftup.down[p]=sys.liftup.down[p+1];
				sys.liftup.down[p+1]=temp;
			}
		}
	}
	for(s=0;s<fl3-1;s++)
	{
		for(p=0;p<fl3-1;p++)
		{
			if(sys.liftdown.down[p]<=sys.liftdown.down[p+1])
			{
				temp=sys.liftdown.down[p];
				sys.liftdown.down[p]=sys.liftdown.down[p+1];
				sys.liftdown.down[p+1]=temp;
			}
		}
	}
	for(s=0;s<fl4-1;s++)
	{
		for(p=0;p<fl4-1;p++)
		{
			if(sys.liftdown.up[p]>=sys.liftdown.up[p+1])
			{
				temp=sys.liftdown.up[p];
				sys.liftdown.up[p]=sys.liftdown.up[p+1];
				sys.liftdown.up[p+1]=temp;
			}
		}
	}
	int c=0;
	for(s=0;s<fl1;)
	{
		sys.liftup.sortin[c]=sys.liftup.up[s];
		s++;
		sys.liftup.sortout[c]=sys.liftup.up[s];
		s++;
		sys.liftup.sort_direction[c]='U';
		c++;
	}

	for(s=0;s<fl2;)
	{
		sys.liftup.sortin[c]=sys.liftup.down[s];
		s++;
		sys.liftup.sortout[c]=sys.liftup.down[s];
		s++;
		sys.liftup.sort_direction[c]='D';
		c++;
	}
	/*for(int z=0;z<(fl1+fl2)/2;z++)
	{
		cout<<sys.liftup.sortin[z]<<"---->"<<sys.liftup.sortout[z]<<"------>";
	}*/
	c=0;
	for(s=0;s<fl3;)
	{
		sys.liftdown.sortin[c]=sys.liftdown.down[s];
		s++;
		sys.liftdown.sortout[c]=sys.liftdown.down[s];
		s++;
		sys.liftdown.sort_direction[c]='D';
		c++;
	}
	for(s=0;s<fl4;)
	{
		sys.liftdown.sortin[c]=sys.liftdown.up[s];
		s++;
		sys.liftdown.sortout[c]=sys.liftdown.up[s];
		s++;
		sys.liftdown.sort_direction[c]='U';
		c++;
	}
	cout<<".............................Path for lift up..................................."<<endl;

	sys.liftup.state = 'R'; sys.liftup.sort_direction[(fl1+fl2)/2]='R';

	for(s=0;s<(fl1+fl2)/2;)
	{
		switch (sys.liftup.state)
		{
		case 'U':
			sys.transitionup(&sys.liftup.current_pos, sys.liftup.sortin[s], sys.liftup.sort_direction[s], sys.liftup.sortout[s]);
			sys.liftup.state = 'R';
			s++;
			break;

		case 'D':
			sys.transitiondown(&sys.liftup.current_pos, sys.liftup.sortin[s], sys.liftup.sort_direction[s], sys.liftup.sortout[s]);
			sys.liftup.state = 'R';
			s++;
			break;


		case 'R':

			cout << sys.liftup.current_pos << " ---> ";
			switch (sys.liftup.sort_direction[s])
			{
			case 'U': sys.liftup.state = 'U';
				break;
			case 'D': sys.liftup.state = 'D';
				break;
			case 'R': sys.liftup.state = 'R';
				s++;
				break;
			}
			break;

		default:
			cout << "INVALID INPUT." << endl;
		}
	}
	cout<<"    "<<endl;
	cout<<"................................Path for lift down............................"<<endl;
	sys.liftdown.state = 'R'; sys.liftdown.sort_direction[(fl3+fl4)/2]='R';
	for(s=0;s<(fl3+fl4)/2;)
	{
		switch (sys.liftdown.state)
		{
		case 'U':
			sys.transitionup(&sys.liftdown.current_pos, sys.liftdown.sortin[s], sys.liftdown.sort_direction[s], sys.liftdown.sortout[s]);
			sys.liftdown.state = 'R';
			s++;
			break;

		case 'D':
			sys.transitiondown(&sys.liftdown.current_pos, sys.liftdown.sortin[s], sys.liftdown.sort_direction[s], sys.liftdown.sortout[s]);
			sys.liftdown.state = 'R';
			s++;
			break;


		case 'R':

			cout << sys.liftdown.current_pos << " ---> ";
			switch (sys.liftdown.sort_direction[s])
			{
			case 'U': sys.liftdown.state = 'U';
				break;
			case 'D': sys.liftdown.state = 'D';
				break;
			case 'R': sys.liftdown.state = 'R';
				s++;
				break;
			}
			break;

		default:
			cout << "INVALID INPUT." << endl;
		}
	}

	cout<<"        "<<endl;
	return 0;




}