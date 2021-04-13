#include<cstring>
#include<cstdio>
#include<stack>
using namespace std;
const int maxn=500100;
struct Graph
{
	Graph(){memset(p,-1,sizeof p);n=0;}
	struct Edge
	{
		int v;
		int nxt;
	}e[maxn];
	int p[maxn],n;
	void ae(int u,int v)
	{
		e[n].v=v;e[n].nxt=p[u];p[u]=n++;
	}
}b,a;
int n,m;
int root,pn;
int times=0;
int vis[maxn],low[maxn],ins[maxn];
stack <int> sta;
int wei[maxn],mar[maxn];
int idx[maxn];
int bn=0;
int bwe[maxn],bma[maxn];
int dyp[maxn];
void input()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		b.ae(u,v);
	}
	for(int i=1;i<=n;i++)	scanf("%d",&wei[i]);
	scanf("%d%d",&root,&pn);
	for(int i=1;i<=pn;i++)
	{
		int t;scanf("%d",&t);
		mar[t]=1;
	}
}

void tarjan(int u)
{
	vis[u]=low[u]=++times;
	ins[u]=1;sta.push(u);
	for(int i=b.p[u];i!=-1;i=b.e[i].nxt)
	{
		int v=b.e[i].v;
		if(vis[v]==0)
		{
			tarjan(v);
			low[u]=min(low[u],low[v]); 
		}
		else	if(ins[v])	low[u]=min(low[u],vis[v]);
	}
	if(low[u]==vis[u])
	{
		bn++;
		int now;
		do
		{
			now=sta.top();	sta.pop();	ins[now]=0;
			idx[now]=bn;	bwe[bn]+=wei[now];	if(mar[now])	bma[bn]=1;
		}while(now!=u);
	}
}
int dfs(int u)
{
	vis[u]=1;
	int flag=0;
	if(bma[u]==1)	dyp[u]=bwe[u],flag=1;
	for(int i=a.p[u];i!=-1;i=a.e[i].nxt)
	{
		int v=a.e[i].v;
		if(vis[v]==0)	dfs(v);
		if(bma[v]==1)	dyp[u]=max(dyp[u],dyp[v]+bwe[u]);//,flag=1;
	}
	bma[u]=flag;
	return flag;
}
void work()
{
	for(int i=1;i<=n;i++)	if(vis[i]==0)	tarjan(i);
	for(int u=1;u<=n;u++)
		for(int i=b.p[u];i!=-1;i=b.e[i].nxt)
		{
			int v=b.e[i].v;
			if(idx[u]!=idx[v])	a.ae(idx[u],idx[v]);//cout<<idx[u]<<" "<<idx[v]<<endl;
		}
	root=idx[root];
	memset(vis,0,sizeof vis);
	dfs(root);
}
int main()
{
	input();
	work();
	printf("%d",dyp[root]);
}
