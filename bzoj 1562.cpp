#include<vector>
#include<cstdio>
#include<cstring>
//#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=20100;
int n;
vector <int> edg[maxn];
int dis[maxn];
int vis[maxn],mat[maxn];
int cnt=0;
int ans[maxn];
int dfs(int u)
{
	for(int i=0;i<edg[u].size();i++)
	{
		int v=edg[u][i];
		if(vis[v]==0)
		{
			vis[v]=1;
			if(mat[v]==0||dfs(mat[v]))
			{
				mat[v]=u;
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)	scanf("%d",&dis[i]);
	for(int i=0;i<n;i++)
	{
		edg[i].push_back((i-dis[i]+n)%n+n);	edg[(i-dis[i]+n)%n+n].push_back(i);
		edg[i].push_back((i+dis[i])%n+n);		edg[(i+dis[i])%n+n].push_back(i);
	}
	for(int i=0;i<2*n;i++)	sort(edg[i].begin(),edg[i].end());
	for(int i=n-1;i>=0;i--)
	{
		memset(vis,0,sizeof vis);
		cnt+=dfs(i);
	}
	if(cnt==n)
	{
		for(int i=n;i<2*n;i++)	ans[mat[i]]=i-n;
		for(int i=0;i<n-1;i++)	printf("%d ",ans[i]);
		printf("%d",ans[n-1]);
	}
	else	printf("No Answer");
}
