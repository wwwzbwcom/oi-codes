#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int oo=1e8;
int n;
int map[10][10];
int dp[20][10][10][10][10];
int vis[20][10][10][10][10];
int sum[10][10][10][10];
double tot=0;
int cnt=0;
int dfs(int now,int x1,int y1,int x2,int y2)
{
	if(vis[now][x1][y1][x2][y2])	return dp[now][x1][y1][x2][y2];
	vis[now][x1][y1][x2][y2]=1;
	if(now==1)	return dp[now][x1][y1][x2][y2]=sum[x1][y1][x2][y2];
	
	for(int i=y1;i<y2;i++)	dp[now][x1][y1][x2][y2]=min( dp[now][x1][y1][x2][y2], min( sum[x1][y1][x2][i]+dfs(now-1,x1,i+1,x2,y2), sum[x1][i+1][x2][y2]+dfs(now-1,x1,y1,x2,i) ) );
	for(int i=x1;i<x2;i++)	dp[now][x1][y1][x2][y2]=min( dp[now][x1][y1][x2][y2], min( sum[x1][y1][i][y2]+dfs(now-1,i+1,y1,x2,y2), sum[i+1][y1][x2][y2]+dfs(now-1,x1,y1,i,y2) ) );
	
	return dp[now][x1][y1][x2][y2];
}
int main()
{
	cin>>n;
	for(int i=1;i<=8;i++)
		for(int j=1;j<=8;j++)
			cin>>map[i][j],tot+=map[i][j];
	for(int y1=1;y1<=8;y1++)
		for(int x1=1;x1<=8;x1++)
			for(int y2=y1;y2<=8;y2++)
				for(int x2=x1;x2<=8;x2++)
				{
					sum[x1][y1][x2][y2]=0;
					for(int i=y1;i<=y2;i++)
						for(int j=x1;j<=x2;j++)
							sum[x1][y1][x2][y2]+=map[i][j];
					sum[x1][y1][x2][y2]=sum[x1][y1][x2][y2]*sum[x1][y1][x2][y2];
				}
	for(int i=0;i<20;i++)
		for(int y1=0;y1<10;y1++)
			for(int x1=0;x1<10;x1++)
				for(int y2=0;y2<10;y2++)
					for(int x2=0;x2<10;x2++)
						dp[i][y1][x1][y2][x2]=oo;
	printf("%.3lf\n",sqrt( ((double)dfs(n,1,1,8,8))/n - pow(tot/n,2)));
//	cout<<cnt<<endl;
	return 0;
}
