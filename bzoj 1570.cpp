#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=1000000;
struct Dinic
{
	Dinic()
	{
		memset(pre,-1,sizeof pre);
		en=0;
		sta=maxn;
		end=maxn+1;
	}
	int n,sta,end;
	struct Edge
	{
		int v,c;
		int nxt;
	}e[maxn+100];
	int pre[maxn+100];
	int lev[maxn+100];
	int en;
	void addedge(int u,int v,int c)
	{
		e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].c=0;e[en].nxt=pre[v];pre[v]=en++;
	}
	int bfs()
	{
		memset(lev,0,sizeof lev);	queue <int> que;
		lev[sta]=1,que.push(sta);
		while(!que.empty())
		{
			int u=que.front();	que.pop();
		//	cout<<u<<endl;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(lev[v]==0&&c)
				{
					lev[v]=lev[u]+1;
					que.push(v);
				}
			}
		}
		return lev[end];
	}
	int dfs(int u,int lc)
	{
		if(u==end)	return lc;
		int nc=0;
		for(int i=pre[u];i!=-1&&nc<lc;i=e[i].nxt)
		{
			int v=e[i].v,c=e[i].c;
			if(lev[v]==lev[u]+1&&c)
			{
				int cc=min(c,lc-nc);
				cc=dfs(v,cc);
				e[i].c-=cc;
				e[i^1].c+=cc;
				nc+=cc;
			}
		}
		if(nc==0)	lev[u]=-1;
		return nc;
	}
	int dinic()
	{
		int ans=0;
		while(bfs())
		{
			ans+=dfs(sta,1e8);
		}
		cout<<ans<<"===="<<lev[end]<<endl;
		return ans;
	}
}d,b;
int main()
{
	int n,m,t;	cin>>n>>m>>t;
	b.n=n;
	int u[10000],v[10000],c[10000];
	for(int i=1;i<=m;i++)	cin>>u[i]>>v[i]>>c[i];
	int tim=1;
	while(1)
	{
		b.addedge(b.sta,(tim-1)*n+1,1e8);
		for(int i=1;i<=n;i++)	b.addedge((tim-1)*n+i,tim*n+i,1e8);
		for(int i=1;i<=m;i++)	b.addedge((tim-1)*n+u[i],tim*n+v[i],c[i]);
		b.addedge(tim*n+n,b.end,1e8);
		d=b;
		if(d.dinic()>=t)	break;
		tim++;
	}
	cout<<tim<<endl;
} 
