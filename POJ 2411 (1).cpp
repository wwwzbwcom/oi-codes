#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
int h,w;
vector <int> idx[3000];
int in[300000];
int out[300000];
unsigned long long dp[20][3000];
int cnt;
int dfs(int now,int ti,int to)
{
	if(now==h)
	{
		in[cnt]=ti;
		out[cnt]=to;
		idx[in[cnt]].push_back(cnt);
		cnt++;
	}
	else
	{
		if(now+2<=h)	dfs(now+2,ti,to);
		dfs(now+1,ti,to+(1<<now));
		dfs(now+1,ti+(1<<now),to);
	}
}
int main()
{
//	cout<<(1<<10)<<endl;
	while(cin>>h>>w,h,w)
	{
	//	swap(h,w);
		cnt=0;
		memset(in,0,sizeof in);
		memset(out,0,sizeof out);
		memset(dp,0,sizeof dp);
		memset(idx,0,sizeof idx); 
		
		if(h*w%2!=0)	cout<<"0"<<endl;
		else
		{
			dfs(0,0,0);
		//	cout<<cnt<<endl;
		//	for(int i=0;i<cnt;i++)
		//		cout<<in[i]<<"="<<out[i]<<endl;
			dp[0][0]=1;
			int siz=(1<<h);
			for(int i=0;i<=w;i++)
				for(int j=0;j<=siz;j++)
					for(int k=0;k<idx[j].size();k++)
						dp[i+1][out[idx[j][k]]]+=dp[i][j];
			cout<<dp[w][0]<<endl;
		}
	}
}
