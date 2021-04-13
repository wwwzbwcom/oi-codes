#include<iostream>
#include<cstring>
using namespace std;
const int oo=999999999;
int gn=0;
int n,times;
int ti[100];
int sn,en;

int st[100][500];
int et[100][500];
int cur;

int dp[500][100];
bool input()
{
	cin>>n;
	if(n)
	{
		memset(st,0,sizeof st);
		memset(et,0,sizeof et);
		cin>>times;
		for(int i=1;i<n;i++)
			cin>>ti[i];
		cin>>sn;
		for(int i=1;i<=sn;i++)
		{
			cin>>cur;
			for(int j=1;j<=n;j++)
			{
				st[j][cur]=1;
				cur+=ti[j];
			}
		}
		cin>>en;
		for(int i=1;i<=en;i++)
		{
			cin>>cur;
			for(int j=n;j>=1;j--)
			{
				et[j][cur]=1;
				cur+=ti[j-1]; 
			}
		}
		return 1;
	}
	else return 0;
}
int main()
{
	while(input())
	{
		gn++;
		for(int i=0;i<=times;i++)
			for(int j=0;j<=n;j++)
				dp[i][j]=oo;
		dp[0][1]=0;
		for(int i=0;i<=times;i++)
			for(int j=1;j<=n;j++)
			{
				int cur=i,wait=0;
				while(st[j][cur]==0&&cur<=times)	cur++,wait++;
				dp[cur+ti[j]][j+1]=min(dp[cur+ti[j]][j+1],dp[i][j]+wait);
				
				cur=i,wait=0;
				while(et[j][cur]==0&&cur<=times)	cur++,wait++;
				dp[cur+ti[j-1]][j-1]=min(dp[cur+ti[j-1]][j-1],dp[i][j]+wait);
			}
		int ans=oo;
		for(int i=0;i<=times;i++)
		{
			ans=min(ans,dp[i][n]+times-i);
		}
		cout<<"Case Number "<<gn<<": ";
		if(ans==oo)	cout<<"impossible"<<endl;
		else cout<<ans<<endl;
	}
}
