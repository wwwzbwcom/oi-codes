#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
struct Graph
{
	Graph(){n=0;memset(p,-1,sizeof p);}
	struct Edge
	{
		int v,c;
		int nxt;
	}e[60100];
	int p[500],n;
	void ae(int u,int v,int c)
	{
		e[n].v=v;e[n].c=c;e[n].nxt=p[u];p[u]=n++;
	}
}f,b;
int n,m;
int qn;
bool vis[500][500];
int dyp[500][500];
void dfs(int u,int v)
{
	if(vis[u][v]==true)	return; 
	vis[u][v]=true;
	for(int i=f.p[u];i!=-1;i=f.e[i].nxt)
		for(int j=b.p[v];j!=-1;j=b.e[j].nxt)
		{
			int uv=f.e[i].v,uc=f.e[i].c;
			int vv=b.e[j].v,vc=b.e[j].c;
			dfs(uv,vv);
			if(uc==vc&&dyp[uv][vv]!=-1)
			{
				if(dyp[u][v]==-1)	dyp[u][v]=dyp[uv][vv]+2;
				else	dyp[u][v]=min(dyp[u][v],dyp[uv][vv]+2);
			}
		}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v; char c[10];	scanf("%d%d%s",&u,&v,c);
		f.ae(u,v,c[0]);
		b.ae(v,u,c[0]);
	}
	memset(dyp,-1,sizeof dyp);
	for(int i=1;i<=n;i++)	dyp[i][i]=0,vis[i][i]=true;
	for(int u=1;u<=n;u++)
		for(int i=f.p[u];i!=-1;i=f.e[i].nxt)
		{
			int v=f.e[i].v;
			dyp[u][v]=1;	vis[u][v]=true;
		}
	scanf("%d",&qn);
	int u,v;
	for(int q=1;q<=qn;q++)
	{
		scanf("%d",&v);
		if(q!=1)
		{
			dfs(u,v);
			printf("%d\n",dyp[u][v]);
		}
		u=v;
	}
}
