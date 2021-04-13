#include<iostream>
using namespace std;
int n,h,delta;
int max0[2100];
int dp[2100][2100];
int book[2100][2100];
int main()
{
	cin>>n>>h>>delta;
	for(int i=0;i<n;i++)
	{
		int	m;	cin>>m;
		for(int j=0;j<m;j++)
		{
			int	t;	cin>>t;
			book[i][t]++;
		}
	}
	for(int i=1;i<=h;i++)
	{
		for(int j=0;j<n;j++)
		{
			dp[j][i]=dp[j][i-1];
			if(i-delta>=0)	dp[j][i]=max(dp[j][i],max0[i-delta]);
			dp[j][i]+=book[j][i];
			max0[i]=max(max0[i],dp[j][i]);
		}
	}
	int ans=0;
	for(int i=0;i<n;i++)	ans=max(ans,dp[i][h]);
	cout<<ans;
}
