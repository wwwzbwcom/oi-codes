#include<iostream>
#include<cstring>
#include<stack>
#include<map>
using namespace std;
struct Graph
{
	Graph(){memset(p,-1,sizeof p);n=0;}
	struct Edge
	{
		int v;
		int nxt;
	}e[1000100];
	int p[100100];
	int n;
	void ae(int u,int v)
	{
		e[n].v=v;e[n].nxt=p[u];p[u]=n++;
	}
}b,a;
int  n,m,x;

int vis[100100];
int low[100100];
int ins[100100];
int blo[100100];
int siz[100100];
stack <int> sta;
int cnt=0,bn=0;

map <int,map<int,int> > boo;

int dyp[100100];
int way[100100];

int mxa=0,ans=0;
void tarjan(int u)
{
	vis[u]=low[u]=++cnt;
	ins[u]=1;	sta.push(u);
	for(int i=b.p[u];i!=-1;i=b.e[i].nxt)
	{
		int v=b.e[i].v;
		if(vis[v]==0)	tarjan(v),low[u]=min(low[u],low[v]);
		else	if(ins[v]==1)	low[u]=min(low[u],vis[v]);
	}
//	cout<<u<<"="<<low[u]<<"="<<vis[u]<<endl;
	if(low[u]==vis[u])
	{
		bn++;
		int p;
		do
		{
			p=sta.top();sta.pop();ins[p]=0;
			blo[p]=bn;siz[bn]++;
		}while(p!=u);
	}
	
}
void dfs(int u)
{
	if(dyp[u])	return;
	dyp[u]=siz[u];way[u]=1;
	for(int i=a.p[u];i!=-1;i=a.e[i].nxt)
	{
		int v=a.e[i].v;
		dfs(v);
		if(dyp[v]+siz[u]>dyp[u])	dyp[u]=dyp[v]+siz[u],way[u]=way[v],way[u]%=x;
		else	if(dyp[v]+siz[u]==dyp[u])	way[u]+=way[v],way[u]%=x;
	}
}
int main()
{
	cin>>n>>m>>x;
	for(int i=1;i<=m;i++)
	{
		int u,v;cin>>u>>v;
		b.ae(u,v);
	}
	
	for(int i=1;i<=n;i++)	if(vis[i]==0)	tarjan(i);
	
	for(int u=1;u<=n;u++)
		for(int i=b.p[u];i!=-1;i=b.e[i].nxt)
		{
			int v=b.e[i].v;
			if(blo[u]!=blo[v])
			if(boo[blo[u]][blo[v]]==0)	a.ae(blo[u],blo[v]),boo[blo[u]][blo[v]]=1;
			//a.ae(blo[u],blo[v]);
		}
	
	for(int i=1;i<=bn;i++)	dfs(i);
	
	for(int i=1;i<=bn;i++)
	{
		if(dyp[i]>mxa)	mxa=dyp[i],ans=way[i],ans%=x;
		else	if(dyp[i]==mxa)	ans+=way[i],ans%=x;
	}
//	cout<<siz[blo[3]]<<" "<<blo[3]<<endl;
//	cout<<dyp[3]<<endl;
	cout<<mxa<<endl<<ans;
}
