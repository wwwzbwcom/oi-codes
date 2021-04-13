#include<iostream>
using namespace std;
int n;
int s[100];
int dp[100];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>s[i];
	dp[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=40;j>=s[i];j--)
			dp[j]+=dp[j-s[i]];
	}
	cout<<dp[40]<<endl;
}
