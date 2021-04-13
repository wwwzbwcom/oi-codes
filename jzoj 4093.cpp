//#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn=100100;
int n,m,q;
class Graph
{
	private: 
		class Edge
		{
			public:
				int v,nxt;
		}e[maxn*10*2];
		int pre[maxn],en;
		int vis[maxn];
		int blo[maxn],bsz[maxn],bn;
		long long sum;
		int low[maxn],tn;
		void dfsblo(int u)
		{
			vis[u]=1;	blo[u]=bn;	bsz[bn]++;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(vis[v]==0)	dfsblo(v);
			}
		}
		int dfsbrg(int u,int fe)
		{
			vis[u]=low[u]=++tn;
			//cout<<u<<"="<<tn<<endl;
			int ret=1;
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;
				if(i/2!=fe/2)
				{
					if(vis[v]==0)	ret+=dfsbrg(v,i),low[u]=min(low[u],low[v]);
					else	low[u]=min(low[u],vis[v]);
				}
			}
			//cout<<u<<" "<<vis[u]<<" "<<low[u]<<endl;
			if(fe!=-1&&vis[u]==low[u])
			{
			//	cout<<fe/2<<" "<<bsz[blo[u]]-ret<<"="<<ret<<" "<<ans[fe/2]<<endl;
				ans[fe/2]+=(long long)(bsz[blo[u]]-ret)*ret;
			}
			return ret;
		}
	public:
		long long ans[maxn*10];
		Graph()
		{
			memset(pre,-1,sizeof pre);	en=0;
		}
		void addedge(int u,int v)
		{
			e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
			e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
		}
		void getblo()
		{
			memset(vis,0,sizeof vis);
			for(int i=0;i<n;i++)
				if(vis[i]==0)
				{
					bn++;
					dfsblo(i);
				}
		}
		void init()
		{
			for(int i=1;i<=bn;i++)	sum+=(long long)bsz[i]*(n-bsz[i]);
			for(int i=0;i<m;i++)	ans[i]=sum/2;
		}
		void getbrg()
		{
			memset(vis,0,sizeof vis);	tn=0;
			for(int i=0;i<n;i++)
				if(vis[i]==0)
					dfsbrg(i,-1);
		}
}gp;
int main()
{
	freopen("water1.in","r",stdin);
	//freopen("out.txt","w",stdout);
	scanf("%d%d%d",&n,&m,&q);
	for(int i=0;i<m;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		gp.addedge(u,v);
	}
	gp.getblo();
	gp.init();
	gp.getbrg();
	for(int i=0;i<q;i++)
	{
		int x;	scanf("%d",&x);
		printf("%lld\n",gp.ans[x]%1000ll);
	}
}
