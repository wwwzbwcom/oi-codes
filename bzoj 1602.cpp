#include<iostream>
#include<cstring>
using namespace std;
const int maxn=1100;
struct Edge
{
	int v,c;
	int nxt;
}e[maxn*2];
int pre[maxn],en=0;
int n,q;
int fat[maxn],dis[maxn],lev[maxn];
void addedge(int u,int v,int c)
{
	e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
}
void dfs(int u,int f,int d,int l)
{
	fat[u]=f;
	dis[u]=d;
	lev[u]=l;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(v!=f)	dfs(v,u,d+c,l+1);
	}
}
int lca(int u,int v)
{
	while(lev[u]>lev[v])	u=fat[u];
	while(lev[u]<lev[v])	v=fat[v];
	while(u!=v)	u=fat[u],v=fat[v];
	return u;
}
int main()
{
	memset(pre,-1,sizeof pre);
	cin>>n>>q;
	for(int i=1;i<=n-1;i++)
	{
		int u,v,c;	cin>>u>>v>>c;
		addedge(u,v,c);
	}
	dfs(1,-1,0,0);
	for(int i=1;i<=q;i++)
	{
		int u,v;	cin>>u>>v;
		cout<<dis[u]+dis[v]-2*dis[lca(u,v)]<<endl;
	}
}
