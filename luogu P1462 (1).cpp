#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
struct Graph
{
	Graph(){n=0;memset(p,-1,sizeof p);}
	struct Edge
	{
		int v;
		long long c;
		int nxt;
	}e[200000];
	int p[20000];
	int n;
	void ae(int u,int v,long long c)
	{
		e[n].v=v;e[n].c=c;e[n].nxt=p[u];p[u]=n++;
		e[n].v=u;e[n].c=c;e[n].nxt=p[v];p[v]=n++;
	}
}g;
int n,m;
long long b;
long long f[20000];
bool vis[20000];
long long dis[20000];
int SPFA(int lim)
{
	queue <int> q;
	memset(vis,0,sizeof vis);
	for(int i=0;i<20000;i++)	dis[i]=2e18;
	dis[1]=0;
	q.push(1);
	vis[1]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();vis[u]=0;
		if(f[u]>lim)	continue;
		for(int i=g.p[u];i!=-1;i=g.e[i].nxt)
		{
			int v=g.e[i].v,c=g.e[i].c;
			if(f[v]<=lim&&dis[v]>dis[u]+c)
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
	if(dis[n]<b)	return 1;
	else	return 0;
}
int main()
{
	cin>>n>>m>>b;
	long long maxn=0;
	for(int i=1;i<=n;i++)	cin>>f[i],maxn=max(maxn,f[i]);
	for(int i=1;i<=m;i++)
	{
		int u,v;long long c;	cin>>u>>v>>c;
		g.ae(u,v,c);
	}
	long long l=f[n],r=maxn;
	long long ans=-1;
	while(l<=r)
	{
		long long mid=(l+r)/2;
		if(SPFA(mid))	ans=mid,r=mid-1;
		else	l=mid+1;
	}
	if(ans==-1)	cout<<"AFK"<<endl;
	else	cout<<ans<<endl;
}
