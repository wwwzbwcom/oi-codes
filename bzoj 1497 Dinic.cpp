#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
const int maxn=60000;
const int oo=1e9;
int n,m;
int sum;
class Dinic
{
	private:
		class Edge
		{
			public:
				int v,c;
				int nxt;
		}e[maxn*10];
		int pre[maxn],en;
		int lev[maxn];
		bool bfs()
		{
			queue <int> que;	memset(lev,0,sizeof lev);
			que.push(sta);	lev[sta]=1;
			while(!que.empty())
			{
				int u=que.front();	que.pop();
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c;
					if(lev[v]==0&&c)
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
			for(int i=pre[u];lc-nc&&i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(lev[u]+1==lev[v]&&c)
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
	public:
		int sta,end;
		Dinic()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v,int c)
		{
			e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=0;e[en].nxt=pre[v];pre[v]=en++;
		}
		int dinic()
		{
			int ans=0;
			while(bfs())
			{
				int t;
				do
				{
					t=dfs(sta,oo);
					ans+=t;
				}while(t);
			}
			return ans;
		}
}di;
int main()
{
	scanf("%d%d",&n,&m);
	di.sta=m+n+1;	di.end=m+n+2;
	for(int i=1;i<=n;i++)
	{
		int val;	scanf("%d",&val);
		di.addedge(m+i,di.end,val);
	}
	for(int i=1;i<=m;i++)
	{
		int a,b,c;	scanf("%d%d%d",&a,&b,&c);
		di.addedge(di.sta,i,c);	sum+=c;
		di.addedge(i,m+a,oo);
		di.addedge(i,m+b,oo);
	}
	printf("%d",sum-di.dinic());
}
