#include<iostream>
using namespace std;
int n;
int dis[20][20];
int dp[20000][20];
int main()
{
	while(cin>>n,n)
	{
		n++;
		for(int i=0;i<20000;i++)
			for(int j=0;j<20;j++)
				dp[i][j]=1e9;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				cin>>dis[i][j];
		
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
		
		dp[0][0]=0;
		for(int i=0;i<(1<<n);i++)
		{
			for(int j=0;j<n;j++)
				for(int k=0;k<n;k++)
					if((i&(1<<k))==0)
						dp[(i|(1<<k))][k]=min(dp[(i|(1<<k))][k],dp[i][j]+dis[j][k]);
				//		cout<<(i|(1<<k))<<"="<<k<<"="<<dp[(i|(1<<k))][k]<<" "<<i<<"="<<j<<"="<<dp[i][j]<<" "<<dis[j][k]<<endl;
		}
		int ans=1e9;
		for(int i=0;i<n;i++)	ans=min(dp[(1<<n)-1][i]+dis[i][0],ans);
		cout<<ans<<endl;
	}
}
