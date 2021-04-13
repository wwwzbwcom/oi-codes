#include<iostream>
#include<cstdio>
using namespace std;
int n;
double dp[2000][2000];
int main()
{
	cin>>n;
	if(n>=4)
	{
		dp[0][0]=1;
		n/=2;
		for(int i=0;i<=n;i++)
		{
			for(int j=0;j<=n;j++)
			{
				if(i!=0) {if(j==n) dp[i][j]+=dp[i-1][j]; else dp[i][j]+=dp[i-1][j]*0.5;}
				if(j!=0) {if(i==n) dp[i][j]+=dp[i][j-1]; else dp[i][j]+=dp[i][j-1]*0.5;}
			}
		}
		printf("%.4lf",dp[n-2][n]+dp[n][n-2]);
	}
	else printf("%.4lf",0);
}

