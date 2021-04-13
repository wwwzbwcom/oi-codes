#include<iostream>
#include<cstdio>
using namespace std;
double dp[1100];
double get(int n)
{
	return double((n)*(n-1));
}
void pt()
{
	dp[0]=1;
	for(int i=2;i<=1000;i++) dp[i]=(get(i)/(get(i+1)-get(1)))*dp[i-2];
}
int gn,t,d;
int main()
{
	pt();
	cin>>gn;
	for(int g=1;g<=gn;g++)
	{
		cin>>t>>d;
		printf("Case %d: %.10lf\n",g,dp[t]);
	}
}
