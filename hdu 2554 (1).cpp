#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=10010;
int n,m;
struct Dijkstra
{
	struct Edge
	{
		int v,c;
		int nxt; 
	}e[maxn*200];
	
	int pre[maxn],en;
	int vis[maxn],dis[maxn];
	int sta,end;
	void init()
	{
		memset(pre,-1,sizeof pre);	en=0;
	}
	void addedge(int u,int v,int c)
	{
	//if(u==1)	cout<<u<<" "<<v<<" "<<c<<endl;
		e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
	}
	struct Con
	{
		int u,d;
		Con(int ui,int di)
		{
			u=ui;	d=di;
		}
		bool operator <(const Con &in)const
		{
			return d>in.d;
		}
	};
	int work()
	{
		memset(vis,0,sizeof vis);
		priority_queue <Con> que;	for(int i=0;i<maxn;i++)	dis[i]=1e9;
		que.push(Con(sta,0));	dis[sta]=0;
		while(!que.empty())
		{
			Con cur=que.top();	que.pop();
			int u=cur.u,d=cur.d;
			if(vis[u]==0)
			{
				vis[u]=1;
			//	cout<<u<<endl;
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c;
				//	cout<<u<<" "<<v<<endl;
					if(vis[v]==0&&dis[v]>dis[u]+c)
					{
						dis[v]=dis[u]+c;
						que.push(Con(v,dis[u]+c));
					}
				}
			//	cout<<"=="<<endl;
			}
		}
		return dis[end];
	}
}di;
int main()
{
	freopen("graph.in","r",stdin);
	while(1)
	{
		scanf("%d%d",&n,&m);
		if(n==0&&m==0)	return 0;
		di.init();
		di.sta=1;	di.end=n;
		for(int i=1;i<=m;i++)
		{
			int u,v,c;	scanf("%d%d%d",&u,&v,&c);
			di.addedge(u,v,c);
		}
		printf("%d\n",di.work());
	}
} 
