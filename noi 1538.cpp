#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int n,m;
double s,v;
double x[200],y[200];
double map[200][200];
int vis[200];
int mat[200];
double getdis(int a,int b)
{
	return sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
}
bool dfs(int u)
{
	vis[u]=1;
	for(int v=1;v<=n+m;v++)
	{
		if(map[u][v]>0&&vis[v]==0)
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
	while(cin>>n>>m>>s>>v)
	{
		for(int i=0;i<200;i++)	for(int j=0;j<200;j++)	map[i][j]=-1e10;
		memset(vis,0,sizeof vis);
		memset(mat,0,sizeof mat);
		
		for(int i=1;i<=n+m;i++)	cin>>x[i]>>y[i];
		
		for(int i=1;i<=n;i++)
			for(int j=n+1;j<=n+m;j++)
				if(getdis(i,j)/v<=s)
					map[i][j]=map[j][i]=getdis(i,j);
		
		int ans=0;
		for(int i=1;i<=n+m;i++)
		{
			memset(vis,0,sizeof vis);
			ans+=dfs(i);
		}
	//	cout<<ans<<endl;
		cout<<n-ans/2<<endl;
	}
}
