#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int oo=999999999;
struct Edge
{
	int v,c;
	int mode;
	int next;
}e[2000100];
int pre[2000];
int vis[2000];
int dis[5][2000];
int en=0;
int gn;
int n,m,x;
void addedge(int u,int v,int c)
{
	e[en].v=v;e[en].c=c;e[en].next=pre[u];e[en].mode=1;pre[u]=en++;
	e[en].v=u;e[en].c=c;e[en].next=pre[v];e[en].mode=2;pre[v]=en++;
}
int SPFA(int s,int mo)
{
	memset(vis,0,sizeof vis);
	for(int i=0;i<2000;i++) dis[mo][i]=oo;
	queue <int> q;
	q.push(s);
	vis[s]=1;
	dis[mo][s]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();vis[u]=0;
	//	cout<<u<<endl;
		for(int i=pre[u];i!=-1;i=e[i].next)
		{
			int v=e[i].v,c=e[i].c;
			if(e[i].mode==mo&&dis[mo][u]+c<dis[mo][v])
			{
				dis[mo][v]=dis[mo][u]+c;
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
	memset(pre,-1,sizeof pre);
	cin>>n>>m>>x;
	for(int i=0;i<m;i++)
	{
		int u,v,c;
		cin>>u>>v>>c;
		addedge(u,v,c);
	}
	SPFA(x,1);SPFA(x,2);
	int ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,dis[1][i]+dis[2][i]);
	cout<<ans<<endl;
}
