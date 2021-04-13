#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
int n,m;
string t,s[100];
long long dp[200][200];
long long gcd(long long a,long long b)
{
	if(b==0)	return a;
	return gcd(b,a%b);
}
int main()
{
	cin>>n>>m;
	getchar();
	for(int i=0;i<n;i++)	getline(cin,t),s[i]=" "+t;
//	for(int i=0;i<n;i++)	cout<<s[i]<<"="<<endl;
	dp[0][s[0].size()-1]=((long long)1<<51);
	for(int i=0;i<n;i++)
		for(int j=0;j<s[i].size();j++)
		{
			if(s[i][j]=='*')	dp[i+1][j-1]+=dp[i][j]/2,dp[i+1][j+1]+=dp[i][j]/2;
			if(s[i][j]=='.')	dp[i+2][j]+=dp[i][j];
		}
	long long a=dp[n][2*m],b=((long long)1<<51);
	long long t=gcd(a,b);
	cout<<a/t<<"/"<<b/t<<endl;
}
