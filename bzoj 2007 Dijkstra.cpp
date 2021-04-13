#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
const int maxn=600*600;
const int oo=1e9;
int n;
class Dijkstra
{
	private:
		class Node
		{
			public:	int v,c,nxt;
		}e[maxn*20];
		int pre[maxn],en;
		int vis[maxn],dis[maxn];
		class Con
		{
			public:
				Con(const int ui,const int di)
				{
					u=ui;	d=di;
				}
				int u,d;
				bool operator<(const Con &in)const
				{
					return in.d<d;
				}
		};
	public:
		int sta,end;
		Dijkstra()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v,int c)
		{
			e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
		}
		int work()
		{
			memset(vis,0,sizeof vis);
			for(int i=0;i<maxn;i++)	dis[i]=oo;
			priority_queue <Con> que;
			
			dis[sta]=0;
			que.push(Con(sta,0));
			
			while(!que.empty())
			{
				Con cur=que.top();	que.pop();
				int u=cur.u,d=cur.d;
				if(vis[u]==0)
				{
					vis[u]=1;	dis[u]=d;
					for(int i=pre[u];i!=-1;i=e[i].nxt)
					{
						int v=e[i].v,c=e[i].c;
						if(vis[v]==0&&dis[v]>dis[u]+c)
						{
							dis[v]=dis[u]+c;
							que.push(Con(v,dis[u]+c));
						}
					}
				}
			}
			return dis[end];
		}
}di;
int idx(int y,int x)
{
	return y*n+x;
}
int main()
{
	scanf("%d",&n);
	di.sta=n*n,di.end=n*n+1;
	for(int i=0;i<n+1;i++)
		for(int j=0;j<n;j++)
		{
			int c;	scanf("%d",&c);
			if(i!=0&&i!=n)	di.addedge(idx(i-1,j),idx(i,j),c);
			else
			{
				if(i==0)	di.addedge(di.sta,idx(i,j),c);
				if(i==n)	di.addedge(idx(i-1,j),di.end,c);
			}
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<n+1;j++)
		{
			int c;	scanf("%d",&c);
			if(j!=0&&j!=n)	di.addedge(idx(i,j),idx(i,j-1),c);
			else
			{
				if(j==0)	di.addedge(idx(i,j),di.end,c);
				if(j==n)	di.addedge(di.sta,idx(i,j-1),c); 
			}
		}
	for(int i=0;i<n+1;i++)
		for(int j=0;j<n;j++)
		{
			int c;	scanf("%d",&c);
			if(i!=0&&i!=n)	di.addedge(idx(i,j),idx(i-1,j),c);
			else
			{
				if(i==0)	di.addedge(idx(i,j),di.sta,c);
				if(i==n)	di.addedge(di.end,idx(i-1,j),c);
			}
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<n+1;j++)
		{
			int c;	scanf("%d",&c);
			if(j!=0&&j!=n)	di.addedge(idx(i,j-1),idx(i,j),c);
			else
			{
				if(j==0)	di.addedge(di.end,idx(i,j),c);
				if(j==n)	di.addedge(idx(i,j-1),di.sta,c); 
			}
		}
	printf("%d",di.work());
}
