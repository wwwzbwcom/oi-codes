#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
int n,m;
int sto[1000];
int sum[1000];
long long dp[1000][1000];
long long ansMin=1e12,ansMax=0;
long long workMin(int l,int r)
{
	for(int i=0;i<1000;i++)	for(int j=0;j<1000;j++)	dp[i][j]=2e9;
	for(int i=l;i<=r;i++)	dp[i][1]=(((sum[i]-sum[l-1])%10+10)%10);
	for(int i=l;i<=r;i++)
	{
		for(int j=l-1;j<i;j++)
			for(int k=2;k<=min(j-l+2,m);k++)
				dp[i][k]=min(dp[i][k],dp[j][k-1]*(((sum[i]-sum[j])%10+10)%10));
	}
	return dp[r][m];
}
long long workMax(int l,int r)
{
	for(int i=0;i<1000;i++)	for(int j=0;j<1000;j++)	dp[i][j]=0;
	dp[l-1][0]=1;
	for(int i=l;i<=r;i++)	dp[i][1]=(((sum[i]-sum[l-1])%10+10)%10);
	for(int i=l;i<=r;i++)
	{
		for(int j=l-1;j<i;j++)
			for(int k=2;k<=min(j-l+2,m);k++)
				dp[i][k]=max(dp[i][k],dp[j][k-1]*(((sum[i]-sum[j])%10+10)%10));
	}
	return dp[r][m];
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>sto[i];
	for(int i=n+1;i<=2*n;i++)	sto[i]=sto[i-n];
	for(int i=1;i<=2*n;i++)	sum[i]=sum[i-1]+sto[i];
//	cout<<workMin(4,n+3)<<endl;
	for(int i=1;i<=n;i++)	ansMin=min(ansMin,workMin(i,i+n-1));
	for(int i=1;i<=n;i++)	ansMax=max(ansMax,workMax(i,i+n-1));
	cout<<ansMin<<endl<<ansMax<<endl; 
}
