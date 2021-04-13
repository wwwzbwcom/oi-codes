//#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
const int maxm=200100;
const int maxn=2000;
const long long oo=1e18;
int n,m;
struct Dijstra
{
	Dijstra(){memset(pre,-1,sizeof pre);en=0;}
	struct Edge
	{
		int v,d;
		int mar;
		int nxt;
	}e[maxm];
	int pre[maxn],en;
	int vis[maxn],dis[maxn];
	void addedge(int u,int v,int d)
	{
		e[en].v=v;e[en].d=d;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].d=d;e[en].nxt=pre[v];pre[v]=en++;
	}
	struct Node
	{
		int u,d;
		Node(int ui,int di)
		{
			u=ui;
			d=di;
		}
		bool operator <(const Node &in)const
		{
			return d>in.d;
		}
	};
	void dijstra()
	{
		priority_queue <Node> que;
		que.push(Node(1,0));
		int flag=-1;
		while(!que.empty())
		{
			Node cur=que.top();	que.pop();
			int u=cur.u,dc=cur.d;
			if(vis[u]==0)
			{
				vis[u]=1;	dis[u]=dc;	
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,d=e[i].d;
					if(vis[v]==0)	que.push(Node(v,dc+d));
				}
			}
		}
	}
	void dfs(int u)
	{
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v,d=e[i].d;
			if(dis[u]-d==dis[v])
			{
				e[i^1].mar=1;
				dfs(v);
			}
		}
	}
}dij;
struct Dinic
{
	Dinic()
	{
		memset(pre,-1,sizeof pre);
		en=0;
	}
	struct Edge
	{
		int v;
		long long c;
		int nxt;
	}e[maxm];
	int pre[maxn],en;
	int lev[maxn];
	int sta,end;
	void addedge(int u,int v,long long c)
	{
		e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].c=0;e[en].nxt=pre[v];pre[v]=en++;
	}
	int bfs()
	{
		memset(lev,-1,sizeof lev);
		queue <int> que;
		que.push(sta);	lev[sta]=1;
		while(!que.empty())
		{
			int u=que.front();	que.pop();
		//	cout<<u<<endl;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				long long c=e[i].c;
			//	cout<<v<<"="<<endl;
				if(lev[v]==-1&&c!=0)
				{
					lev[v]=lev[u]+1;
					if(v==end)	return 1;
					que.push(v);
				}
			}
		}
		return 0;
	}
	long long dfs(int u,long long lc)
	{
	//	cout<<lev[u]<<endl;
		if(u==end)	return lc;
		long long nc=0;
		for(int i=pre[u];i!=-1&&lc-nc>0;i=e[i].nxt)
		{
			int v=e[i].v;
			long long c=e[i].c;
			if(lev[v]==lev[u]+1&&c!=0)
			{
				long long cc=min(lc-nc,c);
				cc=dfs(v,cc);
				e[i].c-=cc;
				e[i^1].c+=cc;
				nc+=cc;
			}
		}
		if(nc==0)	lev[u]=-2;
		return nc; 
	}
	long long dinic()
	{
		long long ans=0;
		while(bfs())
		{
			ans+=dfs(sta,oo);
		}
		return ans;
	}
}din;
int main()
{
//	freopen("network.in","r",stdin);
//	freopen("network.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v,d;	scanf("%d%d%d",&u,&v,&d);
		dij.addedge(u,v,d);
	}
	dij.dijstra();
	dij.dfs(n);
	
	//cout<<"=========="<<endl;
	for(int i=1;i<=n;i++)
	{
		long long val;	scanf("%d",&val);
	//	cout<<i<<" "<<val<<endl;
		din.addedge(i*2-1,i*2,val);
	}
	for(int u=1;u<=n;u++)
		for(int i=dij.pre[u];i!=-1;i=dij.e[i].nxt)	if(dij.e[i].mar)
		{
			int v=dij.e[i].v;
		//	cout<<u<<"="<<v<<"="<<dij.e[i].d<<endl;
			din.addedge(u*2,v*2-1,oo);
		}
	din.sta=1*2;	din.end=n*2-1;
//	puts("============");
	printf("%lld",din.dinic());
}
