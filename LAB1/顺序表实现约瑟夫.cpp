#include<iostream>
#include<fstream>
#include<algorithm>
#define maxsize 100
using namespace std;

struct node
{
	int data[maxsize];
	int length;	
}; 

void init(node *&l)
{
	l=(node *)malloc(sizeof(node));
	l->length=0;
}

void creatlist(node *&l,int a[],int n)
{
	int i=0,k=0;
	l=(node *)malloc(sizeof(node));
	while(i<n)
	{
		l->data[k]=i+1;
		i++;
		k++;
	}
	l->length=k;
}

int main(int argc,char *argv[])
{
	ofstream outfile("Լɪ�򻷽��");
	int n,m,a[maxsize],i,j=0,k=1,p=0,q=0;//kΪ��ǰ��λ�� 
	int e; 
	node *l;
	init(l);
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
			cout<<"���������룡"<<endl;
		}
	}
	cout<<"������ÿ�����õ�������:"<<endl;
	for(i=0;i<n;i++)
	{
		cin>>a[i];
		if(a[i]==0)
		{
			cout<<"���ݴ���"<<endl;
			return 0;
		}
	}
	creatlist(l,a,n);
	cout<<"�������ʼ�ı���:"<<endl;
	cin>>m;
	if(m==0)
	{
		cout<<"���ݴ���"<<endl;
		return 0;
	}
	while(l->length!=0)
	{
		k--;
		i=(k+m-1)%(l->length);
		e=l->data[i];
		outfile<<e<<" ";
		m=a[i];
		for(j=i;j<l->length-1;j++)
		{
			l->data[j]=l->data[j+1];
			a[j]=a[j+1];
		}
		l->length--;
		k=i+1;
	}
	outfile.close();
	return 0;
}
