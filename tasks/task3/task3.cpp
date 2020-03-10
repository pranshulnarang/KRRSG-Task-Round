#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include<bits/stdc++.h>
#include<math.h>
#include<time.h>
#include<fstream>
using namespace std;
using namespace cv;
#define EPSILON 30.0
#define RADIUS 90.0
struct node
{
	Point point;
	int cost;
	struct node* parent;
};
float distance(Point p1,Point p2)
{
	return(sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)));		
}
bool white_check(Point p1,Point p2,Mat img)
{
	LineIterator it(img,p1,p2,8);
	//LineIterator it2=it;
	int i=0;
	Point p3;
	Vec3b val;
	for(i=0;i<it.count;i++,++it)
	{
		val=img.at<Vec3b>(it.pos());
		if(val[0]>=200&&val[1]>=200&&val[2]>=200)
		{
			return(true);
		}
		else
		{
			continue;
		}
	}
	if(i==it.count)
	{
		return(false);
	}
}
int red_check(Point p1,Point p2,Mat img)
{
	LineIterator it(img,p1,p2,8);
	int i=0;
	Point p3;
	Vec3b val;
	for(i=0;i<it.count;i++,++it)
	{
		val=img.at<Vec3b>(it.pos());
		if(val[0]<20&&val[1]<20&&val[2]>=230)
		{
			return(1);
		}
		else
		{
			continue;
		}
	}
	if(i==it.count)
	{
		return(0);
	}
}
	
Point step_from_to(Point p1,Point p2)
{
	float theta;
	if(distance(p1,p2)<EPSILON)
		return p2;
	else
	{
		theta=atan((float)(p2.y-p1.y)/(p2.x-p1.x));
		Point p3;
		p3.x=p1.x+(int)EPSILON*cos(theta);
		p3.y=p1.y+(int)EPSILON*sin(theta);
		return(p3);
	}
}

Point step_from_to1(Point p1,Point p2)
{
	
	float theta;
	if(distance(p1,p2)<EPSILON)
		return p2;
	else
	{
		theta=atan((float)(p2.y-p1.y)/(p2.x-p1.x));
		Point p3;
		p3.x=p1.x-(int)EPSILON*cos(theta);
		p3.y=p1.y-(int)EPSILON*sin(theta);
		return(p3);
	}
}
void search_circle(int number_nodes,struct node p4[],struct node *a,struct node *b,Mat img)//a is the new node to be created and b is the nearest node to a 
{
	int i=0;
	struct node *min_cost_node=b;
	int index;
	while(b->parent!=NULL)
	{	
		if(distance((b->parent)->point,a->point)<RADIUS&&(!white_check((b->parent)->point,a->point,img))&&(b->parent)->cost+distance((b->parent)->point,a->point)<=min_cost_node->cost+distance(min_cost_node->point,a->point))
		{
			min_cost_node=b->parent;
			//cout<<"success"<<endl;
			b=b->parent;
		}
		i++;
		if(i>200)
			break;
		//if(b->parent==&p4[0])
			//cout<<"done"<<endl;
		//cout<<i<<endl;
	}
	a->parent=min_cost_node;
	a->cost=(min_cost_node)->cost+distance(min_cost_node->point,a->point);
	//cout<<a->cost<<endl;
}
int main()
{
	srand(time(NULL));
	RNG rng( 0xFFFFFFFF );
	Mat img=imread("project.jpeg",1);
	int rows=img.rows;
	int cols=img.cols;
	Mat a(rows,cols,CV_8UC3,Scalar(255,255,255));
	for(int k=0;k<rows;k++)
	{
		for(int l=0;l<cols;l++)
		{
			a.at<Vec3b>(k,l)[0]=img.at<Vec3b>(k,l)[0];
			a.at<Vec3b>(k,l)[1]=img.at<Vec3b>(k,l)[1];
			a.at<Vec3b>(k,l)[2]=img.at<Vec3b>(k,l)[2];
		}
	}
	node p4[60000];
	node p5[60000];
	namedWindow("output",0);
	namedWindow("outputarray",0);
	p4[0].point.x=45;
	p4[0].point.y=35;
	p4[0].cost=0;
	p4[0].parent=NULL;
	p5[0].point.x=461;
	p5[0].point.y=475;
	p5[0].cost=0;
	p5[0].parent=NULL;
	node random;
	node random1;
	node nn,nn1;
	nn.point.x=p4[0].point.x;
	nn.point.y=p4[0].point.y;
	nn1.point.x=p5[0].point.x;
	nn1.point.y=p5[0].point.y;
	int j=0,j1=0; int index,index1;
	int t=0;
	int x2=0;
	int x1=0;
	int i=0,i1=0;
    node *p;
    node *p1;
	cout<<"The number of rows "<<rows<<"the number of cols is "<<cols<<endl;
	for(i=0,i1=0;i<10000&&i1<10000;i++,i1++)
	{
		/*waitKey(100);
		imshow("output",img);
		imshow("outputarray",a);*/
		nn.point.x=p4[0].point.x;
		nn.point.y=p4[0].point.y; 
		nn1.point.x=p5[0].point.x;
		nn1.point.y=p5[0].point.y;
		index=0;
		index1=0;
		random.point.x=rng.uniform(0,cols);
		random.point.y=rng.uniform(0,rows);
		random1.point.x=rng.uniform(0,cols);
		random1.point.y=rng.uniform(0,rows);
    	//cout << random.point.x << "  " << random.point.y << endl;
		for(j=0;j<i+1;j++)
		{
			if(distance(p4[j].point,random.point)<=distance(nn.point,random.point))
				{
					nn.point.x=p4[j].point.x;
					nn.point.y=p4[j].point.y;
					index=j;
				}
	
		}	
		p4[i+1].point=step_from_to(nn.point,random.point);
		//cout<<"x coordinate"<<p4[i+1].point.x<<" y coordinate  "<<p4[i+1].point.y<<endl;
		if(white_check(p4[i+1].point,nn.point,img))
		{
			i--;
			//cout<<"rejected"<<endl;
			continue;
		}
			
		else
		{
			p4[i+1].cost=p4[index].cost+distance(p4[i+1].point,nn.point);
			search_circle(i,p4,&p4[i+1],&p4[index],img);
			line(a,nn.point,p4[i+1].point,200,1,8,0);
			//cout<<"hey1"<<endl;
		}
		for(j1=0;j1<i1+1;j1++)
		{
			if(distance(p5[j1].point,random1.point)<=distance(nn1.point,random1.point))
				{
					nn1.point.x=p5[j1].point.x;
					nn1.point.y=p5[j1].point.y;
					index1=j1;
				}
	
		}	
		p5[i1+1].point=step_from_to1(nn1.point,random1.point);
		//cout<<"x coordinate"<<p4[i+1].point.x<<" y coordinate  "<<p4[i+1].point.y<<endl;
		if(white_check(p5[i1+1].point,nn1.point,img))
		{
			i1--;
			//cout<<"rejected"<<endl;
			continue;
		}
			
		else
		{
			p5[i1+1].cost=p5[index1].cost+distance(p5[i1+1].point,nn1.point);
			search_circle(i1,p5,&p5[i1+1],&p5[index1],img);
			line(a,nn1.point,p5[i1+1].point,200,1,8,0);
			//cout<<"hey1"<<endl;
		}
		/*if(red_check(p4[i+1].point,(p4[i+1].parent)->point,img))
		{
			
			p=&p4[i+1];
			break;*/
		 	/*
			while(p->parent!=NULL)
			{
				
				line(a,p->point,(p->parent)->point,Scalar(255,255,255),1,8,0);
				p=p->parent;
				//cout<<"Parent joined"<<endl;
				if(p->parent==NULL)
				{
					//cout<<"NULL point obtained"<<endl;
				}
				
			}*/
		int flag=0;
		for(x1=0;x1<i+1;x1++)
		{
			for(x2=0;x2<i1+1;x2++)
			{
				if(distance(p4[x1].point,p5[x2].point)<EPSILON)
				{
					p=&p4[x1];
					p1=&p5[x2];
					//cout<<x1<<"  "<<x2<<endl;
					flag=1;
					break;
				}
			}
			if (flag==1)
				break;
		}
		if(flag == 1)
			{
				//cout<<"abc "<<p4[x1+1].parent->point.x<<endl;
				//cout<<"done"<<endl;
				//cout<<"abc"<<p4[x1].parent->point.x<<endl;
				line(a,p4[x1].point,p5[x2].point,Scalar(0,0,255),1,8,0);
				break;
			}

		
	}
	float array1[500][2],array2[500][2];
	int l1=0,l2=0;
        //RETRACE LOOP
	while(p->parent!=NULL)
	{
				
		line(a,p->point,(p->parent)->point,Scalar(0,0,255),1,8,0);
		array1[l1][0]=(float)(p->point.x)*0.0214;
		array1[l1][1]=(float)(512-p->point.y)*0.0214;
		l1++;
		p=p->parent;
		//cout<<"Parent joined"<<endl;
				
	}
	while(p1->parent!=NULL)
	{
				
		line(a,p1->point,(p1->parent)->point,Scalar(0,0,255),1,8,0);
		array2[l2][0]=(float)(p1->point.x)*0.0214;
		array2[l2][1]=(float)(512-p1->point.y)*0.0214;
		l2++;
		p1=p1->parent;
		//cout<<"Parent joined"<<endl;
	}
	array1[l1][0]=(float)p->point.x*0.0214;
	array1[l1][1]=(float)(512-p->point.y)*0.0214;
	array2[l2][0]=(float)p1->point.x*0.0214;
	array2[l2][1]=(512-p1->point.y)*0.0214;
	ofstream fout;
	fout.open("ABC.txt");
	//cout<<"Hello"<<endl;
	int k;
	for(k=0;k<l1+1;k++)
	{
		cout<<array1[k][0]<<"  "<<array1[k][1]<<endl;
	}
	int h;
	for(h=l1;h>=0;h--)
	{
		fout<<array1[h][0]<<" "<<array1[h][1]<<endl;
	}
	for(h=0;h<=l2;h++)
	{
		fout<<array2[h][0]<<" "<<array2[h][1]<<endl;
	}


        //ENDS
	
	fout.close();
	imshow("output",img);
	imshow("outputarray",a);
	waitKey(0);

}
