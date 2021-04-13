#include<cstdio>
#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
const int maxn=4e5+100;
struct Edge
{
	int v,c;
	int nxt;
}e[maxn];
int pre[maxn],en=0;
int t,n,m;
int ond[maxn],ind[maxn];
int vis[maxn];
int ans[maxn],an;
void addedge(int u,int v)
{
	e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
}
void dfs(int u)
{
	vis[u]=1;
	for(int i=pre[u];i!=-1;i=pre[u])
	{
		while(i!=-1&&e[i].c==1)	i=e[i].nxt;
		if(i==-1)	break;
		int v=e[i].v;
		e[i].c=1;
		if(t==1)	e[i^1].c=1;
		pre[u]=e[i].nxt;
		dfs(v);
		ans[an++]=i;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	memset(pre,-1,sizeof pre);
	scanf("%d",&t);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		if(t==1)	addedge(u,v),addedge(v,u),ond[u]++,ind[v]++; 
		else	addedge(u,v),ond[u]++,ind[v]++;
	}
	int flag=1;
	if(t==1)
	{
		for(int i=1;i<=n;i++)	if((ind[i]+ond[i])%2==1)	flag=0;
	}
	else
	{
		for(int i=1;i<=n;i++)	if(ind[i]!=ond[i])	flag=0;
	}
	if(flag==0)
	{
		printf("NO\n");
		return 0;
	}
	for(int i=1;i<=n;i++)
		if(ond[i]>0)
		{
			dfs(i);
			break;
		}
	for(int i=1;i<=n;i++)
		if((ond[i]||ind[i])&&vis[i]==0)
		{
			printf("NO\n");
			return 0;
		}
	printf("YES\n");
	for(int i=an-1;i>=0;i--)
	{
		if(t==1)
		{
			if(ans[i]%2==1)	printf("%d ",-(ans[i]/2+1));
			else	printf("%d ",ans[i]/2+1);
		}
		else	printf("%d ",ans[i]+1);
	}
	
}
