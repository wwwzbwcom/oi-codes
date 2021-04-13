#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int y[10000],s[10000];
int book[10000];
int min0[10000];
int dp[2000][2000];
int main()
{
	int n;
	cin>>n;
	int tmp;
	for(int i=1;i<=n;i++)	cin>>tmp,y[tmp]=i;
	for(int i=1;i<=n;i++)	book[y[i]]=i;
	while(cin>>tmp)
	{
		s[tmp]=1;
		for(int i=2;i<=n;i++)
		{
			cin>>tmp;
			s[tmp]=i;
		}
		for(int i=1;i<=n;i++)
			s[i]=book[s[i]];
	//	for(int i=1;i<=n;i++)	cout<<s[i]<<" ";
	//	cout<<endl;
		memset(min0,0,sizeof min0);
		int cur=0;
		for(int i=1;i<=n;i++)
		{
			int t=lower_bound(min0,min0+cur,s[i])-min0;
			if(t>=cur)	cur++;
		//	cout<<i<<"="<<t<<"="<<s[i]<<endl;
			min0[t]=s[i];
		}
		cout<<cur<<endl<<endl;
		
		/* 
		for(int i=2;i<=n;i++)	cin>>s[i];
		memset(dp,0,sizeof dp);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
				if(y[i]==s[j])	dp[i][j]=dp[i-1][j-1]+1;
			}
		cout<<dp[n][n]<<endl;
		*/
	}
}
