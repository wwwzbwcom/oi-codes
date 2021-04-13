#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<queue>
using namespace std;
const int maxn=1100;
int n,e;
int cc,kk;
class Graph
{
	private:
		class Edge
		{
			public:	int v,nxt;
		}e[maxn*2];
		int pre[maxn],en;
		int vis[maxn];
		int dis[maxn][maxn];
		int boo[maxn][maxn];
		double dyp[maxn][maxn];
		void bfs(int sta)
		{
			queue <int> que;
			memset(vis,0,sizeof vis);
			
			vis[sta]=1;
			dis[sta][sta]=0;
			que.push(sta);
			while(!que.empty())
			{
				int u=que.front();	que.pop();
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v;
					if(vis[v]==0)
					{
						vis[v]=1;
						dis[sta][v]=dis[sta][u]+1;
						que.push(v);
					}
				}
			}
		}
		double dfs(int uc,int uk)
		{
			if(boo[uc][uk])	return dyp[uc][uk];
			boo[uc][uk]=1;
			
			if(uc==uk)	return dyp[uc][uk]=0; 
			if(dis[uc][uk]<=2)	return dyp[uc][uk]=1;
			
			int vc=uc;
			for(int i=pre[uc];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(dis[v][uk]<dis[vc][uk])	vc=v;
				else	if(dis[v][uk]==dis[vc][uk]&&v<vc)	vc=v;
			}
			int t=vc;
			for(int i=pre[t];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(dis[v][uk]<dis[vc][uk])	vc=v;
				else	if(dis[v][uk]==dis[vc][uk]&&v<vc)	vc=v;
			}
			
			int cnt=0;
			for(int i=pre[uk];i!=-1;i=e[i].nxt)
			{
				int vk=e[i].v;
				dyp[uc][uk]+=dfs(vc,vk)+1;
				cnt++;
			}
			dyp[uc][uk]+=dfs(vc,uk)+1;
			cnt++;
			
			dyp[uc][uk]/=cnt;
			return dyp[uc][uk];
		}
	public:
		Graph()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v)
		{
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
		}
		void build()
		{
			for(int i=1;i<=n;i++)	bfs(i);
		}
		double work()
		{
			return dfs(cc,kk);
		}
}gp;
int main()
{
	scanf("%d%d",&n,&e);
	scanf("%d%d",&cc,&kk);
	for(int i=1;i<=e;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		gp.addedge(u,v);
	}
	gp.build();
	printf("%.3lf",gp.work());
}
