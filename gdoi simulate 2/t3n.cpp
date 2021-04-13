#include<cstdio>
#include<cstring>
#include<iostream> 
#include<queue>
using namespace std;
const int maxn=100000;
struct Edge
{
	int v,c;
	int nxt;
}e[maxn*2];
int n,m;
int pre[maxn],en=0;
int cnt[maxn],fat[maxn],dis[maxn],sle[maxn];
int blo[maxn],lev[maxn];
int ans[maxn],an=0;
void addedge(int u,int v,int c)
{
	e[en].v=v;e[en].c=c;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].c=c;e[en].nxt=pre[v];pre[v]=en++;
}
void dfs1(int u,int f,int d,int l)
{
	cnt[u]=1;	fat[u]=f;	dis[u]=d;	sle[u]=l;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(v!=f)	dfs1(v,u,d+c,l+1),cnt[u]+=cnt[v];
	}
}
void dfs2(int u,int f,int bf,int l)
{
	blo[u]=bf;	lev[u]=l;
//	cout<<u<<" "<<lev[u]<<endl;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(v!=f&&cnt[v]>cnt[u]/2)	dfs2(v,u,bf,l);
	}
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v,c=e[i].c;
		if(v!=f&&cnt[v]<=cnt[u]/2)	dfs2(v,u,v,l+1);
	}
}
int lca(int u,int v)
{
	while(1)
	{
	//	cout<<u<<" "<<v<<" "<<lev[u]<<" "<<lev[v]<<endl;
		if(blo[u]==blo[v])
		{
			if(sle[u]>sle[v])	return v;
			else	return u;
		}
		else
		{
			if(lev[u]>lev[v])	u=fat[blo[u]];
			else	v=fat[blo[v]];
		}
	}
}
int main()
{
	memset(pre,-1,sizeof pre);
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int u,v,c;	scanf("%d%d%d",&u,&v,&c);
		addedge(u,v,c);
	}
	dfs1(1,0,0,1);
	dfs2(1,0,1,1);
	priority_queue <int> que; 
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
		//	cout<<i<<"="<<j<<"="<<lca(i,j)<<" "<<(dis[i]+dis[j]-2*dis[lca(i,j)])<<endl; 
			que.push(-(dis[i]+dis[j]-2*dis[lca(i,j)]));
			while(que.size()>m)	que.pop();
		}
	while(!que.empty())
	{
		ans[an++]=-que.top();
		que.pop();
	}
	for(int i=an-1;i>=0;i--)	printf("%d\n",ans[i]);
}
