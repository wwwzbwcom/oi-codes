#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=1e5;
struct Edge
{
	int v,c;
	int next;
}e[maxn];
int en=0;
int pre[maxn];
int dis[maxn];
bool vis[maxn];
void addedge(int u,int v,int c)
{
	e[en].v=v;e[en].c=c;e[en].next=pre[u];pre[u]=en++;
	e[en].v=u;e[en].c=c;e[en].next=pre[v];pre[v]=en++;
}
void SPFA(int s)
{
	memset(vis,0,sizeof vis);
	for(int i=0;i<maxn;i++)	dis[i]=2e9;
	dis[s]=0;
	queue <int> q;
	q.push(s);
	vis[s]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();vis[u]=0;
		for(int i=pre[u];i!=-1;i=e[i].next)
		{
			int v=e[i].v,c=e[i].c;
			if(dis[u]+c<dis[v])
			{
				dis[v]=dis[u]+c;
				if(vis[v]==0)
				{
					q.push(v);
					vis[v]=1;
				}
			}
		}
	}
}
int main()
{
	int n,m,q;
	memset(pre,-1,sizeof pre);
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++)
	{
		int u,v,c;
		cin>>u>>v>>c;
		addedge(u,v,c);
	}
	for(int i=1;i<=q;i++)
	{
		int s,e;
		cin>>s>>e;
		SPFA(s);
		cout<<dis[e]<<endl;
	}
}
