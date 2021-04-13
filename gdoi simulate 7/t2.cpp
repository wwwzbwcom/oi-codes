#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;
const int maxn=1000000;
int n,m;
struct Graph
{
	Graph()
	{
		memset(pre,-1,sizeof pre);	en=0;
	}
	struct Edge
	{
		int v,m,nxt;
	}e[maxn];
	int pre[maxn],en;
	int vis[maxn],poi[maxn],ind[maxn],rev[maxn],cnt;
	int buc[maxn];
	vector <int> sto[maxn]; 
	void addedge(int u,int v)
	{
		e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
		e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
	}
	int dfs1(int u,int f,int fe)
	{
		vis[u]=++cnt;
	//	cout<<u<<"="<<f<<endl;
		for(int i=pre[u];i!=-1;i=e[i].nxt)	if(e[i].m==0)
		{
			int v=e[i].v;
			if(vis[v]==0)	e[i].m=1,e[i^1].m=1,dfs1(v,u,i),poi[i/2+1]=v,ind[v]=(ind[v]+1)%2;
			else	if(vis[v]<vis[u])	e[i].m=1,e[i^1].m=1,poi[i/2+1]=v,ind[v]=(ind[v]+1)%2;
		}
	}
	int dfs2(int u,int f,int fe)
	{
		vis[u]=1;
	//	cout<<u<<"~"<<f<<endl;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v;
			if(vis[v]==0)	dfs2(v,u,i);
		}
	//	cout<<u<<" "<<rev[u]<<" "<<ind[u]<<endl;
		if(rev[u]==1&&f!=0)		ind[u]=(ind[u]+1)%2;
		if(ind[u]%2==1&&f!=0)	ind[u]=(ind[u]+1)%2,rev[u]^=1;
		if(rev[u]==1&&f!=0)		rev[f]^=1,ind[f]=(ind[f]+1)%2,poi[fe/2+1]=f;
	}
	void work()
	{
		int ans=0;
		for(int i=1;i<=n;i++)	if(vis[i]==0)	dfs1(i,0,0);
		memset(vis,0,sizeof vis);
		for(int i=1;i<=n;i++)	if(vis[i]==0)	dfs2(i,0,0);
		for(int i=1;i<=m;i++)	buc[poi[i]]++,sto[poi[i]].push_back(i);
		for(int i=1;i<=n;i++)	ans+=buc[i]/2;
		printf("%d\n",ans);
		for(int i=1;i<=n;i++)
			for(int j=0;j+1<sto[i].size();j+=2)
				printf("%d %d\n",sto[i][j],sto[i][j+1]);
	}
}gp;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		gp.addedge(u,v);
	}
	gp.work();
}
