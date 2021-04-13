#include<iostream>
#include<cstring>
using namespace std;
int n,m;
int in[100000];
int out[100000];
long long dp[20][10000];
int cnt=0;
void dfs(int now,int last,int inc,int outc)
{
	if(now==n)
	{
		if(last==0)	in[cnt]=inc,out[cnt]=outc,cnt++;
		return;
	}
	if(last==1)	dfs(now+1,0,inc,outc);
	else
	{
		dfs(now+1,0,inc+(1<<now),outc);
		dfs(now+1,0,inc,outc+(1<<now));
		dfs(now+1,1,inc,outc);
	}
}
int main()
{
//	cout<<(1<<11)<<endl;
//	n=11;
//	dfs(0,0,0,0);
//	cout<<cnt<<endl;
//	for(int i=0;i<cnt;i++)	if(i>10000)cout<<i<<" "<<in[i]<<" "<<out[i]<<endl;
	while(cin>>n>>m,n,m)
	{
		if((n*m)%2==1)	cout<<"0"<<endl;
		else
		{
			cnt=0;	dfs(0,0,0,0);
			memset(dp,0,sizeof dp);
			dp[0][0]=1;
			for(int i=0;i<m;i++)
				for(int j=0;j<(1<<n);j++)	if(dp[i][j]>0)
					for(int k=0;k<cnt;k++)
						if(in[k]==j)	dp[i+1][out[k]]+=dp[i][j];
			//cout<<cnt<<endl;
			cout<<dp[m][0]<<endl;;
		}
	}
}
