#include<cstring>
#include<cstdio>
using namespace std;
const int maxn=810;
int n,m,q;
class SPFA
{
	private:
		class Edge
		{
			public:
				int u,v,c,nxt;
		}e[10010];
		int pre[maxn],en=0;
		int inq[maxn],dis[maxn][maxn];
		int que[maxn*maxn],qs,qe;
		int cdi[maxn];
		int bfs(int p)
		{
			qs=qe=0;	for(int i=0;i<maxn;i++)	cdi[i]=1e9,inq[i]=0;
			que[qe++]=e[p].u;	cdi[e[p].u]=0;	inq[e[p].u]=1;	
			while(qs<=qe)
			{
				int u=que[qs++];	inq[u]=0;
				if(cdi[u]+dis[u][e[p].v]>=cdi[e[p].v])	continue;
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c;
					if(i!=p&&cdi[v]>cdi[u]+c)
					{
						cdi[v]=cdi[u]+c;
						if(inq[v]==0)
						{
							inq[v]=1;
							que[qe++]=v;
						}
					}
				}
			}
			return cdi[e[p].v];
		}
		void spfa(int sta)
		{
			qs=qe=0;	memset(inq,0,sizeof inq);	for(int i=0;i<maxn;i++)	dis[sta][i]=1e9;
			que[qe++]=sta;	inq[sta]=1;	dis[sta][sta]=0;
			while(qs<=qe)
			{
				int u=que[qs++];	inq[u]=0;
				for(int i=pre[u];i!=-1;i=e[i].nxt)
				{
					int v=e[i].v,c=e[i].c;
					if(dis[sta][v]>dis[sta][u]+c)
					{
						dis[sta][v]=dis[sta][u]+c;
						if(inq[v]==0)
						{
							inq[v]=1; 
							que[qe++]=v;
						} 
					}
				}
			}
			return;
		}
	public:
		int ans[10010];
		SPFA()
		{
			memset(pre,-1,sizeof pre);	en=0;
		}
		inline void addedge(int u,int v,int c)
		{
			e[en].u=u;e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
		}
		void work()
		{
			for(int i=1;i<=n;i++)	spfa(i);
			for(int i=1;i<=m;i++)	ans[i]=bfs(i-1);
		}
}sp;

int main()
{
//	freopen("acu3.in","r",stdin);
//	freopen("out.txt","w",stdout); 
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v,c;	scanf("%d%d%d",&u,&v,&c);
		sp.addedge(u,v,c);
	}
	sp.work();
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		int pi;	scanf("%d",&pi);
		if(sp.ans[pi]>=1e9)	printf("TXHRSSB!\n");
		else	printf("%d\n",sp.ans[pi]);
	}
}
