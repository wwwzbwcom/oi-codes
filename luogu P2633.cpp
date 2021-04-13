#include<iostream>
#include<cstring>
using namespace std;
struct Edge
{
	int v,nxt;
}e[50000];
int pre[50000],en=0;
int n;
int wei[50000];
int dp[50000];
int vis[50000];
void addedge(int u,int v)
{
	e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
}
void dfs(int u,int f)
{	
	if(vis[u])	return;
	vis[u]=1;
	for(int i=pre[u];i!=-1;i=e[i].nxt)	if(e[i].v!=f)	dfs(e[i].v,u);
	int t=0;
	for(int i=pre[u];i!=-1;i=e[i].nxt)
	{
		if(e[i].v!=f)
		t+=max(0,dp[e[i].v]);
	}
	dp[u]=max(t+wei[u],0);
}
int main()
{
	memset(pre,-1,sizeof pre);
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>wei[i];
	for(int i=1;i<n;i++)
	{
		int u,v;	cin>>u>>v;
		addedge(u,v);
	}
	dfs(1,0);
	int ans=0;
	for(int i=1;i<=n;i++)	ans=max(ans,dp[i]);
	cout<<ans<<endl;
}
