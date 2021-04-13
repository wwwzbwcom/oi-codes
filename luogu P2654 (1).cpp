#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
priority_queue <long long> q;
int n,m,k;
long long s[100];
long long sum[100];
long long dp[100][100];
bool vis[100][100];
long long dfs(int l,int r)
{
	if(vis[l][r])	return dp[l][r];
	vis[l][r]=1;
	if(l==r)	dp[l][r]=0;
	else	dp[l][r]=1e18;
	for(int i=l;i<r;i++)
	{
		dp[l][r]=min(dp[l][r],dfs(l,i)+dfs(i+1,r)+(sum[r]-sum[l-1]));
	}
	return dp[l][r];
}
long long work()
{
	memset(vis,0,sizeof vis);
	long long ans=1e18;
	for(int i=1;i<=m;i++)
	{
		ans=min(ans,dfs(i,i+m-1));
	}
	return ans;
}
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		long long t;	cin>>t;
		q.push(-t);
	}
	long long ans=0;
	for(int i=1;i<=k;i++)
	{
		long long cur=0;
		for(int j=1;j<=m;j++)
		{
			int p;	cin>>p;
			s[p]=-q.top();	q.pop();
			cur+=s[p];
		}
		
		for(int j=m+1;j<=2*m;j++)	s[j]=s[j-m];
		for(int j=1;j<=2*m;j++)	sum[j]=sum[j-1]+s[j];
		long long tmp=work();
	//	for(int j=1;j<=m;j++)	cout<<s[j]<<" ";
	//	cout<<"================="<<tmp<<endl;
		ans+=tmp;
		q.push(-cur);
	}
	cout<<ans<<endl;
}
