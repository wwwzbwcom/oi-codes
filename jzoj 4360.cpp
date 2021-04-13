#include<cstdio>
//#include<iostream>
#include<cstring>
#include<queue>
#include<stack>
#include<cmath>
using namespace std;
const int maxn=1100;
const double oo=1e15;
int n;
double val[maxn],har[maxn];
int lev[maxn];
struct Tarjan
{
	struct Edge
	{
		int u,v;
		int nxt;
	}e[maxn*20];
	int pre[maxn],en;
	int vis[maxn],low[maxn],ist[maxn],cnt;
	int blo[maxn],siz[maxn],bn;
	stack <int> sta;
	Tarjan()
	{
		memset(pre,-1,sizeof pre);	en=0;
	}
	void addedge(int u,int v)
	{
		e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
	}
	void tarjan(int u)
	{
		vis[u]=low[u]=++cnt;
		sta.push(u);	ist[u]=1;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v;
			if(vis[v]==0)	tarjan(v),low[u]=min(low[u],low[u]);
			else	if(ist[v]==1)	low[u]=min(low[u],vis[v]);
		}
		if(vis[u]==low[u])
		{
			int tmp;
			bn++;
		//	cout<<u<<"~"<<bn<<endl;
			do
			{
				tmp=sta.top();
				sta.pop();
				ist[tmp]=0;
				blo[tmp]=bn;
				siz[bn]++;
			}while(tmp!=u);
		}
	}
}t;
struct Graph
{
	struct Edge
	{
		int u,v;
		int nxt;
	}e[maxn*20];
	int pre[maxn],en;
	int mar[maxn];
	Graph()
	{
		memset(pre,-1,sizeof pre);	en=0;
	}
	void addedge(int u,int v)
	{
		e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
	}
	void dfs(int u)
	{
		mar[u]=1;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v;
			if(mar[v]==0)	dfs(v);
		}
	}
}g;
struct Dinic
{
	struct Edge
	{
		int u,v;
		double c;
		int nxt;
	}e[maxn*20];
	int pre[maxn],en;
	int sta,end;
	Dinic()
	{
		memset(pre,-1,sizeof pre);
		en=0;
	}
	void addedge(int u,int v,double c)
	{
	//	cout<<u<<" "<<v<<" "<<c<<endl;
		e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].c=0;e[en].nxt=pre[v];pre[v]=en++;
	}
	bool bfs()
	{
		memset(lev,-1,sizeof lev);	queue <int> que;
		lev[sta]=1;	que.push(sta);
		while(!que.empty())
		{
			int u=que.front();	que.pop();
			for(int i=pre[u];i!=-1;i=e[i].nxt)
			{
				int v=e[i].v;	double c=e[i].c;
				if(lev[v]==-1&&c>1e-10)
				{
					lev[v]=lev[u]+1;
					if(v==end)	return 1;
					que.push(v);
				}
			}
		}
		return 0;
	}
	double dfs(int u,double lc)
	{
		if(u==end)	return lc;
		double nc=0;
		for(int i=pre[u];i!=-1&&lc-nc>1e-10;i=e[i].nxt)
		{
			int v=e[i].v;	double c=e[i].c;
			if(lev[v]==lev[u]+1&&c>1e-10)
			{
				double cc=min(c,lc-nc);
				cc=dfs(v,cc);
				e[i].c-=cc;
				e[i^1].c+=cc;
				nc+=cc;
			}
		}
		if(nc<1e-10)	lev[u]=-2;
		return nc;
	}
	double dinic()
	{
		double ans=0;
		while(bfs())	ans+=dfs(sta,oo);
		return ans;
	}
}b,d;
bool check(double ans)
{
	d=b;
	double tol=0; 
	for(int i=1;i<=t.bn;i++)
	{
	//	cout<<i<<" "<<ans<<" "<<val[i]<<" "<<har[i]<<" "<<ans*val[i]-har[i]<<endl; 
		if(ans*val[i]-har[i]>=0)	d.addedge(d.sta,i,ans*val[i]-har[i]),tol+=ans*val[i]-har[i];
		else	d.addedge(i,d.end,abs(ans*val[i]-har[i]));
	}
	if(tol-d.dinic()>1e-8)	return 1;
	else 	return 0;
}
int main()
{
	scanf("%d",&n);
	for(int u=1;u<=n;u++)
	{
		int k;	scanf("%d",&k);
		for(int j=1;j<=k;j++)
		{
			int v;	scanf("%d",&v);
			t.addedge(u,v);
		}
	}
	for(int i=1;i<=n;i++)	if(t.vis[i]==0)	t.tarjan(i);
//	for(int i=1;i<=n;i++)	cout<<i<<"-"<<t.blo[i]<<endl;
//	cout<<t.bn<<endl;
	for(int u=1;u<=n;u++)
		for(int i=t.pre[u];i!=-1;i=t.e[i].nxt)
		{
			int v=t.e[i].v;
			if(t.blo[u]!=t.blo[v])	g.addedge(t.blo[u],t.blo[v]);
		}
	for(int u=1;u<=t.bn;u++)	if(t.siz[u]>1)	g.dfs(u);
	for(int u=1;u<=t.bn;u++)
	{
		if(g.mar[u]==0)
			for(int i=g.pre[u];i!=-1;i=g.e[i].nxt)
			{
				int v=g.e[i].v;
				if(g.mar[v]==0)
				{
				//	cout<<u<<"="<<v<<endl;
					b.addedge(u,v,oo);
				}
			}
	}
	b.sta=t.bn+1;
	b.end=t.bn+2;
	for(int i=1;i<=n;i++)
	{
		double vali,hari;	scanf("%lf%lf",&vali,&hari);
	//	cout<<i<<"="<<t.blo[i]<<" "<<vali<<" "<<hari<<endl;
		val[t.blo[i]]=vali;
		har[t.blo[i]]=hari;
	}
//	for(int i=1;i<=t.bn;i++)	cout<<i<<"~"<<val[i]<<"~"<<har[i]<<endl;
//	cout<<check(0.5)<<endl;
//	return 0;
	double l=0,r=10000,ans=-1;
	while(abs(r-l)>1e-10)
	{
		double mid=(l+r)/2;
		if(check(mid)==1)	ans=mid,r=mid;
		else	l=mid;
	}
	if(ans<1e-10)	printf("CanNotFindTreasure!\n");
	else	printf("%lf\n",ans); 
}
