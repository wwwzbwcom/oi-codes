#include<iostream>
using namespace std;
int n,m,qn;
int t[500];
int dis[500][500];
int vis[500];
int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)	cin>>t[i];
	for(int i=0;i<500;i++)	for(int j=0;j<500;j++)	dis[i][j]=1e9;
	for(int i=0;i<m;i++)
	{
		int u,v,c;
		cin>>u>>v>>c;
		dis[u][v]=dis[v][u]=c;
	}
	cin>>qn;
	int l=0;
	for(int q=0;q<qn;q++)
	{
		int u,v,ti;
		cin>>u>>v>>ti;
		for(int k=l;k[t]<=ti&&k<n;k++)	vis[k]=1;
		for(int k=l;t[k]<=ti&&k<n;k++)
		{
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			l++;
		}
		if(dis[u][v]==1e9||!vis[u]||!vis[v])	cout<<"-1"<<endl;
		else	cout<<dis[u][v]<<endl;
	}
}
