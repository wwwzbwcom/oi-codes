#include<iostream>
#include<cstring>
#include<cstdio>
#include<stack>
using namespace std;
struct Edge
{
	int v,s;
	double h;
	int next;
}e[1000000],r[1000000];
int pre[100000],en=0;
int rpre[100000],rn=0;

int cnt=0;
stack <int> s;
int vis[100000],low[100000];
int instack[100000];

int b[100000];
int bs[100000];
int bc[100000];
int block=0;

int n,m;
int start;

int dp[100000];
void addedge(int u,int v,int s,double h)
{
	e[en].v=v;e[en].s=s;e[en].h=h;e[en].next=pre[u];pre[u]=en++;
}
void addrdge(int u,int v,int s)
{
	r[rn].v=v;r[rn].s=s;r[rn].next=rpre[u];rpre[u]=rn++;
}
void tarjan(int u)
{
	vis[u]=low[u]=++cnt;
	s.push(u);instack[u]=1;
	for(int i=pre[u];i!=-1;i=e[i].next)
	{
		int v=e[i].v;
		if(vis[v]==0)
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else	if(instack[v]==1)	low[u]=min(low[u],vis[v]);
	}
	if(vis[u]==low[u])
	{
		block++;
		int t;
		do
		{
			t=s.top();	instack[t]=0;	s.pop();
			b[t]=block;	bs[block]++;
		}while(t!=u);
	}
}
int idx(int s,double h)
{
	int ans=0;
	while(s)	{	ans+=s;	s=(double)s*h;}
	return ans;
}
void dfs(int u)
{
	for(int i=rpre[u];i!=-1;i=r[i].next)	dfs(r[i].v);
	for(int i=rpre[u];i!=-1;i=r[i].next)	dp[u]=max(dp[u],dp[r[i].v]+r[i].s);
	dp[u]+=bc[u];
}
int main()
{
	memset(pre,-1,sizeof pre);en=0;
	memset(rpre,-1,sizeof rpre);rn=0;
	
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int u,v,s;
		double h;
		scanf("%d%d%d%lf",&u,&v,&s,&h);
		addedge(u,v,s,h);
	}
	scanf("%d",&start);
	
	for(int i=1;i<=n;i++)	if(vis[i]==0)	tarjan(i);
	for(int u=1;u<=n;u++)
		for(int i=pre[u];i!=-1;i=e[i].next)
		{
			int v=e[i].v;
			if(b[u]==b[v])	bc[b[u]]+=idx(e[i].s,e[i].h);
			else	addrdge(b[u],b[v],e[i].s);
		}
//	for(int i=1;i<=n;i++)
//		cout<<i<<"="<<b[i]<<endl;
	dfs(b[start]);
	printf("%d\n",dp[b[start]]);
}
