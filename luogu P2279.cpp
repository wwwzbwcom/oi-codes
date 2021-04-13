#include<iostream>
#include<cstring>
using namespace std;
int dp[2000][3];
struct Edge
{
	int v,next;
}e[5000];
int pre[2000],en=0;
int n;
void addedge(int u,int v)
{
	e[en].v=v;e[en].next=pre[u];pre[u]=en++;
	e[en].v=u;e[en].next=pre[v];pre[v]=en++;
}
int dfs(int u,int f)
{
	for(int i=pre[u];i!=-1;i=e[i].next)	if(e[i].v!=f)	dfs(e[i].v,u);
	
	dp[u][0]=dp[u][1]=dp[u][2]=0;
	for(int i=pre[u];i!=-1;i=e[i].next)
	{
		int v=e[i].v;
		dp[u][0]=max(dp[u][0],dp[v][1]);
		dp[u][1]=max(dp[u][1],dp[v][2]);
		dp[u][2]=max(dp[u][2],dp[v][0]+1);
	}
}
int main()
{
	memset(pre,-1,sizeof pre);
	cin>>n;
	for(int u=2;u<=n;u++)
	{
		int v;	cin>>v;
		addedge(u,v);
	}
	dfs(1,0);
	cout<<min(dp[1][1],dp[1][2])<<endl;
}
