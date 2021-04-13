#include<iostream>
using namespace std;
int dp[100100];
int s[10];
int idx[]={1,2,3,5,10,20};
int main()
{
	cin>>s[0]>>s[1]>>s[2]>>s[3]>>s[4]>>s[5];
	dp[0]=1;
	for(int i=0;i<6;i++)
		for(int k=100000;k>=0;k--)
			if(dp[k])
			{
				for(int j=idx[i];j<=s[i]*idx[i];j+=idx[i])
				{
					dp[k+j]=1;
				}
			}
	int ans=0;
	for(int i=1;i<=100000;i++)	if(dp[i])	ans++;
	cout<<"Total="<<ans;
}
