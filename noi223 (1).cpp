#include<iostream>
using namespace std;
long long dp[500][500];
int n;
int main()
{
	for(int i=0;i<500;i++)	dp[0][i]=1;
	for(int i=1;i<500;i++)
		for(int j=i/2+1;j<=i;j++)
			dp[i][j]=1;
	for(int i=1;i<500;i++)
		for(int j=i/2;j>=0;j--)
			dp[i][j]=dp[i-2*j][j]+dp[i][j+1];
	while(cin>>n,n)	cout<<n<<" "<<dp[n][0]<<endl;
}
