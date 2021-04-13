#include<iostream>
using namespace std;
int dp[2000];
int main()
{
	int a1,a2,a3,a4,a5,a6;
	int ans=0;
	cin>>a1>>a2>>a3>>a4>>a5>>a6;
	dp[0]=1;
	for(int i=1;i<=a1;i++)
		for(int j=1000;j>=0;j--)
			if(dp[j])	dp[j+1]=1;
	for(int i=1;i<=a2;i++)
		for(int j=1000;j>=0;j--)
			if(dp[j])	dp[j+2]=1;
	for(int i=1;i<=a3;i++)
		for(int j=1000;j>=0;j--)
			if(dp[j])	dp[j+3]=1;
	for(int i=1;i<=a4;i++)
		for(int j=1000;j>=0;j--)
			if(dp[j])	dp[j+5]=1;
	for(int i=1;i<=a5;i++)
		for(int j=1000;j>=0;j--)
			if(dp[j])	dp[j+10]=1;
	for(int i=1;i<=a6;i++)
		for(int j=1000;j>=0;j--)
			if(dp[j])	dp[j+20]=1;
	for(int i=1;i<=1000;i++)
		if(dp[i])	ans++;
	cout<<"Total="<<ans<<endl;
}
