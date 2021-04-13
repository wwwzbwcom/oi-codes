#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
struct	Edge
{
	int v;
	double c;
	int next;
}e[200000],r[200000];
int en=0,rn=0;
int gn,n,m;
int pre[200000],rpre[200000];
double dis[200000];
int vis[200000];
int cnt[200000];
int book[200000];
void addedge(int u,int v,double c)
{
	e[en].v=v;e[en].c=c;e[en].next=pre[u];pre[u]=en++;	
}
void raddedge(int u,int v,double c)
{
	r[rn].v=v;r[rn].c=c;r[rn].next=rpre[u];rpre[u]=rn++;	
}
void dfs(int u)
{
	book[u]=1;
	for(int i=rpre[u];i!=-1;i=r[i].next)
		if(book[r[i].v]==0)	dfs(r[i].v);
}
int SPFA()
{
	queue <int> q;
	memset(dis,0,sizeof dis);
	memset(vis,0,sizeof vis);
	memset(cnt,0,sizeof cnt);
	dis[1]=1;
	vis[1]=1;
	cnt[1]=1;
	q.push(1);
	while(!q.empty())
	{
		int u=q.front();q.pop();vis[u]=0;
		if(dis[1]>1+1e-6)	return 1;
		for(int i=pre[u];i!=-1;i=e[i].next)
		{
			int v=e[i].v;double c=e[i].c;
			if(book[v])
			{
				if(dis[v]<dis[u]*c)
				{
					dis[v]=dis[u]*c;
					if(vis[v]==0)
					{
						vis[v]=1;
						cnt[v]++;
						if(cnt[v]>=n)	return	1;
						else	q.push(v);
					}
				}
			}
		}
	}
	return 0;
}
int main()
{
	en=0,rn=0;
	memset(pre,-1,sizeof pre);
	memset(rpre,-1,sizeof rpre);
	scanf("%d",&gn);
	while(gn--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
		{
			int u,v;	double c;
			scanf("%d%d%lf",&u,&v,&c);
			addedge(u,v,c);
			raddedge(v,u,c);
		}
		memset(book,0,sizeof book);
		dfs(1);
		if(SPFA())	printf("YES\n");
		else printf("NO\n");
	}
}
