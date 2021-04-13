#include<cstdio>
#include<cstring>
using namespace std;
int n,m;
char s[1000000];
char chan[1000000][2];
char idx[500];
void init()
{
	for(char i='a';i<='z';i++)
	{
		char cur=i;
		for(int j=1;j<=m;j++)
		{
			if(chan[j][0]==cur)	cur=chan[j][1];
			else if(chan[j][1]==cur)	cur=chan[j][0];
		}
		idx[i]=cur;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",s);
	for(int i=1;i<=m;i++)	scanf("%s %s",&chan[i][0],&chan[i][1]);
	init();
	int len=strlen(s);
	for(int i=0;i<len;i++)	putchar(idx[s[i]]);
}
