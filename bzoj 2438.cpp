#include<cstring>
#include<cstdio>
#include<iostream>
#include<iomanip> 
#include<stack>
using namespace std;
const int maxn=300100;
struct Graph
{
	Graph()
	{
		memset(p,-1,sizeof p);	n=0;
	}
	struct Edge
	{
		int v,nxt;
	}e[maxn];
	int p[maxn];
	int n;
	void ae(int u,int v)
	{
		e[n].v=v;e[n].nxt=p[u];p[u]=n++;
	}
}b,a;
int vis[maxn],low[maxn],ist[maxn],tc;
stack <int> sta;
int blo[maxn],siz[maxn],bn;
int ind[maxn];
void tarjan(int u)
{
	vis[u]=low[u]=++tc;
	ist[u]=1;sta.push(u);
	for(int i=b.p[u];i!=-1;i=b.e[i].nxt)
	{
		int v=b.e[i].v;
		if(vis[v]==0)	tarjan(v),	low[u]=min(low[u],low[v]);
		else	if(ist[v]==1)	low[u]=min(low[u],vis[v]);
	}
	if(vis[u]==low[u])
	{
		bn++;
		int v;
		do
		{
			v=sta.top();
			blo[v]=bn;
			ist[v]=0;
			siz[bn]++;
			sta.pop();
		}while(v!=u);
	}
}
int main()
{
	int n,m;	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		b.ae(u,v);
	}
	for(int i=1;i<=n;i++)	if(vis[i]==0)	tarjan(i);
	for(int u=1;u<=n;u++)
		for(int i=b.p[u];i!=-1;i=b.e[i].nxt)
		{
			int v=b.e[i].v;
			if(blo[u]!=blo[v])	a.ae(blo[u],blo[v]),ind[blo[v]]++;
		}
	int ans=0;
	for(int i=1;i<=bn;i++)	if(ind[i]==0)	ans++;
	for(int u=1;u<=bn;u++)	if(ind[u]==0&&siz[u]==1)
	{
		int flag=0;
		for(int i=a.p[u];i!=-1;i=a.e[i].nxt)
		{
			int v=a.e[i].v;	//cout<<v<<" "<<ind[v]<<endl;
			if(ind[v]<2)	flag=1;
		}
		if(flag==1)	continue;
		ans--;
		break;
	}
	cout<<fixed<<setprecision(6)<<1.0-(double)ans/n<<endl; 
}
