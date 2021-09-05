#include<iostream>
#include<algorithm>
#include<string.h>
#include<math.h>
#include<fstream>
#define maxsize 100
using namespace std;

struct stack 
{
	int data[maxsize];
	int top;
};

void init(stack *&l)
{
	l=(stack *)malloc(sizeof(stack));
	l->top=-1;
}

bool push(stack *&l,int e)
{
	if(l->top==maxsize-1)
	{
		return false;	
	}
	l->top++;
	l->data[l->top]=e;
	return true;
}

bool pop(stack *&l)
{
	if(l->top==-1)
	{
		return false;
	}
	l->top--;
	return true;
}

bool gettop(stack *l,int &e)
{
	if(l->top==-1)
		return false;
	e=l->data[l->top];
}

bool stackempty(stack *l)
{
	return 	(l->top==-1);
} 

bool check(int *qu,int t)
{
	int i;
	for(i=0;i<t;i++)
	{
		if(qu[i]==qu[t]||abs(t-i)==abs(qu[t]-qu[i]))
		{
			return false;
		}
	}
	return true;
}

int main(int argc,char *argv[])
{
	char filename[maxsize];
	int n,cnt=0,row=0;//问题的解的数目，行
	n=atoi(argv[1]);
	strcpy(filename,argv[2]);
	ofstream outfile(filename);
	stack *l;
	init(l);
	int *queen=new int[n];//保存皇后列位置 
	queen[0]=-1;//最开始置为-1
	push(l,0);
	while(!stackempty(l))
	{
		gettop(l,row);
		queen[row]++;//尝试下一列
		if(queen[row]>=n)
		{
			pop(l);	
		}	
		else
		{
			if(check(queen,row))
			{
				if(row==n-1)
				{
					outfile<<++cnt<<endl;
					for(int i=0;i<n;i++)
					{
						outfile<<"("<<i<<","<<queen[i]<<")";
					}	
					outfile<<endl;
				}
				else
				{
					queen[row+1]=-1;
					push(l,row+1);
				}
			}
		}
	} 
	delete []queen;
	return 0;
}
