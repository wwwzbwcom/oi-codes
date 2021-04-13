#include<iostream>
#include<cstring>
using namespace std;
char str[1100];
int len;
int mul[1100];
int fla[1100];
int ten[]={1e0,1e1,1e2,1e3,1e4,1e5,1e6,1e7,1e8,1e9};
int idx[]={-1,1};
int dec[][10]={{},{},{},{},{},{},{},{1},{6,9},{}};
int sel[][10]={{6,9},{},{3}}
int inc[][10]={};
int con,flag,cnt;
int sum;
int main()
{
	cin>>str;	len=strlen(str);
	con=0;	flag=1;
	for(int i=0;;i++)
	{
	//	cout<<i<<endl;
		len=i;
		if('0'<=str[i]&&str[i]<='9')	cnt++;
		else
		{
			if(cnt!=0)	for(int j=i-cnt+1;j<i;j++)	mul[j]=ten[i-j-1],fla[j]=flag; 
			cnt=0;
			if(str[i]=='#')	break;
			if(str[i]=='=')	con=1;
			if(str[i]=='+')	flag=1;
			if(str[i]=='-')	flag=0;
			flag^=con;
		}		
	}
	for(int i=0;i<len;i++)
		for(int j=0;j<len;j++)
			if('0'<=str[i]&&str[i]<='9'&&'0'<=str[j]&&str[j]<='9')
			{
				if()
			}
	cout<<sum<<endl;
}
