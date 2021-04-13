#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=10010;
const int oo=1e9;
struct Edge
{
	int v,c,nxt;
}e[maxn*2];
int n,k;
int pre[maxn],en=0;
int siz[maxn];
int vis[maxn];
int dis[maxn];
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
		if(v!=f&&vis[v]==0)	dfssize(v,u),siz[u]+=siz[v];
	}
	return siz[u];
}
int mni;
void getroot(int u,int f,int tot,int &root)
{
	int mxa=tot-siz[u];
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v!=f&&vis[v]==0)	getroot(v,u,tot,root),mxa=max(mxa,siz[v]);
	}
	if(mxa<mni)	mni=mxa,root=u;
}
int le,re;
void dfsdis(int u,int f,int d)
{
	dis[re++]=d;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(v!=f&&vis[v]==0)	dfsdis(v,u,d+c);
	}
}
int getans(int lc,int rc)
{
	sort(dis+lc,dis+rc);
	int ans=0,p=rc-1;
	for(int i=lc;i<rc;i++)
	{
		if(dis[i]>k)	break;
		while(p>=lc&&dis[p]+dis[i]>k)	p--;
		ans+=p-lc+1;
		if(p>i)	ans--;
	}
	return ans/2;
}
int solve(int u)
{
	int ans=0;
	int tot=dfssize(u,0);
	mni=oo;
	int root;
	getroot(u,0,tot,root);
	vis[root]=1;
	for(int i=pre[root];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		if(vis[v]==0)	ans+=solve(v);
	}
	le=re=0;
	for(int i=pre[root];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(vis[v]==0)
		{
			dfsdis(v,root,c);
			ans-=getans(le,re);
			le=re;
		}
	}
	ans+=getans(0,re);
	for(int i=0;i<re;i++)	if(dis[i]<=k)	ans++;
	vis[root]=0;
	return ans;
}
int main()
{
	while(scanf("%d%d",&n,&k)&&n!=0&&k!=0)
	{
		memset(pre,-1,sizeof pre);	en=0;
		for(int i=1;i<n;i++)
		{
			int u,v,c;	scanf("%d%d%d",&u,&v,&c);
			addedge(u,v,c);
		}
		printf("%d\n",solve(1));
	}
}
