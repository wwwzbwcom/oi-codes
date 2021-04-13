#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
struct Edge
{
	int v,c,nxt;
}e[20000];
int pre[20000],en=0;
int n,m;
int dis[20000];
int vis[20000];
int las[20000];
void addedge(int u,int v,int c)
{
	e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
}
int SPFA(int p1,int p2,int mod)
{
	queue<int>q;
	for(int i=0;i<20000;i++)	dis[i]=1e9,vis[i]=0;
	q.push(1);
	vis[1]=1;dis[1]=0;
	
	while(!q.empty())
	{
		int u=q.front();q.pop();vis[u]=0;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v,c=e[i].c;
			if(u==p1&&v==p2)	c*=2;
			if(u==p2&&v==p1)	c*=2;
			if(dis[v]>dis[u]+c)
			{
				dis[v]=dis[u]+c;
				if(mod==0)	las[v]=u;
				if(vis[v]==0)
				{
					q.push(v);
					vis[v]=1;
				}
			}
		}
	}
	return dis[n];
}
int main()
{
	memset(pre,-1,sizeof pre);
	memset(las,-1,sizeof las);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v,c;	cin>>u>>v>>c;
		addedge(u,v,c);
	}
	int origin=SPFA(0,0,0);
	int ans=0;
	int cur=n;
	while(las[cur]!=-1)
	{
	//	cout<<cur<<" "<<SPFA(cur,las[cur],1)<<endl;
		ans=max(ans,SPFA(cur,las[cur],1)-origin);
		cur=las[cur];
	}
	cout<<ans<<endl;
}
