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
	ofstream outfile("Լɪ�򻷽��");
	int n,m,x,i,y=0;//nΪ������mΪ��ʼ�ı�����x��������
	node *l,*r,*s,*q;
	q=(node *)malloc(sizeof(node));
	l=(node *)malloc(sizeof(node));
	r=l;
	cout<<"�����������Ϸ��������"<<endl;
	while(1)
	{
		cin>>n;
		if(n!=0)
		{
			break;
		}	
		else
		{
			cout<<"���������룺"<<endl;
		}
	} 
	y=n;
	cout<<"������ÿ�����õ������룺"<<endl;
	for(i=1;i<=n;i++)
	{
		cin>>x;
		if(x==0)
		{
			cout<<"���ݴ���"<<endl;
			return 0;
		}
		s=(node *)malloc(sizeof(node));
		s->data=i;
		s->code=x;
		r->next=s;
		r=s;	
	} 
	r->next=l->next;
	cout<<"�������ʼ�ı�����"<<endl;
	cin>>m;
	if(m==0)
	{
		cout<<"���ݴ���"<<endl;
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
		y--;//��ǰ������һ 
		m=s->next->code;
		s->next=s->next->next;
		s=s->next;
		q=q->next;
	}
	outfile<<s->data<<endl;
	outfile.close();
	return 0;
}
