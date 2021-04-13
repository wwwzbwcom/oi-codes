#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
using namespace std;
const int maxn=200100;
int t;
int n,m;
int ind[maxn],oud[maxn];
int lis[maxn],ln;
struct GRAPH
{
	struct EDGE
	{
		int v,m,nxt;
	}e[maxn*2];
	int pre[maxn],en;
	int vis[maxn];
	GRAPH()
	{
		memset(pre,-1,sizeof pre);	en=0; 
	}
	void addedge(int u,int v)
	{
		e[en].v=v;e[en].m=0;e[en].nxt=pre[u];pre[u]=en++;
	}
	void dfseul(int u)
	{
		for(int i=pre[u];i!=-1;i=pre[u])
		{
			while(i!=-1&&e[i].m==1)	i=e[i].nxt;
			if(i==-1)	break; 
			if(e[i].m==0)
			{
				e[i].m=1;	if(t==1)	e[i^1].m=1;
				pre[u]=e[i].nxt;
				dfseul(e[i].v);
				lis[ln++]=i; 
			}
		}
	}
}gp;
int main()
{
//	freopen("out.txt","r",stdin);
    
	scanf("%d",&t);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		gp.addedge(u,v),oud[u]++,ind[v]++;
		if(t==1)	gp.addedge(v,u),oud[u]++,ind[v]++;
	}
	int flag=0,sta=-1;
	for(int i=1;i<=n;i++)	if(oud[i]>0)	sta=i;
	if(t==1)
	{
		for(int i=1;i<=n;i++)	if((ind[i]+oud[i])%4!=0)	flag=1;
	}
	else
	{
		for(int i=1;i<=n;i++)	if(ind[i]!=oud[i])	flag=1;
	}
	
	if(flag==1)	printf("NO\n");
	else
	{
		memset(gp.vis,0,sizeof gp.vis);
		if(sta==-1)
		{
			printf("YES\n");
			return 0;
		}
		gp.dfseul(sta);
		if(ln!=m)	printf("NO\n");
		else
		{
			printf("YES\n");
			for(int i=ln-1;i>=0;i--)
			{
				if(t==1)
				{
					if(lis[i]%2==0)	printf("%d ",(lis[i]/2+1));
					else	printf("%d ",-(lis[i]/2+1));
				}
				else	printf("%d ",(lis[i]+1));
			}
		}
	}
}
