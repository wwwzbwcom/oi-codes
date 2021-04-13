#include<cstdio>
#include<cstring>
using namespace std;
int n,m;
int vis[200];
int mat[200];
int edg[200][200];
int ans=0;
int dfs(int u)
{
	for(int v=1;v<=n;v++)
	{
		if(vis[v]==0&&edg[u][v]==1)
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
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		edg[u][v]=1;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(edg[i][k]==1&&edg[k][j]==1)
					edg[i][j]=1;
	
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof vis);
		ans+=dfs(i);
	}
	printf("%d\n",n-ans);
}
