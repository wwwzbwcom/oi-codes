#include<iostream>
using namespace std;
int n;
int dp[200][200];
int s[200][200];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			cin>>s[i][j];
	for(int i=n;i>=1;i--)
		for(int j=1;j<=i;j++)
			dp[i][j]=max(dp[i+1][j],dp[i+1][j+1])+s[i][j];
	cout<<dp[1][1]<<endl;
}
