#include<cstdio>
#include<cstring>
#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=100000;
struct Edge
{
	int v,c;
	int nxt;
}e[maxn*2];
int n,m;
int pre[maxn],en=0;
int cnt[maxn],fat[maxn],dis[maxn];
int blo[maxn],lev[maxn];
int ans[maxn],an=0;
int dyp[maxn][2][20];
int siz[maxn][2];
int cur[maxn][2];
void addedge(int u,int v,int c)
{
	e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
}
void dfs1(int u,int f,int d)
{
	cnt[u]=1;	fat[u]=f;	dis[u]=d;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(v!=f)	dfs1(v,u,d+c),cnt[u]+=cnt[v];
	}
}
void dfs2(int u,int f,int bf,int l)
{
	blo[u]=bf;	lev[u]=l;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(v!=f&&cnt[v]>cnt[u]/2)	dfs2(v,u,bf,l);
	}
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(v!=f&&cnt[v]<=cnt[u]/2)	dfs2(v,u,v,l+1);
	}
}
int lca(int u,int v)
{
	while(1)
	{
		if(blo[u]==blo[v])	return min(u,v);
		else
		{
			if(lev[u]>lev[v])	u=fat[blo[u]];
			else	v=fat[blo[v]];
		}
	}
}
int dfs3(int u,int f)
{
	priority_queue <int> que[2];
	memset(cur,0,sizeof cur);
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(v!=f)	dfs3(v,u);
	}
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(v!=f)
		{
			for(int j=0;j<siz[v][1];j++)
			que[1].push(-dyp[v][1][j]);
		}
	}
	
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(v!=f)
		{
			que[0].push(-c);	que[1].push(-c);
			for(int j=0;j<siz[v][0];j++)	que[0].push(-dyp[v][0][j]-c),que[1].push(-dyp[v][0][j]-c);
		}
	}
	
	int flag=1;
	for(int k=1;k<=m;k++)
	{
		int p=0,add;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v,c=e[i].c;
			if(v!=f)
			{
				if(dyp[v][0][cur[v][0]]+c>dyp[p][0][cur[p][0]]+add) p=v,add=c;
			}
		}
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v,c=e[i].c;
			if(v!=f&&v!=p)	que[0].push(-(dyp[p][0][cur[p][0]]+dyp[v][0][cur[v][0]]+c+add)),que[1].push(-(dyp[p][0][cur[p][0]]+dyp[v][0][cur[v][0]]+c+add));
		}
		cur[p][0]++;
	}
	while(que[0].size()>m)	que[0].pop();
	while(que[1].size()>m)	que[1].pop();
	while(!que[0].empty())	dyp[u][0][siz[u][0]++]=que[0].top(),que[0].pop();
	while(!que[1].empty())	dyp[u][1][siz[u][1]++]=que[1].top(),que[1].pop();
	sort(dyp[u][0],dyp[u][0]+siz[u][0]);
	sort(dyp[u][1],dyp[u][1]+siz[u][1]);
	for(int i=0;i<siz[u][0];i++)	dyp[u][0][i]=-dyp[u][0][i];
	for(int i=0;i<siz[u][1];i++)	dyp[u][1][i]=-dyp[u][1][i];
}
int main()
{
	memset(pre,-1,sizeof pre);
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int u,v,c;	scanf("%d%d%d",&u,&v,&c);
		addedge(u,v,c);
	}
	if(0)
	{
		dfs1(1,0,0);
		dfs2(1,0,1,1);
		priority_queue <int> que; 
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
			{
				que.push(-(dis[i]+dis[j]-2*dis[lca(i,j)]));
				while(que.size()>m)	que.pop();
			}
		while(!que.empty())
		{
			ans[an++]=-que.top();
			que.pop();
		}
		for(int i=an-1;i>=0;i--)	printf("%d\n",ans[i]);
	}
	else
	{
		dfs3(1,0);
		for(int i=0;i<m;i++)	printf("%d\n",dyp[1][1][i]);
	}
}
