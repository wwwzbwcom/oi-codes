#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=500;
const int oo=1e8;
int n,m;
int boo[maxn][maxn];
class Dinic
{
	private:
		class Edge
		{
			public:
				int v,c,nxt;
		}e[maxn*maxn*2];
		int pre[maxn],en;
		int lev[maxn];
		bool bfs()
		{
			queue <int> que;	memset(lev,-1,sizeof lev);
			que.push(sta);	lev[sta]=1;
			while(!que.empty())
			{
				int u=que.front();	que.pop();
			//	cout<<u<<endl;
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
			//cout<<u<<endl;
			if(u==end)	return lc;
			int nc=0;
			for(int i=pre[u];i!=-1&&lc-nc;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(lev[v]==lev[u]+1&&c)
				{
					int cc=min(lc-nc,c);
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
			//	cout<<"==="<<endl;
				ans+=dfs(sta,oo);
			}
			return ans;
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
		void work()
		{
			if(dinic()==n)
			{
				for(int u=n+1;u<=n+n;u++)
				{
					for(int i=pre[u];i!=-1;i=e[i].nxt)
					{
						int v=e[i].v,c=e[i].c;
						if(c==1&&1<=v&&v<=n)	cout<<v<<" ";
					}
				}
			}
			else	cout<<-1<<endl;
		}
}din;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int cmd,x,y,v;	cin>>cmd>>x>>y>>v;
		if(cmd==1)
		{
			for(int i=v+1;i<=n;i++)
				for(int j=x;j<=y;j++)
					if(boo[i][j]!=-1)	boo[i][j]=1;
			for(int i=1;i<x;i++)	boo[v][i]=-1;
			for(int i=y+1;i<=n;i++)	boo[v][i]=-1;
		}
		else
		{
			for(int i=1;i<=v-1;i++)
				for(int j=x;j<=y;j++)
					if(boo[i][j]!=-1)	boo[i][j]=1;
			for(int i=1;i<x;i++)	boo[v][i]=-1;
			for(int i=y+1;i<=n;i++)	boo[v][i]=-1;
		}
	}
	 
	din.sta=n*2+1;
	din.end=n*2+2;
	for(int i=1;i<=n;i++)	din.addedge(din.sta,i,1);
	for(int i=1;i<=n;i++)	din.addedge(n+i,din.end,1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(boo[i][j]==0)
				din.addedge(i,n+j,1);
		//	cout<<boo[i][j]<<' '; 
		}
		//cout<<endl;
	}
	din.work();
}
