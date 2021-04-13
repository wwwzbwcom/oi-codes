#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=500;
const int oo=1e9;
class Dinic
{
	private:
		class Edge
		{
			public:
				int v,c;
				int nxt;
		}e[maxn*maxn*2];
		int pre[maxn],en;
		int lev[maxn];
		bool bfs()
		{
			queue <int> que;	memset(lev,0,sizeof lev);
			que.push(sta);		lev[sta]=1;
			while(!que.empty())
			{
				int u=que.front();	que.pop();
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c;
					if(lev[v]==0&&c)
					{
						lev[v]=lev[u]+1;
						if(v==end)	return true;
						que.push(v);
					}
				}
			}
			return false;
		}
		int dfs(int u,int lc)
		{
		//	cout<<u<<endl;
			if(u==end)	return lc;
			int nc=0;
			for(int i=pre[u];lc-nc&&i!=-1;i=e[i].nxt)
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
			if(nc==0)	lev[u]=-2;
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
		//	cout<<u<<" "<<v<<" "<<c<<endl;
			e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=0;e[en].nxt=pre[v];pre[v]=en++;
		}
		int work()
		{
			int ans=0;
			while(bfs())
			{
				int t;
				do
				{
					
					t=dfs(sta,oo);
					ans+=t;
				//	cout<<t<<" "<<ans<<endl;
				}while(t);
			}
			return ans;
		}
}di;
int n,m;
int dis[maxn][maxn];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;	cin>>u>>v;
		dis[u][v]=1;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) 
				if(dis[i][k]&&dis[k][j])	dis[i][j]=1;
	
	di.sta=n*2+1;	di.end=n*2+2;
	
	for(int i=1;i<=n;i++)	di.addedge(di.sta,i,1),di.addedge(i+n,di.end,1);
		
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)	if(i!=j&&dis[i][j])
		{
			di.addedge(i,j+n,1); 
		}
	cout<<n-di.work()<<endl;
}
