#include<cstdio>
#include<algorithm>
#include<cstring>
#include<map>
using namespace std;
const int maxn=60000;
const int oo=1e9;
struct Edge
{
	int v,c;
	int nxt;
}e[maxn*2];
int n,m,k;
int pre[maxn],en=0;
int siz[maxn];
int vis[maxn];
int dis[maxn];
struct Node
{
	Node(int le,int re){}
	int le,re,p;
};
void addedge(int u,int v,int c)
{
	e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
}
int dfssize(int u,int f)
{
	siz[u]=1;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v!=f&&vis[v]==0)
		{
			dfssize(v,u);
			siz[u]+=siz[v];
		}
	}
	return siz[u];
}
int mni;
void dfsroot(int u,int f,int tot,int &root)
{
	int mxa=tot-siz[u];
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v!=f&&vis[v]==0)
		{
			dfsroot(v,u,tot,root);
			mxa=max(mxa,siz[v]);
		}
	}
	if(mxa<mni)	mni=mxa,root=u;
}
int le,re;
void dfsdist(int u,int f,int d)
{
	dis[re++]=d;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(v!=f&&vis[v]==0)	dfsdist(v,u,d+c);
	}
}
int solve(int u,int mod)
{
	
	int ans=0;
	int tot=dfssize(u,0);
	int root;	mni=oo;	dfsroot(u,0,tot,root);
	vis[root]=1;
	for(int i=pre[root];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		if(vis[v]==0)	ans+=solve(v,mod);
	}
	for(int i=pre[root];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(vis[v]==0)	dfsdis(v,u,c);
	}
	return ans;
}
int work(int lim,int mod)
{
	k=lim;
	if(solve(1,mod)>=m)	return 1;
	else	return 0;
}
int main()
{
	freopen("path3.in","r",stdin);
	freopen("path.out","w",stdout);
	memset(pre,-1,sizeof pre);
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int u,v,c;	scanf("%d%d%d",&u,&v,&c);
		addedge(u,v,c);
	}
	work(0,0);
}
