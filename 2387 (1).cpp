#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int oo=999999999;
struct Edge
{
	int v,c;
	int next;
}e[10000];
int en=0;
int pre[10000];
int dis[10000];
int vis[10000];
int m,n;
void addedge(int u,int v,int c)
{
	e[en].v=v;e[en].c=c;e[en].next=pre[u];pre[u]=en++;
	e[en].v=u;e[en].c=c;e[en].next=pre[v];pre[v]=en++;
}
int dijstra()
{
	queue <int> q;
	q.push(1);
	dis[1]=0;
	vis[1]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();vis[u]=0;
	//	cout<<u<<endl;
		for(int i=pre[u];i!=-1;i=e[i].next)
		{
			int v=e[i].v,c=e[i].c;
			//cout<<v<<"="<<endl; 
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
	return dis[n];
}
int main()
{
	memset(pre,-1,sizeof pre);
	memset(vis,0,sizeof vis);
	for(int i=0;i<10000;i++) dis[i]=oo;
	cin>>m>>n;
	int u,v,c;
	for(int i=0;i<m;i++) cin>>u>>v>>c,addedge(u,v,c);
	cout<<dijstra()<<endl;
}
