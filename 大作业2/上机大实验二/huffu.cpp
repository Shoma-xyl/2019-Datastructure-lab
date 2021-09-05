#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//ͳ���ַ�Ƶ�ȵĽ��
typedef struct{
	unsigned char huf_char;//��8bitsΪ��Ԫ���޷����ַ�
	unsigned long weight;//ÿ���ַ�����Ƶ��
}TmpNode;

//�����������
typedef struct{
	unsigned char huf_char;//��8bitsΪ��Ԫ���޷����ַ�
	unsigned long weight;//ÿ���ַ�����Ƶ��
	char *code;//�ַ���Ӧ�Ĺ���������
	int parent,lchild,rchild;//˫�׺����Һ���
}HTNode,*HuffmanTree;

//ѡ����С�ʹ�С��������㣬����������������
void Select(HTNode *HT, unsigned int n, int &s1, int &s2)
{
	//����С
	unsigned int i;
	unsigned long min=ULONG_MAX;
	for(i=0;i<n;++i)           
		if(HT[i].parent==0&&HT[i].weight<min)
		{
			min=HT[i].weight;
			s1=i;
		}
		HT[s1].parent=1;//��Ǵ˽���Ҵ�С
	//�Ҵ�С
	min=ULONG_MAX;
	for(i=0;i<n;++i)            
		if(HT[i].parent==0 && HT[i].weight<min)
		{
			min=HT[i].weight;
			s2=i;
		}
} 

//������������
void CreateTree(HTNode *HT,unsigned int char_kinds,unsigned int node_num)
{
	unsigned int i;
	int s1,s2;
	for(i=char_kinds;i<node_num;++i)  
	{ 
		Select(HT,i,s1,s2);//ѡ����С���������,�����µĽڵ�
		HT[s1].parent=HT[s2].parent=i; 
		HT[i].lchild=s1; 
		HT[i].rchild=s2; 
		HT[i].weight=HT[s1].weight+HT[s2].weight; 
	} 
}

//���� 
void HufCode(HTNode *HT,unsigned n,int node_num)
{
	unsigned int i;
	int cur,next,start;
	char *cd=(char *)malloc(node_num*sizeof(char));//�ݴ���룬���256��Ҷ�ӣ����볤�Ȳ�����255
	cd[node_num-1]='\0'; 
	for(i=0;i<n;++i) 
	{
		start=node_num-1;	//������ʱ�ռ�������ʼ��
		//��Ҷ�����������������
		for(cur=i,next=HT[i].parent;next!=0;cur=next,next=HT[next].parent)  
			if(HT[next].lchild==cur) 
				cd[--start]='0';
			else 
				cd[--start]='1';
		HT[i].code=(char *)malloc((node_num-start)*sizeof(char));	//Ϊ��i���ַ����붯̬����洢�ռ� 
		strcpy(HT[i].code,&cd[start]);//���򱣴���뵽�������Ӧ����
	} 
	free(cd);//�ͷű�����ʱ�ռ�
}

//ѹ��
int compress(char *ifname)
{
    char *ofname;
	unsigned int i,j;
	unsigned int char_kinds;//�ַ�����
	unsigned char char_temp;//�ݴ�8bits�ַ�
	unsigned long file_len=0;//�ļ�����
	FILE *infile, *outfile;//��������ļ�
	TmpNode node_temp;
	unsigned int node_num;//�ڵ���
	HuffmanTree huf_tree;
	char code_buf[256]="\0";//������뻺����
	unsigned int code_len;
    //��������ļ�
    bool flag=false;
    short PathSize=strlen(ifname);
    for(short i=PathSize-1;i>=0;i--)
    {
        if(ifname[i]=='\\')
        {
            ofname=new char[PathSize-i+3];
            for(short j=0;i<PathSize;i++,j++)
               ofname[j]=ifname[i+1];
            flag=true;
            break;
        }
    }
    if(flag==false)
    {
        ofname=new char[PathSize+4];
        strcpy(ofname,ifname);
    }
    strcat(ofname,".hf");
	TmpNode *tmp_nodes=(TmpNode *)malloc(256*sizeof(TmpNode));//ͳ��Ƶ��
	//��ʼ���ݴ���
	for(i=0;i<256;++i)
	{
		tmp_nodes[i].weight = 0;
		tmp_nodes[i].huf_char = (unsigned char)i;//�����256���±���256���ַ���Ӧ
	}
	infile=fopen(ifname, "rb");
	if(infile == NULL)// �ж������ļ��Ƿ����
		return -1;
    //��ȡ�ļ����õ��ַ�Ȩ��
	fread((char *)&char_temp,sizeof(unsigned char),1,infile);//����һ���ַ�
	while(!feof(infile))
	{
		++tmp_nodes[char_temp].weight;	//ͳ���±��Ӧ�ַ���Ȩ�أ����������������ʿ���ͳ���ַ�Ƶ��
		++file_len;
		fread((char *)&char_temp, sizeof(unsigned char), 1, infile);//����һ���ַ�
	}
	fclose(infile);
	//����ɾȥȨ��Ϊ���
	for(i=0;i<256-1;++i)           
		for(j=i+1;j<256;++j)
			if(tmp_nodes[i].weight<tmp_nodes[j].weight)
			{
				node_temp=tmp_nodes[i];
				tmp_nodes[i]=tmp_nodes[j];
				tmp_nodes[j]=node_temp;
			}
	//ͳ��ʵ�ʵ��ַ�����(���ִ�����Ϊ0��
	for(i=0;i<256;++i)
		if(tmp_nodes[i].weight==0) 
			break;
	char_kinds=i;
    if(char_kinds<=20)
        printf("�ļ�̫С��");
	if(char_kinds==1)
	{
        printf("�ļ�̫С��");
		outfile=fopen(ofname, "wb");//��ѹ�������ɵ��ļ�
		fwrite((char *)&char_kinds,sizeof(unsigned int),1,outfile);//д���ַ�����
		fwrite((char *)&tmp_nodes[0].huf_char,sizeof(unsigned char),1,outfile);//д��Ψһ���ַ�
		fwrite((char *)&tmp_nodes[0].weight,sizeof(unsigned long),1,outfile);//д���ַ�Ƶ�ȣ�Ҳ�����ļ�����
		free(tmp_nodes);
		fclose(outfile);
	}
	else
	{
		node_num=2*char_kinds-1;//�������������������� 
		huf_tree=(HTNode *)malloc(node_num*sizeof(HTNode));	 
		//��ʼ��ǰchar_kinds�����
		for(i=0;i<char_kinds;++i) 
		{ 
			//���ݴ�����ַ���Ƶ�ȿ����������
			huf_tree[i].huf_char=tmp_nodes[i].huf_char; 
			huf_tree[i].weight=tmp_nodes[i].weight;
			huf_tree[i].parent=0; 
		}	
		free(tmp_nodes); //�ͷ��ַ�Ƶ��ͳ�Ƶ��ݴ���
		//��ʼ����node_num-char_kins�����
		for(;i<node_num;++i) 
			huf_tree[i].parent=0; 
		CreateTree(huf_tree,char_kinds,node_num);//������������
        HufCode(huf_tree,char_kinds,node_num);	
		//���ɹ���������
		//д���ַ�����ӦȨ�أ�����ѹʱ�ؽ���������
		outfile = fopen(ofname,"wb");//��ѹ�������ɵ��ļ�
		fwrite((char *)&char_kinds,sizeof(unsigned int),1,outfile);//д���ַ�����
		for(i=0;i<char_kinds;++i)
		{
			fwrite((char *)&huf_tree[i].huf_char,sizeof(unsigned char),1,outfile);//д���ַ�
			fwrite((char *)&huf_tree[i].weight,sizeof(unsigned long),1,outfile);//д���ַ���ӦȨ��
		}
		//�������ַ���Ȩ����Ϣ����д���ļ����Ⱥ��ַ�����
		fwrite((char *)&file_len,sizeof(unsigned long),1,outfile);//д���ļ�����
		infile = fopen(ifname,"rb");//�Զ�������ʽ�򿪴�ѹ�����ļ�
		fread((char *)&char_temp,sizeof(unsigned char), 1, infile);//ÿ�ζ�ȡ8bits
		while(!feof(infile))//�ж��ļ��Ƿ���� 
		{
			//ƥ���ַ���Ӧ����
			for(i=0;i<char_kinds;++i)
				if(char_temp == huf_tree[i].huf_char)
					strcat(code_buf,huf_tree[i].code);
			while(strlen(code_buf)>=8)
			{
				char_temp='\0';//����ַ��ݴ�ռ䣬��Ϊ�ݴ��ַ���Ӧ����
				for(i=0;i<8;++i)
				{
					char_temp<<=1;//����һλ��Ϊ��һ��bit�ڳ�λ��
					if(code_buf[i]=='1')
						char_temp|=1;//�����λ1
				}
				fwrite((char *)&char_temp,sizeof(unsigned char),1,outfile);//���ֽڶ�Ӧ��������ļ�
				strcpy(code_buf,code_buf+8);//���뻺��ȥ���Ѵ����ǰ��λ
			}
			fread((char *)&char_temp,sizeof(unsigned char),1,infile);//ÿ�ζ�ȡ8bits
		}
		//���������8bits����
		code_len=strlen(code_buf);
		if(code_len>0)
		{
			char_temp='\0';//����		
			for(i=0;i<code_len;++i)
			{
				char_temp<<= 1;		
				if(code_buf[i]=='1')
					char_temp|=1;//���λ��1
			}
			char_temp<<=8-code_len;//�������ֶδ�β���Ƶ��ֽڵĸ�λ
			fwrite((char *)&char_temp,sizeof(unsigned char),1,outfile);//�������һ���ֽ�
		}
		//�ر��ļ�
		fclose(infile);
		fclose(outfile);
		//�ͷ��ڴ�
		for(i=0;i<char_kinds;++i)
			free(huf_tree[i].code);
		free(huf_tree);
	}
}

// ��ѹ
int extract(char *ifname)
{
	unsigned int i;
	unsigned long file_len;
	unsigned long writen_len = 0;//�����ļ�д�볤��
	FILE *infile, *outfile;
	unsigned int char_kinds;//�洢�ַ�����
	unsigned int node_num;
	HuffmanTree huf_tree;
	unsigned char code_temp;//�ݴ�8bits����
	unsigned int root;//��
	infile=fopen(ifname, "rb");//�Զ����Ʒ�ʽ��ѹ���ļ�
	if (infile==NULL)//�ж������ļ��Ƿ����
		return -1;
    int len=strlen(ifname);
    char *ofname=new char[len-2];
    for(int i=0;i<len-3;i++)
        ofname[i]=ifname[i];
        ofname[len-3]='\0';//��ѹ�ļ���
	// ��ȡѹ���ļ�ǰ�˵��ַ�����Ӧ���룬�����ؽ���������
	fread((char *)&char_kinds,sizeof(unsigned int),1,infile);//��ȡ�ַ�������
	if (char_kinds==1)
	{
		fread((char *)&code_temp,sizeof(unsigned char),1,infile);//��ȡΨһ���ַ�
		fread((char *)&file_len,sizeof(unsigned long),1,infile);//��ȡ�ļ�����
		outfile = fopen(ofname,"wb");//��ѹ�������ɵ��ļ�
		while (file_len--)
			fwrite((char *)&code_temp, sizeof(unsigned char), 1, outfile);	
		fclose(infile);
		fclose(outfile);
	}
	else
	{
		node_num=2*char_kinds-1;//�����ַ������������㽨������������������ 
		huf_tree = (HTNode *)malloc(node_num*sizeof(HTNode));//��̬��������������ռ�
		//��ȡ�ַ�����ӦȨ�أ�������������ڵ�
		for(i=0;i<char_kinds;++i)     
		{
			fread((char *)&huf_tree[i].huf_char,sizeof(unsigned char),1,infile);//�����ַ�
			fread((char *)&huf_tree[i].weight,sizeof(unsigned long),1,infile);//�����ַ���ӦȨ��
			huf_tree[i].parent=0;
		}
		//��ʼ��
		for(;i<node_num;++i) 
			huf_tree[i].parent=0;
		CreateTree(huf_tree,char_kinds,node_num);//�ؽ���������
		//��ȡ�ļ����Ⱥͱ���,���н���
		fread((char *)&file_len,sizeof(unsigned long),1,infile);//�����ļ�����
		outfile=fopen(ofname, "wb");//��ѹ�������ɵ��ļ�
		root=node_num-1;
		while(1)
		{
			fread((char *)&code_temp,sizeof(unsigned char),1,infile);//��ȡһ���ַ����ȵı���
			//�����ȡ��һ���ַ����ȵı��루ͨ��Ϊ8λ��
			for(i=0;i<8;++i)
			{
				// �ɸ�����ֱ��Ҷ�ڵ�����ƥ������Ӧ�ַ�
				if(code_temp&128)//���code_temp��λ��ֵ
					root=huf_tree[root].rchild;
				else
					root=huf_tree[root].lchild;

				if(root<char_kinds)
				{
					fwrite((char *)&huf_tree[root].huf_char,sizeof(unsigned char),1,outfile);
					++writen_len;
					if (writen_len==file_len) break;//�����ļ�����
					root=node_num-1;//��λ��
				}
				code_temp<<=1;// �����뻺�����һλ�Ƶ����λ
			}
			if (writen_len==file_len) break;// �����ļ�����
		}
		// �ر��ļ�
		fclose(infile);
		fclose(outfile);
		// �ͷ��ڴ�
		free(huf_tree);
	}
}//extract()
 
int main()
{
	while(1)
	{
		int opt,flag=0;//ÿ�ν���ѭ����Ҫ��ʼ��flagΪ0
		char ifname[256],ofname[256];//������������ļ���
		//������ѡ��������͵����ִ��ţ�1��ѹ����2����ѹ��3���˳�
		printf("���������:\n 1:ѹ�� \n 2: ��ѹ��\n 3: �˳�\n");
		scanf("%d", &opt);
		if (opt==3)
			break;
		else
		{
			printf("�����ļ���: ");
            getchar();
			fflush(stdin);//��ձ�׼����������ֹ����gets������ȡ�ļ���
			gets(ifname);
		}
		switch(opt)
		{
		case 1: printf("ѹ����\n");
				flag = compress(ifname);//ѹ��������ֵ�����ж��Ƿ��ļ���������
				break;		
		case 2: printf("��ѹ����\n");
				flag = extract(ifname);//��ѹ������ֵ�����ж��Ƿ��ļ���������
				break;		
		}
		if (flag == -1)
			printf("�ļ� \"%s\" ������\n", ifname);//�����־Ϊ��-1���������ļ�������
		else
			printf("�������\n");//�������
	}
	return 0;
}
