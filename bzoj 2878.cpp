#include<stack>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=100100;
int n,m;
class CACTUS
{
	private:
		class Edge
		{
			public:
				int v,c,nxt;
		}e[maxn*2];
		int pre[maxn],en;
		double dod[maxn],upd[maxn],dis[maxn];
		int cnt[maxn];
		int vis[maxn],cir[maxn]; 
		void dfs1(int u,int f)
		{
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(v!=f)
				{
					dfs1(v,u);
					dod[u]+=dod[v]+c;	cnt[u]++;
				}
			}
			if(cnt[u]!=0)	dod[u]/=cnt[u];
		}
		void dfs2(int u,int f,double d)
		{
			int num=0;
			if(f!=-1)
			{
				upd[u]=d;
				dis[u]=(dod[u]*cnt[u]+upd[u])/(cnt[u]+1);
				num=1;
			}
			else	dis[u]=dod[u],num=0;
			
			double sum=upd[u];
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(v!=f)
				{
					sum+=dod[v]+c;
					num++;
				}
			}
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(v!=f)
				{
					dfs2(v,u,(sum-dod[v]-c)/(num-1)+c);
				}
			}
		}
		int dfscir1(int u,int f)
		{
			vis[u]=1;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(v!=f)
				{
					if(vis[v])
					{
						cir[v]=cir[u]=1;
						return v;
					}
					else
					{
						int t=dfscir1(v,u);
						if(t==0)	continue;
						
						cir[u]=1;
						if(t==u)	return 0;
						else	return t;
					}
				}
			}
			return 0;
		}
		double dfscir2(int u,int f,int ff)
		{
			if(u==ff)
			{
				double ans=0;
				for(int i=pre[u];i!=-1;i=e[i].nxt)	if(cir[e[i].v]==1)	ans+=dfscir2(e[i].v,u,ff)+e[i].c;
				return ans/2;
			}
			int cnt=0;
			for(int i=pre[u];i!=-1;i=e[i].nxt)	if(e[i].v!=f&&e[i].v!=ff)	cnt++;
			double ans=0;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v,c=e[i].c;
				if(v!=f&&v!=ff)
				{
					if(cir[v]==1)	ans+=dfscir2(v,u,ff)+c; 
					else	ans+=dod[v]+c;
				}
			}
			if(cnt==0)	return 0;
			return ans/cnt;
		}
	public:
		CACTUS()
		{
			memset(pre,-1,sizeof pre);
		}
		void addedge(int u,int v,int c)
		{
			e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
		}
		void build()
		{
			if(n==m+1)
			{
				dfs1(1,-1);
				dfs2(1,-1,0);
			}
			else
			{
				dfscir1(1,-1);
				for(int u=1;u<=n;u++)	if(cir[u]==1)
					for(int i=pre[u];i!=-1;i=e[i].nxt)
					{
						int v=e[i].v;
						if(cir[v]==0)	dfs1(v,u);
					}
					
				for(int i=1;i<=n;i++)	if(cir[i]==1)	upd[i]=dfscir2(i,-1,i);
				for(int u=1;u<=n;u++)	if(cir[u]==1)
				{
					int num=0;
					double sum=upd[u]*2;
					for(int i=pre[u];i!=-1;i=e[i].nxt)
					{
						int v=e[i].v,c=e[i].c;
						if(cir[v]==0)	sum+=dod[v]+c,num++;
					}
					for(int i=pre[u];i!=-1;i=e[i].nxt)
					{
						int v=e[i].v,c=e[i].c;
						if(cir[v]==0)	dfs2(v,u,(sum-dod[v]-c)/(num+1)+c);
					}
					dis[u]=sum/(num+2);
				}
				for(int i=1;i<=n;i++)	if(cir[i]==0)	dis[i]=(upd[i]+dod[i]*cnt[i])/(cnt[i]+1);
			}
			double ans=0;
			for(int i=1;i<=n;i++)	ans+=dis[i];
			printf("%.5lf\n",ans/n);
		}
}ca;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v,c;	scanf("%d%d%d",&u,&v,&c);
		ca.addedge(u,v,c);
	}
	ca.build();
}
