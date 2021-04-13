#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
struct Edge
{
	int v,nxt;
	double c;
}e[1000000];
int pre[1000],en=0;
void addedge(int u,int v,double c)
{
	e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
}
int n,m;
double x[1000],y[1000];
double dis[1000];
int las[1000];
int vis[1000];

double getdis(int a,int b)
{
	return sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
}
double SPFA(int p1,int p2,int mod)
{
	queue <int> q;
	for(int i=0;i<1000;i++)	dis[i]=1e10,vis[i]=0;
	q.push(1);
	dis[1]=0;vis[1]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();vis[u]=0;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v;
			double c=e[i].c;
			if(u==p1&&v==p2)	continue;
			if(u==p2&&v==p1)	continue;
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
	memset(las,-1,sizeof las);
	memset(pre,-1,sizeof pre);
	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>x[i]>>y[i];
	for(int i=1;i<=m;i++)
	{
		int u,v;	cin>>u>>v;
		addedge(u,v,getdis(u,v));
	}
	double t=SPFA(0,0,0);
	int cur=n;
	double ans=1e10;
	while(las[cur]!=-1)
	{
		ans=min(ans,SPFA(las[cur],cur,1));
		cur=las[cur];
	}
	if(ans>1e10-1)	cout<<-1<<endl;
	else	printf("%.2lf",ans);
}
