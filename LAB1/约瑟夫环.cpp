#include<iostream>
#include<fstream>
#include<algorithm> 
#define maxsize 100
using namespace std;

struct node
{
	int data;
	int code;
	struct node *next;		
};

int main(int argc,char *argv[])
{
	ofstream outfile("约瑟夫环结果");
	int n,m,x,i,y=0;//n为人数，m为初始的报数，x代表密码
	node *l,*r,*s,*q;
	q=(node *)malloc(sizeof(node));
	l=(node *)malloc(sizeof(node));
	r=l;
	cout<<"请输入参与游戏的人数："<<endl;
	while(1)
	{
		cin>>n;
		if(n!=0)
		{
			break;
		}	
		else
		{
			cout<<"请重新输入："<<endl;
		}
	} 
	y=n;
	cout<<"请输入每个人拿到的密码："<<endl;
	for(i=1;i<=n;i++)
	{
		cin>>x;
		if(x==0)
		{
			cout<<"数据错误！"<<endl;
			return 0;
		}
		s=(node *)malloc(sizeof(node));
		s->data=i;
		s->code=x;
		r->next=s;
		r=s;	
	} 
	r->next=l->next;
	cout<<"请输入初始的报数："<<endl;
	cin>>m;
	if(m==0)
	{
		cout<<"数据错误！"<<endl;
		return 0;
	}
	s=l->next;
	q=l->next->next;
	for(i=1;i<n-2;i++)
	{
		q=q->next;
	}
	while(s->next!=s)
	{
		if(m==1)
		{
			m=m+y;
		}
		for(i=1;i<m-1;i++)
		{
			s=s->next;
			q=q->next;
		}
		outfile<<s->next->data<<" ";
		y--;//当前人数减一 
		m=s->next->code;
		s->next=s->next->next;
		s=s->next;
		q=q->next;
	}
	outfile<<s->data<<endl;
	outfile.close();
	return 0;
}
