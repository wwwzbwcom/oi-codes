#include<iostream>
#include<cstring>
using namespace std;
struct Edge
{
	int v,nxt;
}e[10000];
int n;
int pre[10000],en=0;
int dp[10000][5];
int vis[10000];
void addedge(int u,int v)
{
	e[en].v=v;e[en].nxt=pre[u];pre[u]=en++;
	e[en].v=u;e[en].nxt=pre[v];pre[v]=en++;
}
void dfs(int u,int f)
{
	if(vis[u])	return;
	vis[u]=1;	int flag=0;	
	for(int i=pre[u];i!=-1;i=e[i].nxt)	if(e[i].v!=f)	dfs(e[i].v,u),flag=1;
	
	if(flag==0)
	{
		dp[u][0]=dp[u][1]=0;	dp[u][2]=dp[u][3]=1e9;	dp[u][4]=1;
	}
	else
	{
		dp[u][0]=dp[u][1]=0;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v;
			if(v==f)	continue;
			dp[u][0]+=min(min(dp[v][1],dp[v][2]),min(dp[v][3],dp[v][4]));
			dp[u][1]+=min(dp[v][2],min(dp[v][3],dp[v][4]));
		}
		dp[u][2]=dp[u][3]=1e9;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v1=e[i].v;
			if(v1==f)	continue;
			int t2=dp[v1][3],t3=dp[v1][4];
			for(int j=pre[u];j!=-1;j=e[j].nxt)
			{
				int v2=e[j].v;
				if(v2==f)	continue;
				if(v2!=v1)	t2+=min(dp[v2][2],min(dp[v2][3],dp[v2][4])),t3+=min(min(dp[v2][1],dp[v2][2]),min(dp[v2][3],dp[v2][4]));
			}
			dp[u][2]=min(dp[u][2],t2);
			dp[u][3]=min(dp[u][3],t3);
		}
		dp[u][4]=1;
		for(int i=pre[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].v;
			if(v==f)	continue;
			dp[u][4]+=min(min(min(dp[v][0],dp[v][1]),min(dp[v][2],dp[v][3])),dp[v][4]);
		}
	}
}
int main()
{
	memset(pre,-1,sizeof pre);
	cin>>n;
	for(int u=2;u<=n;u++)
	{
		int v;
		cin>>v;
		addedge(u,v);
	}
	dfs(1,0);
	cout<<min(min(dp[1][2],dp[1][3]),dp[1][4])<<endl;
	//for(int i=1;i<=n;i++)		cout<<dp[i][0]<<" "<<dp[i][1]<<" "<<dp[i][2]<<" "<<dp[i][3]<<" "<<dp[i][4]<<endl;
}
