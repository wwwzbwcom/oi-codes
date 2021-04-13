#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
int n,c;
int h[100010];
int dp[100010][110];
int les[110],mor[110];
int ans=1e9+5e8;
int main()
{
	cin>>n>>c;
	for(int i=1;i<=n;i++)	cin>>h[i];
	for(int i=0;i<100000;i++)	for(int j=0;j<110;j++)	dp[i][j]=1e9+5e8;
	for(int i=0;i<110;i++)	dp[0][i]=0;
	for(int i=0;i<110;i++)	les[i]=-c*i,mor[i]=c*i;
	for(int i=1;i<=n;i++)
	{
		for(int j=h[i];j<=100;j++)	dp[i][j]=min( les[j]+c*j , mor[j]-c*j )+(j-h[i])*(j-h[i]);
		for(int j=0;j<110;j++)	les[j]=mor[j]=1e9+5e8;
		for(int j=1;j<=100;j++)	les[j]=min(les[j-1],dp[i][j]-c*j);
		for(int j=100;j>=1;j--)	mor[j]=min(mor[j+1],dp[i][j]+c*j); 
	}
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=1;j<=10;j++)
//			cout<<dp[i][j]<<" ";
//		cout<<endl;
//	}
	for(int j=1;j<=100;j++)	ans=min(ans,dp[n][j]);
	cout<<ans<<endl;
}
