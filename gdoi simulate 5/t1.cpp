#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=5000;
int n;
struct SPFA
{
	SPFA()
	{
		memset(pre,-1,sizeof pre);	en=0;
	}
	struct Edge
	{
		int v,nxt;
	}e[maxn*maxn];
	int pre[maxn],en;
	int dis[maxn],vis[maxn];
	void addedge(int u,int v)
	{
		e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
	}
	int spfa(int s)
	{
		for(int i=0;i<6000;i++)	dis[i]=1e9;	queue <int> que;	memset(vis,0,sizeof vis);
		dis[s]=0;	que.push(s);	vis[s]=1;
		while(!que.empty())
		{
			int u=que.front();	que.pop();	vis[u]=0;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(dis[v]>dis[u]+1)
				{
					dis[v]=dis[u]+1;
					if(vis[v]==0)
					{
						vis[v]=1;
						que.push(v);
					}
				}
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++)	ans+=dis[i];
		return ans;
	}
}s;
struct Point
{
	int y,x;
}p[maxn];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>p[i].y>>p[i].x;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)	if(i!=j)
			if((p[i].y<p[j].y&&p[i].x<p[j].x)||(p[i].y>p[j].y&&p[i].x>p[j].x))
				s.addedge(i,j);
	for(int i=1;i<=n;i++)
	{
		cout<<s.spfa(i)<<endl;Akakii
	}
}
