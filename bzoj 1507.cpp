#include<iostream>
#include<ext/rope>
#include<cstdio>
using namespace __gnu_cxx;
using namespace std;
const int maxn=1024*1024*3;
int n;
rope <char> rop;
char str[maxn];
int main()
{
	scanf("%d",&n);
	int p=0;
	for(int i=1;i<=n;i++)
	{
		char cmd[20];	scanf("%s",cmd);	int n,k;
		if(cmd[0]=='M')	scanf("%d",&k),p=k;
		if(cmd[0]=='I')
		{
			scanf("%d",&n);	getchar();
			int cur=0;
			while(1)
			{
				char c=getchar();
				if(c!='\n')	str[cur++]=c;
				if(cur==n)	break;
			}
			rop.insert(p,str,n);
		}
		if(cmd[0]=='D')	scanf("%d",&n),rop.erase(p,n);
		if(cmd[0]=='G')	scanf("%d",&n),printf("%s\n",rop.substr(p,n).c_str());
		if(cmd[0]=='P')	p--;
		if(cmd[0]=='N')	p++;
	}	
}
