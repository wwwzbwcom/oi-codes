#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char str[100];
int dyp[100][100];
int vis[100][100];
void dfs(int le,int re)
{
	if(vis[le][re]==1)	return;
	vis[le][re]=1;
	dyp[le][re]=1e9;
	
	if(le>re)	return;
	if(le==re)
	{
		dyp[le][re]=1;
		return;
	}
	if(str[le]==str[re])
	{
		dfs(le,re-1);	dfs(le+1,re);
		dyp[le][re]=min(dyp[le+1][re],dyp[le][re-1]);
	}
	else
	{
		for(int k=le;k<=re-1;k++)
		{
			dfs(le,k);	dfs(k+1,re);
			dyp[le][re]=min(dyp[le][re],dyp[le][k]+dyp[k+1][re]);
		}
	}
}
int main()
{
	scanf("%s",str+1);
	int len=strlen(str+1);
	dfs(1,len);
	printf("%d",dyp[1][len]);
}
