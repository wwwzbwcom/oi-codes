#include<cstring>
#include<queue>
#include<cstdio>
using namespace std;
const int maxn=1000000;
const int oo=1e9;
struct Dinic
{
	Dinic()
	{
		memset(pre,-1,sizeof pre);en=0;
	}
	struct Edge
	{
		int v,c;
		int nxt;
	}e[maxn*2];
	int pre[maxn],en;
	int sta,end;
	int lev[maxn];
	void addedge(int u,int v,int c)
	{
		e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].c=0;e[en].nxt=pre[v];pre[v]=en++;
	}
	int bfs()
	{
		queue <int> que;	memset(lev,-1,sizeof lev);
		que.push(sta);	lev[sta]=1;
		while(!que.empty())
		{
			int u=que.front();que.pop();
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(lev[v]==-1&&c)
				{
					lev[v]=lev[u]+1;
					if(v==end)	return 1;
					que.push(v);
				}
			}
		}
		return 0;
	}
	int dfs(int u,int lc)
	{
		if(u==end)	return lc;
		int nc=0;
		for(int i=pre[u];i!=-1&&lc-nc>=0;i=e[i].nxt)
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
		while(bfs())	ans+=dfs(sta,oo);
		return ans;
	}
}d;
int main()
{
	int n;	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		int m;	scanf("%d",&m);
		for(int j=1;j<=m;j++)
		{
			int v;	scanf("%d",&v);
			if(i==1||v==n)	d.addedge(i,v,1);
			else	d.addedge(i,v,oo);
		}
	}
	d.sta=1;
	d.end=n;
	printf("%d\n",d.dinic());
}
