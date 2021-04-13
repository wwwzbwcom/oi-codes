#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
const int maxn=1e6+10;
int n;
class Graph
{
	private:
		class Edge
		{
			public:
				int u,v,c;
				int nxt;
		}e[maxn*2];
		int pre[maxn],en;
		int cnt[maxn];
		void dfs(int u,int f)
		{
			cnt[u]=1;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(v!=f)	dfs(v,u),cnt[u]+=cnt[v];
			}
		}
	public:
		Graph()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v,int c)
		{
			e[en].u=u;e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
			e[en].u=v;e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
		}
		long long work()
		{
			dfs(1,-1);
			long long ans=0;
			for(int i=0;i<en;i+=2)
			{
				int u=e[i].u,v=e[i].v,c=e[i].c;
				if(cnt[u]<cnt[v])	swap(u,v);
				ans+=(long long)abs((n-cnt[v])-cnt[v])*c;
			}
			return ans;
		}
}gp;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		int u,v,c;	scanf("%d%d%d",&u,&v,&c);
		gp.addedge(u,v,c);
	}
	printf("%lld",gp.work());
}
