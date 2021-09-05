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
	ofstream outfile("约瑟夫环结果");
	int n,m,a[maxsize],i,j=0,k=1,p=0,q=0;//k为当前的位置 
	int e; 
	node *l;
	init(l);
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
			cout<<"请重新输入！"<<endl;
		}
	}
	cout<<"请输入每个人拿到的密码:"<<endl;
	for(i=0;i<n;i++)
	{
		cin>>a[i];
		if(a[i]==0)
		{
			cout<<"数据错误！"<<endl;
			return 0;
		}
	}
	creatlist(l,a,n);
	cout<<"请输入初始的报数:"<<endl;
	cin>>m;
	if(m==0)
	{
		cout<<"数据错误！"<<endl;
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
