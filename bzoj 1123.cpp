#include<iostream>
#include<cstring>
using namespace std;
struct Edge
{
	int v;
	int nxt;
}e[1000100];
int n,m;
int pre[100100],en=0;
int vis[100100],low[100100],isc[100100];
int times=0;
void addedge(int u,int v)
{
	e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
}
void tarjan(int u,int f)
{
	int child=0;
	vis[u]=low[u]=++times;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		if(vis[v]==0)
		{
			child++;
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=vis[u])	isc[u]=1;
		}
		else	if(v!=f)	low[u]=min(low[u],vis[v]);
	}
	if(f==-1&&child==1)	isc[u]=0;
}
int work(int u)
{
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		sum+=
	}
}
int main()
{
	memset(pre,-1,sizeof pre);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;	cin>>u>>v;
		addedge(u,v);
	}
	tarjan(1,-1);
	for(int i=1;i<=n;i++)
	{
		if(isc[i]==0)	cout<<0<<endl;
		else	cout<<work(i)<<endl;
	}
}
