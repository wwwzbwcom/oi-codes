#include<iostream>
#include<cstdio>
using namespace std;
int dp[801][801][20][2];
int map[801][801];
int main()
{
	int n,m,mod;
	cin>>n>>m>>mod;mod++;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&map[i][j]),map[i][j]%=mod;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			dp[i][j][map[i][j]][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=0;k<mod;k++)
			{
				dp[i][j][k][0]+=dp[i-1][j][(k-map[i][j]+mod)%mod][1];dp[i][j][k][0]%=1000000007;
				dp[i][j][k][0]+=dp[i][j-1][(k-map[i][j]+mod)%mod][1];dp[i][j][k][0]%=1000000007;
				dp[i][j][k][1]+=dp[i-1][j][(k+map[i][j])%mod][0];dp[i][j][k][1]%=1000000007;
				dp[i][j][k][1]+=dp[i][j-1][(k+map[i][j])%mod][0];dp[i][j][k][1]%=1000000007;
			}
	int	ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			ans+=dp[i][j][0][1];
			ans%=1000000007;
		}
	//cout<<endl;
	}
	cout<<ans<<endl;
}
