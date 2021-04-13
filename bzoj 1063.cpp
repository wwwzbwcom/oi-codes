#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=100100;
int n,m,q;
int fix(long long in)
{
	if(in&&in%q==0)	return q;
	return in%q;
}
class Tree
{
	private:
		class Edge
		{
			public:	int v,nxt;
		}e[maxn*2];
		int pre[maxn],en;
		int vis[maxn];
		int dyp[maxn][20][3];
		void dfs(int u,int f)
		{
			vis[u]=1;
			for(int i=0;i<20;i++)	dyp[u][i][0]=1;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(v!=f)
				{
					dfs(v,u);
					for(int j=0;j<20;j++)
					{
						long long f1=0,f2=0;
						f1=dyp[v][j][0]+dyp[v][j][1];
						if(j!=0)	f2=dyp[v][j-1][0]+dyp[v][j-1][1]+dyp[v][j-1][2];
						
						dyp[u][j][2]=fix(dyp[u][j][1]*f1+dyp[u][j][2]*f2);
						dyp[u][j][1]=fix(dyp[u][j][0]*f1+dyp[u][j][1]*f2);
						dyp[u][j][0]=fix(dyp[u][j][0]*f2);
					}
				}
			}
		}
	public:
		Tree()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v)
		{
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
		}
		void work()
		{
			dfs(1,-1);
			for(int i=1;i<=n;i++)	if(vis[i]==0)
			{
				printf("%d\n%d\n",-1,-1);
				return;
			}
			for(int i=0;i<20;i++)	if((long long)dyp[1][i][0]+dyp[1][i][1]+dyp[1][i][2]!=0)
			{
				printf("%d\n%d\n",i,((long long)dyp[1][i][0]+dyp[1][i][1]+dyp[1][i][2])%q);
				return;
			}
		}
}tr;
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		tr.addedge(u,v);
	}
	tr.work();
}
