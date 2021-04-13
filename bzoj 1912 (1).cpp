#include<cstdio>
#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
const int maxn=100100;
struct Graph
{
	Graph(){memset(p,-1,sizeof p);n=0;}
	struct Edge
	{
		int v,c;
		int nxt;
	}e[maxn*2];
	int p[maxn],n;
	void ae(int u,int v,int c)
	{
		e[n].v=v;e[n].c=c;e[n].nxt=p[u];p[u]=n++;
		e[n].v=u;e[n].c=c;e[n].nxt=p[v];p[v]=n++;
	}
}g;
int n,k;
int dis[maxn];
int len[maxn];
int fat[maxn];
int fed[maxn];
int boo[2*maxn];
int u,v,bn,ans;
void dfs(int u,int f,int fe,int d)
{
	dis[u]=d;	fat[u]=f;	fed[u]=fe;
	for(int i=g.p[u];i!=-1;i=g.e[i].nxt)
	{
		int v=g.e[i].v,c=g.e[i].c;
		if(v!=f)	dfs(v,u,i,d+c);
	}
}
void work(int u,int f)
{
	int m1=0,m2=0;
	for(int i=g.p[u];i!=-1;i=g.e[i].nxt)
	{
		int v=g.e[i].v,c=g.e[i].c;
		if(v!=f)
		{
			work(v,u);
			int l=len[v]+c;
			if(l>m1)	m2=m1,m1=l;
			else	if(l>m2)	m2=l;
		}
	}
	len[u]=max(m1,m2);
	dis[u]=m1+m2;
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%d%d",&n,&k);
	
	for(int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		g.ae(u,v,1);
	}
	ans=(n-1)*2;
	u=v=0;
	dfs(1,-1,-1,0);	for(int i=1;i<=n;i++)	if(dis[u]<dis[i])	u=i;
	dfs(u,-1,-1,0);	for(int i=1;i<=n;i++)	if(dis[v]<dis[i])	v=i;
	if(dis[v]>0)	ans=ans-dis[v]+1;
	if(k==1)	printf("%d\n",ans);
	else
	{
		while(fed[v]!=-1)	g.e[fed[v]].c=g.e[fed[v]^1].c=-1,v=fat[v];
		u=v=0;
		work(1,-1);
		for(int i=1;i<=n;i++)	if(dis[i]>dis[v])	v=i;
		if(dis[v]>0)	ans=ans-dis[v]+1;
		printf("%d\n",ans);
	}
}
