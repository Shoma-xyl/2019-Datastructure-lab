#include<iostream>
#include<fstream>
#include<algorithm>
#define maxsize 100
using namespace std;

struct stack
{
	int data[maxsize];
	int top;	
};

int push(stack *l,int e)
{
	l->data[l->top++]=e;
	return e;
}

int pop(stack *l)
{
	l->top--;
	int e=l->data[l->top];
	return e;
}

int main(int argc,char *argv[])
{
	int v,n,a[maxsize],i;
	int sum;//栈中总的元素的和 
	int z=0;
	stack l;
	v=atoi(argv[1]);
	n=atoi(argv[2]);
	for(i=3;i<(3+n);i++)
	{
		a[z]=atoi(argv[i]);	
		z++;
	}  
	ofstream outfile(argv[n+3]);
	for(i=0;i<n;i++)
	{
		sum=0;
		l.top=0;
		int r,p;//r指针不断移动进行试探，p指针则进行保留作用 
		sum+=a[push(&l,i)];
		r=p=i+1;
		if(sum>v)
		{
			continue;
		}
		else
		{
			while(l.top!=0)
			{
				if(sum<v&&r<n)//当总质量小于容量且没有遍历完毕 
				{
					sum+=a[push(&l,r)];
					r++;
				}
				if(sum>v)
				{
					sum-=a[pop(&l)];
				}
				if(sum==v)
				{
					for(int k=0;k<l.top;k++)
					{
						outfile<<a[l.data[k]]<<" ";
					}
					outfile<<endl;
					sum-=a[pop(&l)];
				}
				if(r==n)
				{
					p=pop(&l);
					if(l.top==0)
					{
						break;
					}
					sum-=a[p];
					p++;
					if(p<n)
					{
						sum+=a[push(&l,p)];
						p++;
						r=p;
					}
					else
					{
						p=pop(&l);
						if(l.top==0)
						{
							break;
						}
						sum-=a[p];
						p++;
						sum+=a[push(&l,p)];
						p++;
						r=p;
					}
				}
			}
		}
	}
	return 0;
}
